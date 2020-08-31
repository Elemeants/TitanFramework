#include "i2c.h"

#include "pin_wiring.h"
#include "gpio.h"

#if EN_TWI0
static void _I2C0_Init()
{
    I2C_Init(&I2CBus);
}
static void _I2C0_DeInit()
{
    I2C_DeInit(&I2CBus);
}
static void _I2C0_SetAddress(uint8_t addr)
{
    I2C_SetAddress(&I2CBus, addr);
}
static void _I2C0_SetFrequency(I2C_BusSpeed_e frec)
{
    I2C_SetFrequency(&I2CBus, frec);
}
static uint8_t _I2C0_ReadFrom(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop)
{
    return I2C_ReadFrom(&I2CBus, address, data, length, sendStop);
}
static uint8_t _I2C0_WriteTo(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
    return I2C_WriteTo(&I2CBus, address, data, length, wait, sendStop);
}
static uint8_t _I2C0_Transmit(const uint8_t *data, uint8_t length)
{
    return I2C_Transmit(&I2CBus, data, length);
}
static void _I2C0_AttachSlaveRxEvent(void (*function)(uint8_t *, int))
{
    I2C_AttachSlaveRxEvent(&I2CBus, function);
}
static void _I2C0_AttachSlaveTxEvent(void (*function)(void))
{
    I2C_AttachSlaveTxEvent(&I2CBus, function);
}
static void _I2C0_Reply(uint8_t ack)
{
    I2C_Reply(&I2CBus, ack);
}
static void _I2C0_Stop()
{
    I2C_Stop(&I2CBus);
}
static void _I2C0_ReleaseBus()
{
    I2C_ReleaseBus(&I2CBus);
}

I2C_BusHandler I2CBus = {
    .port = TWI0_Register,
    .state = 0b00,
    .send_stop = 0b0,
    .in_rep_start = 0b0,
    .error = 0b0,
    .sla_rw.raw = 0x00,
    .Init = _I2C0_Init,
    .DeInit = _I2C0_DeInit,
    .SetAddress = _I2C0_SetAddress,
    .SetFrequency = _I2C0_SetFrequency,
    .ReadFrom = _I2C0_ReadFrom,
    .WriteTo = _I2C0_WriteTo,
    .Transmit = _I2C0_Transmit,
    .AttachSlaveRxEvent = _I2C0_AttachSlaveRxEvent,
    .AttachSlaveTxEvent = _I2C0_AttachSlaveTxEvent,
    .Reply = _I2C0_Reply,
    .Stop = _I2C0_Stop,
    .ReleaseBus = _I2C0_ReleaseBus,
};
#endif

void I2C_Init(I2C_BusHandler *bus)
{
    bus->state = I2C_READY;
    bus->send_stop = 1;
    bus->in_rep_start = 1;

    GPIO_PinMode(I2C_SCL_PIN, PULL_UP);
    GPIO_PinMode(I2C_SDA_PIN, PULL_UP);

    bus->port->_TWSR.prescaler = 0b00;
    bus->port->_TWBR = ((F_CPU/I2C_BUS_FREQ) - 16) / 2;
}

void I2C_DeInit(I2C_BusHandler *bus)
{
}

void I2C_SetAddress(I2C_BusHandler *bus, uint8_t addr)
{
}

void I2C_SetFrequency(I2C_BusHandler *bus, I2C_BusSpeed_e frec)
{
}

uint8_t I2C_ReadFrom(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop)
{
    return 0x00;
}

uint8_t I2C_WriteTo(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
    return 0x00;
}

uint8_t I2C_Transmit(I2C_BusHandler *bus, const uint8_t *data, uint8_t length)
{
    return 0x00;
}

void I2C_AttachSlaveRxEvent(I2C_BusHandler *bus, void (*function)(uint8_t *, int))
{
}

void I2C_AttachSlaveTxEvent(I2C_BusHandler *bus, void (*function)(void))
{
}

void I2C_Reply(I2C_BusHandler *bus, uint8_t ack)
{
}

void I2C_Stop(I2C_BusHandler *bus)
{
}

void I2C_ReleaseBus(I2C_BusHandler *bus)
{
}
