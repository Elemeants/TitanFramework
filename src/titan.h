#if !defined(TITAN_HAL_H)
#define TITAN_HAL_H

#include "wiring.h"
#include "platform.h"

#include "drivers/interrupts.h"
#include "drivers/gpio.h"

extern void delay_ms(uint32_t _ms);
extern void delay_us(uint32_t _us);

#endif // TITAN_HAL_H
