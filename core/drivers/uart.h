#if !defined(__TITAN_DRIVERS_UART_H)
#define __TITAN_DRIVERS_UART_H

#include "uart_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define __USART_DEFAULT_FRAMELEN 8U

    extern void USART_Init(uint8_t usart_id, uint32_t baudrate);
    extern void USART_Mode(uint8_t usart_id, uint8_t mode);
    extern void USART_ParityMode(uint8_t usart_id, uint8_t mode);
    extern void USART_StopBits(uint8_t usart_id, uint8_t stop);
    extern void USART_FrameLength(uint8_t usart_id, uint8_t frame_length);
    extern void USART_WriteByte(uint8_t usart_id, uint8_t byte);
    extern void USART_WriteBuffer(uint8_t usart_id, void *buffer, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif  // __TITAN_DRIVERS_UART_H
