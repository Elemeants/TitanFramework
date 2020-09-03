#if !defined(MCU_COMMON_MACROS_H)
#define MCU_COMMON_MACROS_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define __GPIO_DEF(__port, __pin, __type)                         \
    {                                                             \
        .port = __port, .no_pin = __pin, .gpio_type.mask = __type \
    }

#define __HW_INTERRUPT_DEF(__pin, __vector) \
    {                                       \
        .pin = __pin,                       \
        ._isrCall = NULL,                   \
        .__isr_count = 0,                   \
        .__vector_num = __vector,           \
        .params = NULL                      \
    }

#define __SW_INTERRUPT_DEF(__vector) \
    {                                \
        ._isrCall = NULL,            \
        .__isr_count = 0,            \
        .__vector_num = __vector     \
    }

#define ISR_Wrapper(__vector_num, __function)  \
    ISR(_VECTOR(__vector_num))        \
    {                                 \
        __function(__vector_num); \
    }

#endif  // MCU_COMMON_MACROS_H
