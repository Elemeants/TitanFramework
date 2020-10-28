/**
 * @file gpio_high_level.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief This header file contains a set of functions for high level GPIO Pin operations
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_GPIO_HIGH_LEVEL_H)
#define __TITAN_DRIVERS_GPIO_HIGH_LEVEL_H

#include "gpio_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    /**
 * @brief 
 * 
 * @param pin 
 * @param mode 
 */
    void pinMode(uint8_t pin, uint8_t mode);

    /**
 * @brief 
 * 
 * @param pin 
 * @param value 
 */
    void digitalWrite(uint8_t pin, uint8_t value);

    /**
 * @brief 
 * 
 * @param pin 
 * @return uint8_t 
 */
    uint8_t digitalRead(uint8_t pin);

    /**
 * @brief 
 * 
 * @param gpio 
 */
    void digitalToggle(uint8_t gpio);

    /**
 * @brief 
 * 
 * @param pin 
 * @param value 
 */
    void analogWrite(uint8_t pin, uint16_t value);

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_GPIO_HIGH_LEVEL_H
