#if !defined(__TITAN_DRIVERS_INTERRUPTS_H)
#define __TITAN_DRIVERS_INTERRUPTS_H

#include <avr/interrupt.h>

#include "interrupts_defs.h"
#include "platform.h"

/**
 * @brief Macro to enable interruptions
 * this calls "sei" inbuild macro
 * 
 */
#define ISR_enable_interrrupts() sei()

/**
 * @brief Macro to disable interruptions
 * this calls "cli" inbuild macro
 * 
 */
#define ISR_disable_interrrupts() cli()

/**
 * @brief Hardware ISR Call when input is LOW 
 * 
 */
#define ISR_ON_LOW 0b00

/**
 * @brief Hardware ISR Call when input changes
 * 
 */
#define ISR_ON_ANY 0b01

/**
 * @brief Hardware ISR Call when input is falling from HIGH to LOW
 * 
 */
#define ISR_ON_FALLING 0b10

/**
 * @brief Hardware ISR Call when input is falling from LOW to HIGH
 * 
 */
#define ISR_ON_RISING 0b11

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    /**
     * @brief Transforms an VectorID into a string
     * 
     * @param __vec_num Vector ID
     * @return const char* Name of the vector in string
     */
    extern const char *ISR_VectorNumName(uint8_t __vec_num);
    /**
     * @brief Transforms a pin id into a hardware interrupt handler
     * 
     * @param pin Pin where interruption is allocated
     * @return HWInterrupt_Handler_t* A ref to the hardware interrupt handler
     */
    extern HWInterrupt_Handler_t *ISR_PinToHandler(uint8_t pin);

    /**
     * @brief Disables ISR calls from a specific pin
     * 
     * @param pin Pin to disable interrupts
     */
    extern void ISR_hw_deinit(uint8_t pin);

    /**
     * @brief Enables ISR calls from a specific pin
     * 
     * @param pin Pin to enable interrupts
     */
    extern void ISR_hw_init(uint8_t pin, uint8_t mode);

    /**
     * @brief Initializes an ISR routine for a hardware interrupt
     * 
     * @param pin_num Pin where the interrupt is set
     * @param isr_call Function to be call when the interrupt is triggered
     * @param params Params for the ISR Call (can be NULL if params is not needed)
     * @param isrMode Represents the ISR mode
     */
    void ISR_hw_attach(uint8_t pin_num, void (*isr_call)(void *params), void *params, uint8_t isrMode);

    /**
     * @brief Deinitializes an ISR routine from a hardware interrupt
     * 
     * @param pin_num Pin where is interrupt is unset
     */
    void ISR_hw_deattach(uint8_t pin_num);

    /**
     * @brief Initializes an ISR routine for a software interrupt
     * 
     * @param __vec_num VectorID to attach the interrupt
     * @param isr_call Function to be call when the interrupt is triggered
     * @param params Params for the ISR Call (can be NULL if params is not needed)
     */
    void ISR_sw_attach(uint8_t __vec_num, void (*isr_call)(void *params), void *params);

    /**
     * @brief Deinitializes an ISR routine from a software interrupt
     * 
     * @param __vec_num VectorID to disable
     */
    void ISR_sw_deattach(uint8_t __vec_num);

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_INTERRUPTS_H
