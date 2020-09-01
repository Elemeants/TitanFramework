#include "i2c.h"

#include <assert.h>
#include <util/twi.h>

#include "gpio.h"
#include "utils/loop_utils.h"
#include "wiring.h"

#define I2C_DEFAULT_FLAGS (_BV(TWIE) | _BV(TWEN) | _BV(TWEA))
#define I2C_FRECUENCY_CALC(frec) (((F_CPU / frec) - 16U) / 2U)

void I2C_Init(I2C_BusHandler *bus)
{
    if (bus == NULL)
    {
        return;
    }

    // Pullup I2C pins
    GPIO_PinMode(I2C_SCL_PIN, PULL_UP);
    GPIO_PinMode(I2C_SDA_PIN, PULL_UP);

    // Set bus as initiated
    bus->state = I2C_READY;
    bus->send_stop = 1;
    bus->in_rep_start = 1;

    // Set frecuency
    bus->port->_TWBR = I2C_FRECUENCY_CALC(I2C_BUS_FREQ);
    // Preset clock prescaler
    _clear_bits(bus->port->_TWSR.prescaler, 0b00);
    // Set TWI Enabled, interruption enabled and ack slave
    _set_bits(bus->port->_TWCR.mask, I2C_DEFAULT_FLAGS);
}

void I2C_DeInit(I2C_BusHandler *bus)
{
    if (bus == NULL)
    {
        return;
    }

    _clear_bits(bus->port->_TWCR.mask, I2C_DEFAULT_FLAGS);
    GPIO_DigitalWrite(I2C_SCL_PIN, LOW);
    GPIO_DigitalWrite(I2C_SDA_PIN, LOW);
}

void I2C_SetAddress(I2C_BusHandler *bus, uint8_t addr)
{
    if (bus == NULL)
    {
        return;
    }

    bus->port->_TWAR.slaveAddress = addr;
}

void I2C_SetFrequency(I2C_BusHandler *bus, uint32_t frec)
{
    if (bus == NULL || frec == 0)
    {
        return;
    }

    bus->port->_TWBR = I2C_FRECUENCY_CALC(frec);
}

uint8_t I2C_ReadFrom(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop)
{
    if (bus == NULL)
    {
        return 0x00;
    }

    return 0x00;
}

uint8_t I2C_WriteTo(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
    if (bus == NULL)
    {
        return 0x00;
    }

    return 0x00;
}

uint8_t I2C_Transmit(I2C_BusHandler *bus, const uint8_t *data, uint8_t length)
{
    if (bus == NULL)
    {
        return 0x00;
    }

    return 0x00;
}

void I2C_AttachSlaveRxEvent(I2C_BusHandler *bus, void (*function)(uint8_t lenght))
{
    if (bus == NULL)
    {
        return;
    }

    bus->rxEvent = function;
}

void I2C_AttachSlaveTxEvent(I2C_BusHandler *bus, void (*function)(void))
{
    if (bus == NULL)
    {
        return;
    }

    bus->txEvent = function;
}

void I2C_Reply(I2C_BusHandler *bus, uint8_t ack)
{
    if (bus == NULL)
    {
        return;
    }

    bus->port->_TWCR.tw_int = 0b1;
    if (ack)
    {
        bus->port->_TWCR.tw_en_ack = 0b1;
    }
}

void I2C_Stop(I2C_BusHandler *bus)
{
    if (bus == NULL)
    {
        return;
    }

    bus->port->_TWCR.tw_en_ack = 0b1;
    bus->port->_TWCR.tw_stop = 0b1;
    while (bus->port->_TWCR.tw_stop)
        ;
    bus->state = I2C_READY;
}

void I2C_ReleaseBus(I2C_BusHandler *bus)
{
    if (bus == NULL)
    {
        return;
    }

    _set_bits(bus->port->_TWCR.mask, I2C_DEFAULT_FLAGS | _BV(TWINT));
    bus->state = I2C_READY;
}

void I2C_ISR_Call(void *params)
{
    // If not bus pointer then end the isr call
    if (params == NULL)
    {
        return;
    }
    I2C_ISR_Handler((I2C_BusHandler *)params);
}

uint8_t I2C_ReadNextByte(I2C_BusHandler *bus)
{
    int value = -1;

    // get each successive byte on each call
    if (bus->rxEventBuff_index < bus->rxEventBuff_lenght)
    {
        value = bus->rxEventBuff[bus->rxEventBuff_index];
        ++bus->rxEventBuff_index;
    }

    return value;
}
void I2C_ReadNextBytes(I2C_BusHandler *bus, uint8_t *buffer, uint8_t len)
{
    for_in_range(uint8_t, _index, 0, len)
    {
        uint8_t byte = I2C_ReadNextByte(bus);
        buffer[_index] = byte;
    }
}

void I2C_txEventHandler(I2C_BusHandler *bus)
{
    if (bus->txEvent)
        bus->txEvent();
}

void I2C_rxEventHandler(I2C_BusHandler *bus, uint8_t *inBytes, int numBytes)
{
    // don't bother if rx buffer is in use by a master requestFrom() op
    // i know this drops data, but it allows for slight stupidity
    // meaning, they may not have read all the master requestFrom() data yet
    if (bus->rxEventBuff_index < bus->rxEventBuff_lenght)
    {
        return;
    }
    // copy twi rx buffer into local read buffer
    // this enables new reads to happen in parallel
    for (uint8_t i = 0; i < numBytes; ++i)
    {
        bus->rxEventBuff[i] = inBytes[i];
    }
    // set rx iterator vars
    bus->rxEventBuff_index = 0;
    bus->rxEventBuff_lenght = numBytes;

    if (bus->rxEvent)
        bus->rxEvent(numBytes);
}

void I2C_ISR_Handler(I2C_BusHandler *bus)
{
    TWI_Handler bus_register = bus->port;
    uint8_t bus_status = bus_register->_TWSR.status;

    switch (bus_status)
    {
    // All Master
    case TW_START:      // sent start condition
    case TW_REP_START:  // sent repeated start condition
        // copy device address and r/w bit to output register and ack
        bus_register->_TWDR = bus->sla_rw.raw;
        I2C_Reply(bus, 1);
        break;

    // Master Transmitter
    case TW_MT_SLA_ACK:   // slave receiver acked address
    case TW_MT_DATA_ACK:  // slave receiver acked data
        // if there is data to send, send it, otherwise stop
        if (bus->masterBuffer_index < bus->masterBuffer_lenght)
        {
            // copy data to output register and ack
            TWDR = bus->masterBuffer[bus->masterBuffer_index++];
            I2C_Reply(bus, 1);
        }
        else
        {
            if (bus->send_stop)
                I2C_Stop(bus);
            else
            {
                bus->in_rep_start = true;  // we're gonna send the START
                // don't enable the interrupt. We'll generate the start, but we
                // avoid handling the interrupt until we're in the next transaction,
                // at the point where we would normally issue the start.
                bus_register->_TWCR.mask = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
                bus->state = I2C_READY;
            }
        }
        break;
    case TW_MT_SLA_NACK:  // address sent, nack received
        bus->error = TW_MT_SLA_NACK;
        I2C_Stop(bus);
        break;
    case TW_MT_DATA_NACK:  // data sent, nack received
        bus->error = TW_MT_DATA_NACK;
        I2C_Stop(bus);
        break;
    case TW_MT_ARB_LOST:  // lost bus arbitration
        bus->error = TW_MT_ARB_LOST;
        I2C_ReleaseBus(bus);
        break;

    // Master Receiver
    case TW_MR_DATA_ACK:  // data received, ack sent
        // put byte into buffer
        bus->masterBuffer[bus->masterBuffer_index++] = bus_register->_TWDR;
    case TW_MR_SLA_ACK:  // address sent, ack received
        // ack if more bytes are expected, otherwise nack
        if (bus->masterBuffer_index < bus->masterBuffer_lenght)
        {
            I2C_Reply(bus, 1);
        }
        else
        {
            I2C_Reply(bus, 0);
        }
        break;
    case TW_MR_DATA_NACK:  // data received, nack sent
        // put final byte into buffer
        bus->masterBuffer[bus->masterBuffer_index++] = bus_register->_TWDR;
        if (bus->send_stop)
            I2C_Stop(bus);
        else
        {
            bus->in_rep_start = true;  // we're gonna send the START
            // don't enable the interrupt. We'll generate the start, but we
            // avoid handling the interrupt until we're in the next transaction,
            // at the point where we would normally issue the start.
            bus_register->_TWCR.mask = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
            bus->state = I2C_READY;
        }
        break;
    case TW_MR_SLA_NACK:  // address sent, nack received
        I2C_Stop(bus);
        break;
    // TW_MR_ARB_LOST handled by TW_MT_ARB_LOST case

    // Slave Receiver
    case TW_SR_SLA_ACK:             // addressed, returned ack
    case TW_SR_GCALL_ACK:           // addressed generally, returned ack
    case TW_SR_ARB_LOST_SLA_ACK:    // lost arbitration, returned ack
    case TW_SR_ARB_LOST_GCALL_ACK:  // lost arbitration, returned ack
        // enter slave receiver mode
        bus->state = I2C_SRX;
        // indicate that rx buffer can be overwritten and ack
        bus->rxBuffer_index = 0;
        I2C_Reply(bus, 1);
        break;
    case TW_SR_DATA_ACK:        // data received, returned ack
    case TW_SR_GCALL_DATA_ACK:  // data received generally, returned ack
        // if there is still room in the rx buffer
        if (bus->rxBuffer_index < I2C_BUFFER_LENGTH)
        {
            // put byte in buffer and ack
            bus->rxBuffer[bus->rxBuffer_index++] = bus_register->_TWDR;
            I2C_Reply(bus, 1);
        }
        else
        {
            // otherwise nack
            I2C_Reply(bus, 0);
        }
        break;
    case TW_SR_STOP:  // stop or repeated start condition received
        // ack future responses and leave slave receiver state
        I2C_ReleaseBus(bus);
        // put a null char after data if there's room
        if (bus->rxBuffer_index < I2C_BUFFER_LENGTH)
        {
            bus->rxBuffer[bus->rxBuffer_index] = '\0';
        }
        // callback to user defined callback
        I2C_rxEventHandler(bus, bus->rxBuffer, bus->rxBuffer_index);
        // since we submit rx buffer to "wire" library, we can reset it
        bus->rxBuffer_index = 0;
        break;
    case TW_SR_DATA_NACK:        // data received, returned nack
    case TW_SR_GCALL_DATA_NACK:  // data received generally, returned nack
        // nack back at master
        I2C_Reply(bus, 0);
        break;

    // Slave Transmitter
    case TW_ST_SLA_ACK:           // addressed, returned ack
    case TW_ST_ARB_LOST_SLA_ACK:  // arbitration lost, returned ack
        // enter slave transmitter mode
        bus->state = I2C_STX;
        // ready the tx buffer index for iteration
        bus->txBuffer_index = 0;
        // set tx buffer length to be zero, to verify if user changes it
        bus->rxBuffer_lenght = 0;
        // request for txBuffer to be filled and length to be set
        // note: user must call twi_transmit(bytes, length) to do this
        I2C_txEventHandler(bus);
        // if they didn't change buffer & length, initialize it
        if (0 == bus->rxBuffer_lenght)
        {
            bus->rxBuffer_lenght = 1;
            bus->txBuffer[0] = 0x00;
        }
        // transmit first byte from buffer, fall
    case TW_ST_DATA_ACK:  // byte sent, ack returned
        // copy data to output register
        bus_register->_TWDR = bus->txBuffer[bus->txBuffer_index++];
        // if there is more to send, ack, otherwise nack
        if (bus->txBuffer_index < bus->rxBuffer_lenght)
        {
            I2C_Reply(bus, 1);
        }
        else
        {
            I2C_Reply(bus, 0);
        }
        break;
    case TW_ST_DATA_NACK:  // received nack, we are done
    case TW_ST_LAST_DATA:  // received ack, but we are done already!
        // ack future responses
        I2C_Reply(bus, 1);
        // leave slave receiver state
        bus->state = I2C_READY;
        break;

    // All
    case TW_NO_INFO:  // no state information
        break;
    case TW_BUS_ERROR:  // bus error, illegal stop/start
        bus->error = TW_BUS_ERROR;
        I2C_Stop(bus);
        break;
    }
}

#undef I2C_DEFAULT_FLAGS
#undef I2C_FRECUENCY_CALC
