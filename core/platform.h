#if !defined(__TITAN_PLATFORM_H)
#define __TITAN_PLATFORM_H

#include <avr/io.h>
#include <stddef.h>
#include <stdint.h>

// ----------------------------- [Firmware] ------------------------------
#define FIRMWARE_VERSION "0.5.0"

// ----------------------------- [Platform] ------------------------------
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define __IO volatile
#define __I volatile const
#define __O volatile

#ifndef _BV
#define _BV(bit) (1 << bit)
#endif  // ! _BV

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

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    typedef uint8_t BaseType_t;
    typedef __IO BaseType_t *MemAddressType_t;

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_PLATFORM_H
