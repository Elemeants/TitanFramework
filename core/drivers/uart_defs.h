#if !defined(__TITAN_DRIVERS_UART_DEFS_H)
#define __TITAN_DRIVERS_UART_DEFS_H

#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

    struct USART_ControlRegisterA_t
    {
        __IO uint8_t multi_processor_flag : 1;
        __IO uint8_t double_speed : 1;
        __I uint8_t parity_error : 1;
        __I uint8_t data_overrun : 1;
        __I uint8_t frame_error : 1;
        __I uint8_t register_empty : 1;
        __IO uint8_t tx_completed : 1;
        __I uint8_t rx_completed : 1;
    };

    struct USART_ControlRegisterB_t
    {
        __IO uint8_t TXB8n : 1;
        __I uint8_t RXB8n : 1;
        __IO uint8_t char_size : 1;
        __IO uint8_t tx_enable : 1;
        __IO uint8_t rx_enable : 1;
        __IO uint8_t register_empty_isr_en : 1;
        __IO uint8_t rx_completed_isr_en : 1;
        __IO uint8_t tx_completed_isr_en : 1;
    };

    struct USART_ControlRegisterC_t
    {
        __IO uint8_t clk_polarity : 1;
        __IO uint8_t package_size : 2;
        __IO uint8_t stop_bit : 1;
        __IO uint8_t parity_mode : 2;
        __IO uint8_t usart_mode : 2;
    };

    typedef struct USART_ControlRegisterA_t USART_ControlRegisterA_t;
    typedef struct USART_ControlRegisterB_t USART_ControlRegisterB_t;
    typedef struct USART_ControlRegisterC_t USART_ControlRegisterC_t;

#define __USART_MODE_ASYNC 0b00
#define __USART_MODE_SYNC 0b01
#define __USART_MODE_MASTER_SPI 0b11

#define __USART_PARITY_MODE_DISABLED 0b00
#define __USART_PARITY_MODE_EVEN 0b10
#define __USART_PARITY_MODE_ODD 0b11

#define __USART_NUM_STOP_BITS_1 0b0
#define __USART_NUM_STOP_BITS_2 0b1

#define __USART_CLOCK_POLARITY_RISING 0b0
#define __USART_CLOCK_POLARITY_FALLING 0b1

#define __USART_CHAR_SIZE_5 0b000
#define __USART_CHAR_SIZE_6 0b001
#define __USART_CHAR_SIZE_7 0b010
#define __USART_CHAR_SIZE_8 0b011
#define __USART_CHAR_SIZE_9 0b111

#define __USART_UBBR_CALC(__baud, __factor) ((F_CPU / (__factor * __baud)) - 1)

#define __USART_UBRR_ASYNC_CALC(__baud) __USART_UBBR_CALC(__baud, 16)
#define __USART_UBRR_ASYNC_U2X_CALC(__baud) __USART_UBBR_CALC(__baud, 8)
#define __USART_UBRR_SYNC_CALC(__baud) __USART_UBBR_CALC(__baud, 2)

#define __USART_UBBR_BAUD(__ubbr, __factor) ((F_CPU / (__factor * (__ubbr + 1))))

#define __USART_UBRR_ASYNC_BAUD(__ubbr) __USART_UBBR_BAUD(__baud, 16)
#define __USART_UBRR_ASYNC_U2X_BAUD(__ubbr) __USART_UBBR_BAUD(__baud, 8)
#define __USART_UBRR_SYNC_BAUD(__ubbr) __USART_UBBR_BAUD(__baud, 2)

#define __USART_UBBR_ERROR(__ubbr, __factor, __expected_baud) (100.0F * (((float)__USART_UBBR_BAUD(__ubbr, __factor) / __expected_baud) - 1))

#define __USART_UBRR_ASYNC_ERROR(__ubbr, __expected_baud) __USART_UBBR_ERROR(__ubbr, 16, __expected_baud)
#define __USART_UBRR_ASYNC_U2X_ERROR(__ubbr, __expected_baud) __USART_UBBR_ERROR(__ubbr, 8, __expected_baud)
#define __USART_UBRR_SYNC_ERROR(__ubbr, __expected_baud) __USART_UBBR_ERROR(__ubbr, 8, __expected_baud)

#ifndef __USART_BUFFER_LENGTH
#define __USART_BUFFER_LENGTH 32
#endif

    struct USART_Handler_t
    {
        __IO USART_ControlRegisterA_t *CtrlRegA;
        __IO USART_ControlRegisterB_t *CtrlRegB;
        __IO USART_ControlRegisterC_t *CtrlRegC;
        __IO uint8_t *UBRR_L;
        __IO uint8_t *UBRR_H;
        __IO uint8_t *DataRegister;

        char rx_buffer[__USART_BUFFER_LENGTH];
    };
    typedef struct USART_Handler_t USART_Handler_t;

#ifdef __cplusplus
}
#endif

#endif  // __TITAN_DRIVERS_UART_DEFS_H
