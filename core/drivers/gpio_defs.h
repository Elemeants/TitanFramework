/**
 * @file gpio_defs.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Contains definitions for GPIO driver
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_GPIO_DEFS_H)
#define __TITAN_DRIVERS_GPIO_DEFS_H

#include "platform.h"

// ------------------- MCU Gpio list --------------------

#ifdef PINA
#define GPIOA ((GPIO_Handler)(&PINA))
#endif
#ifdef PINB
#define GPIOB ((GPIO_Handler)(&PINB))
#endif
#ifdef PINC
#define GPIOC ((GPIO_Handler)(&PINC))
#endif
#ifdef PIND
#define GPIOD ((GPIO_Handler)(&PIND))
#endif
#ifdef PINE
#define GPIOD ((GPIO_Handler)(&PINE))
#endif
#ifdef PINF
#define GPIOD ((GPIO_Handler)(&PINF))
#endif
#ifdef PING
#define GPIOD ((GPIO_Handler)(&PING))
#endif
#ifdef PINH
#define GPIOD ((GPIO_Handler)(&PINH))
#endif
#ifdef PINI
#define GPIOD ((GPIO_Handler)(&PINI))
#endif

/**
 * @brief Bit flag GPIO as generic
 * 
 */
#define GPIO_GENERIC _BV(0)

/**
 * @brief Bit flag GPIO as interrupt
 * 
 */
#define GPIO_INTERRUPT _BV(1)

/**
 * @brief Bit flag GPIO as pwm
 * 
 */
#define GPIO_PWM _BV(2)

/**
 * @brief Bit flag GPIO as adc
 * 
 */
#define GPIO_ADC _BV(3)

/**
 * @brief Bit flag GPIO as i2c
 * 
 */
#define GPIO_I2C _BV(4)

/**
 * @brief Bit flag GPIO as spi
 * 
 */
#define GPIO_SPI _BV(5)

/**
 * @brief Bit flag GPIO as uart
 * 
 */
#define GPIO_UART _BV(6)

/**
 * @brief Checks if GPIO Pin is generic
 * 
 */
#define IS_GPIO_GENERIC(type) ((type).mask & GPIO_GENERIC)

/**
 * @brief Checks if GPIO Pin is interrupt
 * 
 */
#define IS_GPIO_INTERRUPT(type) ((type).mask & GPIO_INTERRUPT)

/**
 * @brief Checks if GPIO Pin is pwm
 * 
 */
#define IS_GPIO_PWM(type) ((type).mask & GPIO_PWM)

/**
 * @brief Checks if GPIO Pin is adc
 * 
 */
#define IS_GPIO_ADC(type) ((type).mask & GPIO_ADC)

/**
 * @brief Checks if GPIO Pin is i2c
 * 
 */
#define IS_GPIO_I2C(type) ((type).mask & GPIO_I2C)

/**
 * @brief Checks if GPIO Pin is spi
 * 
 */
#define IS_GPIO_SPI(type) ((type).mask & GPIO_SPI)

/**
 * @brief Checks if GPIO Pin is uart
 * 
 */
#define IS_GPIO_UART(type) ((type).mask & GPIO_UART)

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus
    /**
 * @brief GPIO Register structure
 * 
 */
    typedef struct
    {
        /**
     * @brief GPIO PIN read input register
     */
        __IO BaseType_t pin;

        /**
     * @brief GPIO DDR port config register
     */
        __IO BaseType_t ddr;

        /**
     * @brief GPIO PORT write config register
     */
        __IO BaseType_t port;
    } GPIO_RefControl_t;
    typedef __IO GPIO_RefControl_t *GPIO_Handler;

    /**
 * @brief GPIO Pin definition config
 * 
 */
    typedef struct
    {
        /**
     * @brief Port of the pin
     * 
     */
        GPIO_Handler port;
        /**
     * @brief Number of the pin
     * 
     */
        BaseType_t no_pin;

        /**
     * @brief GPIO Type register
     */
        union
        {
            struct
            {
                /**
             * @brief Generic digital IO
             */
                uint8_t isGeneric : 1;
                /**
             * @brief Digital interruption pin
             */
                uint8_t isInterrupt : 1;
                /**
             * @brief Digital PWM Output
             */
                uint8_t isPwm : 1;
                /**
             * @brief Analog input
             */
                uint8_t isAdc : 1;
                /**
             * @brief I2C Pin bus
             */
                uint8_t isI2c : 1;
                /**
             * @brief SPI Pin bus
             */
                uint8_t isSpi : 1;
                /**
             * @brief UART Pin bus
             */
                uint8_t isUart : 1;
                uint8_t _ : 1;
            };
            /**
         * @brief Type mask
         */
            uint8_t mask;
        } gpio_type;
    } GPIO_Def_t;

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_GPIO_DEFS_H
