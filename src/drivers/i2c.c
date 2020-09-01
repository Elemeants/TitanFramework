#include "i2c.h"

#include "wiring.h"
#include "gpio.h"
#include <assert.h>

#define I2C_DEFAULT_FLAGS (_BV(TWIE) | _BV(TWEN) | _BV(TWEA))
#define I2C_FRECUENCY_CALC(frec) (((F_CPU/frec) - 16U) / 2U)

void I2C_Init(I2C_BusHandler *bus)
{
    if(bus == NULL) { return; }

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
    if(bus == NULL) { return; }

    _clear_bits(bus->port->_TWCR.mask, I2C_DEFAULT_FLAGS);
    GPIO_DigitalWrite(I2C_SCL_PIN, LOW);
    GPIO_DigitalWrite(I2C_SDA_PIN, LOW);
}

void I2C_SetAddress(I2C_BusHandler *bus, uint8_t addr)
{
    if(bus == NULL) { return; }

    bus->port->_TWAR.slaveAddress = addr;
}

void I2C_SetFrequency(I2C_BusHandler *bus, uint32_t frec)
{
    if(bus == NULL || frec == 0) { return; }

    bus->port->_TWBR = I2C_FRECUENCY_CALC(frec);
}

uint8_t I2C_ReadFrom(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop)
{
    if(bus == NULL) { return 0x00; }

    return 0x00;
}

uint8_t I2C_WriteTo(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
    if(bus == NULL) { return 0x00; }

    return 0x00;
}

uint8_t I2C_Transmit(I2C_BusHandler *bus, const uint8_t *data, uint8_t length)
{
    if(bus == NULL) { return 0x00; }

    return 0x00;
}

void I2C_AttachSlaveRxEvent(I2C_BusHandler *bus, void (*function)(uint8_t *, int))
{
    if(bus == NULL) { return; }

    bus->rxEvent = function;
}

void I2C_AttachSlaveTxEvent(I2C_BusHandler *bus, void (*function)(void))
{
    if(bus == NULL) { return; }

    bus->txEvent = function;
}

void I2C_Reply(I2C_BusHandler *bus, uint8_t ack)
{
    if(bus == NULL) { return; }

    bus->port->_TWCR.tw_int = 0b1;
    if (ack) {
        bus->port->_TWCR.tw_en_ack = 0b1;
    }
}

void I2C_Stop(I2C_BusHandler *bus)
{
    if(bus == NULL) { return; }

    bus->port->_TWCR.tw_en_ack = 0b1;
    bus->port->_TWCR.tw_stop = 0b1;
    while (bus->port->_TWCR.tw_stop);
    bus->state = I2C_READY;
}

void I2C_ReleaseBus(I2C_BusHandler *bus)
{
    if(bus == NULL) { return; }

    _set_bits(bus->port->_TWCR.mask, I2C_DEFAULT_FLAGS | _BV(TWINT));
    bus->state = I2C_READY;
}

#undef I2C_DEFAULT_FLAGS
#undef I2C_FRECUENCY_CALC
