#include "pin_wiring.h"

#define __GPIO_DEF(__port, __pin, __type)                         \
    {                                                             \
        .port = __port, .no_pin = __pin, .gpio_type.mask = __type \
    }

// Arduino boards compatibility constants
GPIO_Def_t gpio_pins[NO_DIGITAL_GPIO_PIN] = {
    __GPIO_DEF(GPIOD, 0, GPIO_GENERIC | GPIO_UART),                  // Digital 0 - RX UART
    __GPIO_DEF(GPIOD, 1, GPIO_GENERIC | GPIO_UART),                  // Digital 1 - TX UART
    __GPIO_DEF(GPIOD, 2, GPIO_GENERIC | GPIO_INTERRUPT),             // Digital 2 - INT0
    __GPIO_DEF(GPIOD, 3, GPIO_GENERIC | GPIO_INTERRUPT | GPIO_PWM),  // Digital 3 - INT1 - PWM
    __GPIO_DEF(GPIOD, 4, GPIO_GENERIC),                              // Digital 4
    __GPIO_DEF(GPIOD, 5, GPIO_GENERIC),                              // Digital 5 - PWM
    __GPIO_DEF(GPIOD, 6, GPIO_GENERIC | GPIO_PWM),                   // Digital 6 - PWM
    __GPIO_DEF(GPIOD, 7, GPIO_GENERIC),                              // Digital 7

    __GPIO_DEF(GPIOB, 0, GPIO_GENERIC),                        // Digital 8
    __GPIO_DEF(GPIOB, 1, GPIO_GENERIC | GPIO_PWM),             // Digital 9 - PWM
    __GPIO_DEF(GPIOB, 2, GPIO_GENERIC | GPIO_PWM | GPIO_SPI),  // Digital 10 - PWM - SS
    __GPIO_DEF(GPIOB, 3, GPIO_GENERIC | GPIO_PWM | GPIO_SPI),  // Digital 11 - MOSI
    __GPIO_DEF(GPIOB, 4, GPIO_GENERIC | GPIO_SPI),             // Digital 12 - MISO
    __GPIO_DEF(GPIOB, 6, GPIO_GENERIC | GPIO_SPI),             // Digital 13 - SCK

    __GPIO_DEF(GPIOC, 0, GPIO_GENERIC | GPIO_ADC),  // Analog 0 - Digital 14
    __GPIO_DEF(GPIOC, 1, GPIO_GENERIC | GPIO_ADC),  // Analog 1 - Digital 15
    __GPIO_DEF(GPIOC, 2, GPIO_GENERIC | GPIO_ADC),  // Analog 2 - Digital 16
    __GPIO_DEF(GPIOC, 3, GPIO_GENERIC | GPIO_ADC),  // Analog 3 - Digital 17

    __GPIO_DEF(GPIOC, 4, GPIO_GENERIC | GPIO_ADC | GPIO_I2C),  // Analog 4 - Digital 18 - SDA
    __GPIO_DEF(GPIOC, 5, GPIO_GENERIC | GPIO_ADC | GPIO_I2C),  // Analog 5 - Digital 19 - SCL
};

#undef __GPIO_DEF