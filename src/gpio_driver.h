#if !defined(GPIO_DRIVER_H)
#define GPIO_DRIVER_H

#include "portable.h"
#include <avr/io.h>

typedef struct
{
    volatile BaseType_t pin;
    volatile BaseType_t ddr;
    volatile BaseType_t port;
} PORT_RefControl_t;

#ifdef PORTA
#   define GPIOA (*(PORT_RefControl_t*)(&PORTA))
#endif
#ifdef PORTB
#   define GPIOB (*(PORT_RefControl_t*)(&PORTB))
#endif
#ifdef PORTC
#   define GPIOC (*(PORT_RefControl_t*)(&PORTC))
#endif
#ifdef PORTD
#   define GPIOD (*(PORT_RefControl_t*)(&PORTD))
#endif

extern void GPIO_Init(PORT_RefControl_t* port, BaseType_t ddr_set);
extern void GPIO_Write(PORT_RefControl_t* port, BaseType_t value);
extern void GPIO_WritePin(PORT_RefControl_t* port, BaseType_t pin, BaseType_t value);
extern BaseType_t GPIO_Read(PORT_RefControl_t* port);
extern BaseType_t GPIO_ReadPin(PORT_RefControl_t* port, BaseType_t pin);

#endif // GPIO_DRIVER_H
