/**
 * @file delay.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Implements some delay functions 
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_DELAY_H)
#define __TITAN_DRIVERS_DELAY_H

#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    /**
 * @brief Represents datetime basic structure
 * 
 */
    struct Time_t
    {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint8_t millisecond;
    };
    typedef struct Time_t Time_t;

    /**
 * @brief Creates a delay in the microcontroller
 * 
 * @param _ms Time in miliseconds to blocks the microcontroller
 */
    void delay_ms(uint32_t _ms);

    /**
 * @brief Creates a delay in the microcontroller
 * 
 * @param _ms Time in microseconds to blocks the microcontroller
 */
    void delay_us(uint32_t _us);

    // WIP (Work in progress)
    // This function should check if an timespan elapsed
    // extern uint8_t blockUntil(Time_t *actualSysMillis, uint32_t milliseconds_to_block);
    // extern uint32_t getSysMillis();
    // extern Time_t getSysTime();

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_DELAY_H
