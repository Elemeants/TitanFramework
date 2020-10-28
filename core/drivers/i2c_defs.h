/**
 * @file i2c_defs.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Includes definitions for I2C driver
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_I2C_DEFS_H)
#define __TITAN_DRIVERS_I2C_DEFS_H

#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus
    /**
 * @brief AVR I2C Register structure
 * 
 */
    struct TWI_RefControl_t
    {
        /**
     * @brief TWI Bit rate register
     */
        __IO uint8_t _TWBR;

        /**
     * @brief TWI Status register
     */
        __IO union
        {
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
        __IO union
        {
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
        __IO union
        {
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
        __IO union
        {
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
    };

    typedef struct TWI_RefControl_t TWI_RefControl_t;

    /**
     * @brief A pointer to a TWI_RefControl_t
     * 
     */
    typedef __IO TWI_RefControl_t *TWI_Handler;

// Exists the I2C Control register TWBR so make an TWI Handler
#ifdef TWBR
#define TWI0_Register ((TWI_Handler)(&TWBR))
#endif  // TWBR

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_I2C_DEFS_H
