/**
 * @file gpio_low_level.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief This header file contains a set of functions for low level GPIO operation
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_GPIO_LOW_LEVEL_H)
#define __TITAN_DRIVERS_GPIO_LOW_LEVEL_H

#include "gpio_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    /**
 * @brief Initializes a GPIO peripheral raw, assigning the DDR value directly 
 * 
 * @param port GPIO(PORT) where would be assigned the DDR value
 * @param ddr_set Represents the value to be assigned to the PORT as 0 for 
 * input and 1 for outputs, for example if you want to set all port as output
 * the value in an architecture of 8bits should be 0xFF -> 0b11111111
 */
    void GPIO_HAL_PortInit(GPIO_Handler port, BaseType_t ddr_set);

    /**
 * @brief Writes a value to an expecifict GPIO Port
 * 
 * @param port 
 * @param value 
 */
    void GPIO_HAL_PortWrite(GPIO_Handler port, BaseType_t value);

    /**
 * @brief 
 * 
 * @param port 
 * @return BaseType_t 
 */
    BaseType_t GPIO_HAL_PortRead(GPIO_Handler port);

    /**
 * @brief Initializes a GPIO Pin as some kind of status for example: INPUT, OUTPUT or PULL_UP
 * 
 * @param port GPIO(PORT) where the pin would be configurated
 * @param pin No. of the pin where the higher value is the MSB
 * @param status Pin status for example: INPUT, OUTPUT or PULL_UP
 */
    void GPIO_HAL_PinInit(GPIO_Handler port, BaseType_t pin, uint8_t status);

    /**
 * @brief 
 * 
 * @param port 
 * @param pin 
 * @param value 
 */
    void GPIO_HAL_PinWrite(GPIO_Handler port, BaseType_t pin, BaseType_t value);

    /**
 * @brief 
 * 
 * @param port 
 * @param pin 
 * @return uint8_t 
 */
    uint8_t GPIO_HAL_PinRead(GPIO_Handler port, BaseType_t pin);

    /**
 * @brief 
 * 
 * @param port 
 * @param pin 
 */
    void GPIO_HAL_PinToggle(GPIO_Handler port, BaseType_t pin);

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_GPIO_LOW_LEVEL_H
