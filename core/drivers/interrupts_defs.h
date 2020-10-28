/**
 * @file interrupts_defs.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Contains definitions for interruptions drivers
 * @date 2020-10-25
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_INTERRUPTS_DEFS_H)
#define __TITAN_DRIVERS_INTERRUPTS_DEFS_H

#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    /**
 * @brief Hardware interruptions control register AVR
 * 
 */
    struct HW_INT_CtrlRegister_t
    {
        __IO BaseType_t INT0_type : 2;
        __IO BaseType_t INT1_type : 2;
        __IO BaseType_t RESERVED : 4;
    };

    /**
 * @brief Hardware interrupt handler
 * 
 */
    struct HWInterrupt_Handler_t
    {
        /**
         * @brief Pin allocated
         * 
         */
        uint8_t pin;

        /**
         * @brief ISR Call with params
         * 
         */
        void (*_isrCall)(void *params);

        /**
         * @brief Params for the ISR call
         * 
         */
        void *params;
        /**
         * @brief Counter of call num
         * 
         */
        uint32_t __isr_count;
        /**
         * @brief ISR Vector id table
         * 
         */
        uint8_t __vector_num;
    };

    /**
 * @brief Software interrupt handler
 * 
 */
    struct SWInterrupt_Handler_t
    {
        /**
         * @brief ISR Call with params
         * 
         */
        void (*_isrCall)(void *params);

        /**
         * @brief Params for the ISR call
         * 
         */
        void *params;
        /**
         * @brief Counter of call num
         * 
         */
        uint32_t __isr_count;
        /**
         * @brief ISR Vector id table
         * 
         */
        uint8_t __vector_num;
    };

    typedef struct HW_INT_CtrlRegister_t HW_INT_CtrlRegister_t;
    typedef struct HWInterrupt_Handler_t HWInterrupt_Handler_t;
    typedef struct SWInterrupt_Handler_t SWInterrupt_Handler_t;

    /**
     * @brief When a software interrupt occurs calls the interrupt wrapper to redirec to the ISR Function
     * 
     * @param __vector_num Vector ID Table
     */
    extern void sw_isr_wrapper(uint8_t __vector_num);
    
    /**
     * @brief When a hardware interrupt occurs calls the interrupt wrapper to redirec to the ISR Function
     * 
     * @param __vector_num Vector ID Table
     */
    extern void hw_isr_wrapper(uint8_t __vector_num);
    
    /**
     * @brief Transforms a Vector id into a index of the software interrupt handler table
     * 
     * @param __vector_num Vector ID Table
     */
    extern uint8_t index_isr_vector(uint8_t __vector_num);
    
    /**
     * @brief Transforms a Vector id into a index of the hardware interrupt handler table
     * 
     * @param __vector_num Vector ID Table
     */
    extern uint8_t index_hw_isr_vector(uint8_t __vector_num);

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_INTERRUPTS_DEFS_H
