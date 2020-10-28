/**
 * @file gpio_mid_level.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief This header file contains a set of functions for mid level GPIO operation
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_GPIO_MID_LEVEL_H)
#define __TITAN_DRIVERS_GPIO_MID_LEVEL_H

#include "gpio_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    /**
 * @brief 
 * 
 * @param gpio 
 * @param mode 
 */
    void GPIO_PinInit(GPIO_Def_t gpio, uint8_t mode);

    /**
 * @brief 
 * 
 * @param gpio 
 * @param value 
 */
    void GPIO_PinWrite(GPIO_Def_t gpio, uint8_t value);

    /**
 * @brief 
 * 
 * @param gpio 
 * @return uint8_t 
 */
    uint8_t GPIO_PinRead(GPIO_Def_t gpio);

    /**
 * @brief 
 * 
 * @param gpio 
 */
    void GPIO_PinToggle(GPIO_Def_t gpio);

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_GPIO_MID_LEVEL_H
