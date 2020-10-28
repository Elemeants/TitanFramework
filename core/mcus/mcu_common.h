/**
 * @file mcu_common.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Common include header for microcontroller specific header
 * @date 2020-10-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_MCU_COMMON_HEADER_H)
#define __TITAN_MCU_COMMON_HEADER_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <utils/loop_utils.h>

#include "drivers/delay.h"
#include "drivers/gpio.h"
#include "drivers/i2c.h"
#include "drivers/interrupts.h"
#include "platform.h"

/**
 * @brief Macro for GPIO definitions
 * 
 */
#define __GPIO_DEF(__port, __pin, __type)                         \
    {                                                             \
        .port = __port, .no_pin = __pin, .gpio_type.mask = __type \
    }

/**
 * @brief Macro for hardware interrupt handler definitions
 * 
 */
#define __HW_INTERRUPT_DEF(__pin, __vector) \
    {                                       \
        .pin = __pin,                       \
        ._isrCall = NULL,                   \
        .__isr_count = 0,                   \
        .__vector_num = __vector,           \
        .params = NULL                      \
    }

/**
 * @brief Macro for software interrupt handler definitions
 * 
 */
#define __SW_INTERRUPT_DEF(__vector) \
    {                                \
        ._isrCall = NULL,            \
        .__isr_count = 0,            \
        .__vector_num = __vector     \
    }

/**
 * @brief Macro for ISR interrupt wrapper definitions
 * 
 */
#define ISR_Wrapper(__vector_num, __function) \
    ISR(_VECTOR(__vector_num))                \
    {                                         \
        __function(__vector_num);             \
    }

#endif  // __TITAN_MCU_COMMON_HEADER_H
