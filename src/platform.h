#if !defined(HAL_DRIVER_DEFINES_H)
#define HAL_DRIVER_DEFINES_H

#include <stdint.h>

// General config

#define __IO volatile
#define __I  volatile const
#define __O  volatile

#ifndef  _BV
#define _BV(x) (1 << x)
#endif // ! _BV

#define _clear_bit(byte, bit) (byte) & ((byte) & ~(1 << pin))
#define _set_bit(byte, bit) (byte) | _BV(bit)

typedef uint8_t BaseType_t;
typedef __IO BaseType_t *MemAddressType_t;
typedef __IO BaseType_t RegisterType_t;

// GPIO config

typedef struct
{
    RegisterType_t pin;
    RegisterType_t ddr;
    RegisterType_t port;
} PORT_RefControl_t;

#ifdef PORTA
#   define GPIOA ((PORT_RefControl_t*)(&PORTA))
#endif
#ifdef PORTB
#   define GPIOB ((PORT_RefControl_t*)(&PORTB))
#endif
#ifdef PORTC
#   define GPIOC ((PORT_RefControl_t*)(&PORTC))
#endif
#ifdef PORTD
#   define GPIOD ((PORT_RefControl_t*)(&PORTD))
#endif

// GPIO config
typedef struct
{
    RegisterType_t _TWBR;
    RegisterType_t _TWSR;
    RegisterType_t _TWAR;
    RegisterType_t _TWDR;
    RegisterType_t _TWCR;
    RegisterType_t _TWAMR;
} TWI_RefControl_t;

#define TWI ((TWI_RefControl_t)(0xB8))

#endif // HAL_DRIVER_DEFINES_H
