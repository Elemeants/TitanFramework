#include "uart.h"

#include "mcus/include.h"
#include "utils/loop_utils.h"

#if __USART_1_ENABLED
// TODO: More ergonomic way to define this USART handlers
#if defined(__AVR_ATmega32__)
static USART_Handler_t USART_1 = {
    .CtrlRegA = (__IO USART_ControlRegisterA_t*)&UCSRA,
    .CtrlRegB = (__IO USART_ControlRegisterB_t*)&UCSRB,
    .CtrlRegC = (__IO USART_ControlRegisterC_t*)&UCSRC,
    .UBRR_L = (__IO uint8_t*)&UBRRL,
    .UBRR_H = (__IO uint8_t*)&UBRRH,
    .DataRegister = (__IO uint8_t*)&UDR,
    .rx_buffer = "",
};
#elif defined(__AVR_ATmega328P__)
static USART_Handler_t USART_1 = {
    .CtrlRegA = (__IO USART_ControlRegisterA_t*)&UCSR0A,
    .CtrlRegB = (__IO USART_ControlRegisterB_t*)&UCSR0B,
    .CtrlRegC = (__IO USART_ControlRegisterC_t*)&UCSR0C,
    .UBRR_L = (__IO uint8_t*)&UBRR0L,
    .UBRR_H = (__IO uint8_t*)&UBRR0H,
    .DataRegister = (__IO uint8_t*)&UDR0,
    .rx_buffer = "",
};
#endif
#endif
#if __USART_2_ENABLED  // TODO: Create USART 2 -> 4 Handlers
static USART_Handler_t USART_2;
#endif
#if __USART_3_ENABLED
static USART_Handler_t USART_3;
#endif
#if __USART_4_ENABLED
static USART_Handler_t USART_4;
#endif

static inline USART_Handler_t* USART_GetHandlerFromId(uint8_t usart_id)
{
    USART_Handler_t* usart = NULL;
    switch (usart_id)
    {
#if __USART_1_ENABLED
    case 1:
        usart = &USART_1;
        break;
#endif
#if __USART_2_ENABLED
    case 2:
        usart = &USART_2;
        break;
#endif
#if __USART_3_ENABLED
    case 3:
        usart = &USART_3;
        break;
#endif
#if __USART_4_ENABLED
    case 4:
        usart = &USART_4;
        break;
#endif
    }
    return usart;
}

static inline void USART_SetOptimizedBaudRate(uint8_t usart_id, uint32_t baudrate)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }

    uint8_t ubrr_a = __USART_UBRR_ASYNC_CALC(baudrate);
    float ubrr_a_err = __USART_UBRR_ASYNC_ERROR(ubrr_a, baudrate);
    uint8_t ubrr_b = __USART_UBRR_ASYNC_U2X_CALC(baudrate);
    float ubrr_b_err = __USART_UBRR_ASYNC_ERROR(ubrr_a, baudrate);

    uint8_t ubbr = 0;
    if (ubrr_b_err < ubrr_a_err)
    {
        usart->CtrlRegA->double_speed = 0b1;
        ubbr = ubrr_b;
    }
    else
    {
        ubbr = ubrr_a;
    }

    *usart->UBRR_L = ubbr & 0x00FF;
    *usart->UBRR_H = (ubbr & 0x0F00) >> 8;
}

void USART_Init(uint8_t usart_id, uint32_t baudrate)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }

    // 1-. Setting baudrate
    USART_SetOptimizedBaudRate(usart_id, baudrate);

    // 2-. Frame format
    USART_FrameLength(usart_id, __USART_DEFAULT_FRAMELEN);

    // 3-. Enable TX
    usart->CtrlRegB->tx_enable = 0b1;
    usart->CtrlRegB->rx_enable = 0b1;

    // TODO ->
    // 5-. Clear global interrupts flag with all interrupts disabled
}

void USART_FrameLength(uint8_t usart_id, uint8_t frame_length)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }
    // |--------|--------|--------|----------------|
    // | UCSZn2 | UCSZn1 | UCSZn0 | Character_Size |
    // |--------|--------|--------|----------------|
    // | 0      | 0      | 0      | 5-bit          |
    // |--------|--------|--------|----------------|
    // | 0      | 0      | 1      | 6-bit          |
    // |--------|--------|--------|----------------|
    // | 0      | 1      | 0      | 7-bit          |
    // |--------|--------|--------|----------------|
    // | 0      | 1      | 1      | 8-bit          |  -> Predefined frameformat
    // |--------|--------|--------|----------------|
    // | 1      | 0      | 0      | Reserved       |
    // |--------|--------|--------|----------------|
    // | 1      | 0      | 1      | Reserved       |
    // |--------|--------|--------|----------------|
    // | 1      | 1      | 0      | Reserved       |
    // |--------|--------|--------|----------------|
    // | 1      | 1      | 1      | 9-bit          |
    // |--------|--------|--------|----------------|

    switch (frame_length)
    {
    case 5U:
        usart->CtrlRegB->char_size = 0b0;
        usart->CtrlRegC->package_size = 0b00;
        break;
    case 6U:
        usart->CtrlRegB->char_size = 0b0;
        usart->CtrlRegC->package_size = 0b01;
        break;
    case 7U:
        usart->CtrlRegB->char_size = 0b0;
        usart->CtrlRegC->package_size = 0b10;
        break;
    case 8U:
        usart->CtrlRegB->char_size = 0b0;
        usart->CtrlRegC->package_size = 0b11;
        break;
    case 9U:
        usart->CtrlRegB->char_size = 0b1;
        usart->CtrlRegC->package_size = 0b11;
        break;
    default:
        break;
    }
}

void USART_ParityMode(uint8_t usart_id, uint8_t mode)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }
    usart->CtrlRegC->parity_mode = mode;
}

void USART_StopBits(uint8_t usart_id, uint8_t stop)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }
    usart->CtrlRegC->stop_bit = stop;
}

void USART_Mode(uint8_t usart_id, uint8_t mode)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }
    usart->CtrlRegC->usart_mode = mode;
}

static inline void USART_FastWriteByte(USART_Handler_t* usart, uint8_t byte)
{
    while (!usart->CtrlRegA->register_empty)
        ;
    *usart->DataRegister = byte;
}

void USART_WriteByte(uint8_t usart_id, uint8_t byte)
{
    // TODO: Implement write 9bits
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }
    while (!usart->CtrlRegA->register_empty)
        ;
    *usart->DataRegister = byte;
}

void USART_WriteBuffer(uint8_t usart_id, void* buffer, uint16_t length)
{
    USART_Handler_t* usart = USART_GetHandlerFromId(usart_id);
    // If usart handler by id not exist
    if (!usart)
    {
        return;
    }
    pinMode(D3, OUTPUT);
    uint8_t* ptr = (uint8_t*)buffer;
    for (uint8_t i = 0; i < length; i++)
    {
        digitalWrite(D3, HIGH);
        USART_FastWriteByte(usart, *ptr);
        ptr++;
        digitalWrite(D3, LOW);
    }
}