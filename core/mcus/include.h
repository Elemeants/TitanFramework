/**
 * @file include.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Includes the microcontroller header for each target
 * @date 2020-10-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_MCU_INCLUDE_H)
#define __TITAN_MCU_INCLUDE_H

#ifdef __AVR_ATmega328P__
#include "mcus/atmega328p/mcu_m328p.h"
#elif __AVR_ATmega32__
#include "mcus/atmega32/mcu_m32.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus
    /**
 * @brief Vector of GPIO microcontroller specific
 * 
 */
    extern GPIO_Def_t gpio_pins[NO_GPIO_PIN];
    /**
 * @brief Vector of hardware interrupt handlers microcontroller specific
 * 
 */
    extern HWInterrupt_Handler_t hw_isr_vectors[NO_HW_INTERRUPTS];
    /**
 * @brief Vector of software interrupt handlers microcontroller specific
 * 
 */
    extern SWInterrupt_Handler_t sw_isr_vectors[NO_SW_INTERRUPTS];
#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_MCU_INCLUDE_H
