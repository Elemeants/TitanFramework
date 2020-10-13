#if !defined(TITAN_HAL_H)
#define TITAN_HAL_H

#include "wiring.h"
#include "platform.h"

#include "drivers/interrupts.h"
#include "drivers/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

extern void delay_ms(uint32_t _ms);
extern void delay_us(uint32_t _us);

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif // TITAN_HAL_H
