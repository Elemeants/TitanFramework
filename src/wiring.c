#include "wiring.h"

#define __GPIO_DEF(__port, __pin, __type)                         \
    {                                                             \
        .port = __port, .no_pin = __pin, .gpio_type.mask = __type \
    }

// Arduino boards compatibility constants
GPIO_Def_t gpio_pins[NO_DIGITAL_GPIO_PIN] = {
    __GPIO_DEF(GPIOD, 0, GPIO_GENERIC | GPIO_UART),                 // Digital 0 - RX UART
    __GPIO_DEF(GPIOD, 1, GPIO_GENERIC | GPIO_UART),                 // Digital 1 - TX UART
    __GPIO_DEF(GPIOD, 2, GPIO_GENERIC | GPIO_INTERRUPT),            // Digital 2 - INT0
    __GPIO_DEF(GPIOD, 3, GPIO_GENERIC | GPIO_INTERRUPT | GPIO_PWM), // Digital 3 - INT1 - PWM
    __GPIO_DEF(GPIOD, 4, GPIO_GENERIC),                             // Digital 4
    __GPIO_DEF(GPIOD, 5, GPIO_GENERIC),                             // Digital 5 - PWM
    __GPIO_DEF(GPIOD, 6, GPIO_GENERIC | GPIO_PWM),                  // Digital 6 - PWM
    __GPIO_DEF(GPIOD, 7, GPIO_GENERIC),                             // Digital 7

    __GPIO_DEF(GPIOB, 0, GPIO_GENERIC),                       // Digital 8
    __GPIO_DEF(GPIOB, 1, GPIO_GENERIC | GPIO_PWM),            // Digital 9 - PWM
    __GPIO_DEF(GPIOB, 2, GPIO_GENERIC | GPIO_PWM | GPIO_SPI), // Digital 10 - PWM - SS
    __GPIO_DEF(GPIOB, 3, GPIO_GENERIC | GPIO_PWM | GPIO_SPI), // Digital 11 - MOSI
    __GPIO_DEF(GPIOB, 4, GPIO_GENERIC | GPIO_SPI),            // Digital 12 - MISO
    __GPIO_DEF(GPIOB, 6, GPIO_GENERIC | GPIO_SPI),            // Digital 13 - SCK

    __GPIO_DEF(GPIOC, 0, GPIO_GENERIC | GPIO_ADC), // Analog 0 - Digital 14
    __GPIO_DEF(GPIOC, 1, GPIO_GENERIC | GPIO_ADC), // Analog 1 - Digital 15
    __GPIO_DEF(GPIOC, 2, GPIO_GENERIC | GPIO_ADC), // Analog 2 - Digital 16
    __GPIO_DEF(GPIOC, 3, GPIO_GENERIC | GPIO_ADC), // Analog 3 - Digital 17

    __GPIO_DEF(GPIOC, 4, GPIO_GENERIC | GPIO_ADC | GPIO_I2C), // Analog 4 - Digital 18 - SDA
    __GPIO_DEF(GPIOC, 5, GPIO_GENERIC | GPIO_ADC | GPIO_I2C), // Analog 5 - Digital 19 - SCL
};

#undef __GPIO_DEF

void I2CBus_Init()
{
    I2C_Init(&I2CBus);
}
void I2CBus_DeInit()
{
    I2C_DeInit(&I2CBus);
}
void I2CBus_SetAddress(uint8_t addr)
{
    I2C_SetAddress(&I2CBus, addr);
}
void I2CBus_SetFrequency(I2C_BusSpeed_e frec)
{
    I2C_SetFrequency(&I2CBus, frec);
}
uint8_t I2CBus_ReadFrom(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop)
{
    return I2C_ReadFrom(&I2CBus, address, data, length, sendStop);
}
uint8_t I2CBus_WriteTo(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
    return I2C_WriteTo(&I2CBus, address, data, length, wait, sendStop);
}
uint8_t I2CBus_Transmit(const uint8_t *data, uint8_t length)
{
    return I2C_Transmit(&I2CBus, data, length);
}
void I2CBus_AttachSlaveRxEvent(void (*function)(uint8_t *, int))
{
    I2C_AttachSlaveRxEvent(&I2CBus, function);
}
void I2CBus_AttachSlaveTxEvent(void (*function)(void))
{
    I2C_AttachSlaveTxEvent(&I2CBus, function);
}
void I2CBus_Reply(uint8_t ack)
{
    I2C_Reply(&I2CBus, ack);
}
void I2CBus_Stop()
{
    I2C_Stop(&I2CBus);
}
void I2CBus_ReleaseBus()
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
    .Init = I2CBus_Init,
    .DeInit = I2CBus_DeInit,
    .SetAddress = I2CBus_SetAddress,
    .SetFrequency = I2CBus_SetFrequency,
    .ReadFrom = I2CBus_ReadFrom,
    .WriteTo = I2CBus_WriteTo,
    .Transmit = I2CBus_Transmit,
    .AttachSlaveRxEvent = I2CBus_AttachSlaveRxEvent,
    .AttachSlaveTxEvent = I2CBus_AttachSlaveTxEvent,
    .Reply = I2CBus_Reply,
    .Stop = I2CBus_Stop,
    .ReleaseBus = I2CBus_ReleaseBus,
};

#undef __SW_INTERRUPT_DEF