#if !defined(HAL_DRIVER_DEFINES_H)
#define HAL_DRIVER_DEFINES_H

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

// ----------------------------- [Firmware] ------------------------------
#define FIRMWARE_VERSION "0.4.0"

// ----------------------------- [Platform] ------------------------------
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define __IO volatile
#define __I volatile const
#define __O volatile

#ifndef _BV
#define _BV(bit) (1 << bit)
#endif // ! _BV

#define _clear_bits(sfr, bits) ((sfr) &= ~(bits))
#define _set_bits(sfr, bits) ((sfr) |= (bits))

#define _clear_bit(sfr, bit) ((sfr) &= ~_BV((bit)))
#define _set_low(sfr) _clear_bit(sfr, 0)

#define _set_bit(sfr, bit) ((sfr) |= _BV((bit)))
#define _set_high(sfr) _set_bit(sfr, 0)

#define _mask_bit(sfr, bit) ((sfr)&_BV(bit))

#define PULL_UP 2
#define OUTPUT 1
#define INPUT 0

#define true 1
#define false 0

#define HIGH 1
#define LOW 0

typedef uint8_t BaseType_t;
typedef __IO BaseType_t *MemAddressType_t;

// ------------------------------- [GPIO] --------------------------------
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

#define GPIO_GENERIC _BV(0)
#define GPIO_INTERRUPT _BV(1)
#define GPIO_PWM _BV(2)
#define GPIO_ADC _BV(3)
#define GPIO_I2C _BV(4)
#define GPIO_SPI _BV(5)
#define GPIO_UART _BV(6)

#define IS_GPIO_GENERIC(type) ((type).mask & GPIO_GENERIC)
#define IS_GPIO_INTERRUPT(type) ((type).mask & GPIO_INTERRUPT)
#define IS_GPIO_PWM(type) ((type).mask & GPIO_PWM)
#define IS_GPIO_ADC(type) ((type).mask & GPIO_ADC)
#define IS_GPIO_I2C(type) ((type).mask & GPIO_I2C)
#define IS_GPIO_SPI(type) ((type).mask & GPIO_SPI)
#define IS_GPIO_UART(type) ((type).mask & GPIO_UART)

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
    union {
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

// -------------------------------- [I2C] --------------------------------

/**
 * @brief AVR I2C Register structure
 * 
 */
typedef struct
{
    /**
     * @brief TWI Bit rate register
     */
    __IO uint8_t _TWBR;

    /**
     * @brief TWI Status register
     */
    __IO union {
        struct
        {
            /**
             * @brief Clock prescaler
             */
            __IO uint8_t prescaler : 2;
            __I uint8_t RESERVED : 1;
            /**
             * @brief Status register
             */
            __I uint8_t status : 5;
        };
        /**
         * @brief Register mask
         */
        __IO uint8_t mask;
    } _TWSR;

    /**
     * @brief TWI Address register
     */
    __IO union {
        struct
        {
            /**
             * @brief TWI General call recognition enable bit
             */
            __IO uint8_t generalCallEnabled : 1;

            /**
             * @brief TWI slave address register
             */
            __IO uint8_t slaveAddress : 7;
        };
        /**
         * @brief Register mask
         */
        __IO uint8_t mask;
    } _TWAR;

    /**
     * @brief TWI Address register
     */
    __IO uint8_t _TWDR;

    /**
     * @brief TWI General call recognition enable bit
     */
    __IO union {
        struct
        {
            /**
             * @brief TWI General call recognition enable bit
             */
            __IO uint8_t twie : 1;
            __I uint8_t RESERVED : 1;
            /**
             * @brief TWI Enable
             */
            __IO uint8_t twi_en : 1;
            /**
             * @brief TWI Write Collision Flag
             */
            __I uint8_t twwc : 1;
            /**
             * @brief  TWI STOP Condition Bit
             */
            __IO uint8_t tw_stop : 1;
            /**
             * @brief TWI START Condition Bit
             */
            __IO uint8_t tw_start : 1;
            /**
             * @brief TWI Enable Acknowledge Bit
             */
            __IO uint8_t tw_en_ack : 1;
            /**
             * @brief TWI Interrupt Flag
             */
            __IO uint8_t tw_int : 1;
        };
        /**
         * @brief Register mask
         */
        __IO uint8_t mask;
    } _TWCR;

    /**
     * @brief TWI Mask Address register
     */
    __IO union {
        struct
        {
            __IO uint8_t RESERVED : 1;

            /**
             * @brief TWI mask address register
             */
            __IO uint8_t maskAddress : 7;
        };
        /**
         * @brief Register mask
         */
        __IO uint8_t mask;
    } _TWAMR;
} TWI_RefControl_t;
typedef __IO TWI_RefControl_t *TWI_Handler;

// ----------------------------- [INTERRUPT] ----------------------------

typedef struct
{
    __IO BaseType_t INT0_type : 2;
    __IO BaseType_t INT1_type : 2;
    __IO BaseType_t RESERVED : 4;
} HW_INT_CtrlRegister_t;

typedef struct
{
    uint8_t pin;
    void (*_isrCall)(void *params);

    void *params;
    uint32_t __isr_count;
    uint8_t __vector_num;
} HWInterrupt_Handler_t;

typedef struct
{
    void (*_isrCall)(void *params);

    void *params;
    uint32_t __isr_count;
    uint8_t __vector_num;
} SWInterrupt_Handler_t;

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif // HAL_DRIVER_DEFINES_H
