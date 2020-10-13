#if !defined(_INTERRUPT_DRIVER_H)
#define _INTERRUPT_DRIVER_H

#include <avr/interrupt.h>
#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

extern const char *ISR_VectorNumName(uint8_t __vec_num);
extern HWInterrupt_Handler_t *ISR_PinToHandler(uint8_t pin);

#define ISR_enable_interrrupts() sei()
#define ISR_disable_interrrupts() cli()

#define ISR_ON_LOW 0b00
#define ISR_ON_ANY 0b01
#define ISR_ON_FALLING 0b10
#define ISR_ON_RISING 0b11

void ISR_hw_attach(uint8_t pin_num, void (*isr_call)(void *params), void *params, uint8_t isrMode);
void ISR_hw_deattach(uint8_t pin_num);

void ISR_sw_attach(uint8_t __vec_num, void (*isr_call)(void *params), void *params);
void ISR_sw_deattach(uint8_t __vec_num);

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif // _INTERRUPT_DRIVER_H
