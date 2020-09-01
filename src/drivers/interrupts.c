#include "interrupts.h"

#include "wiring.h"
#include "utils/loop_utils.h"

extern void ISR_hw_init(uint8_t pin, uint8_t mode);
extern void ISR_hw_deinit(uint8_t pin);

void ISR_hw_attach(uint8_t pin_num, void (*isr_call)(void *params), void *params, uint8_t isrMode)
{
    if (pin_num >= NO_DIGITAL_GPIO_PIN || !IS_GPIO_INTERRUPT(gpio_pins[pin_num].gpio_type))
    {
        return;
    }
    HWInterrupt_Handler_t *handler = ISR_PinToHandler(pin_num);
    handler->params = params;
    handler->_isrCall = isr_call;
    ISR_hw_init(pin_num, isrMode);
}
void ISR_hw_deattach(uint8_t pin_num)
{
    if (pin_num >= NO_DIGITAL_GPIO_PIN || !IS_GPIO_INTERRUPT(gpio_pins[pin_num].gpio_type))
    {
        return;
    }
    HWInterrupt_Handler_t *handler = ISR_PinToHandler(pin_num);
    handler->_isrCall = NULL;
    handler->params = NULL;
    ISR_hw_deinit(pin_num);
}

void ISR_sw_attach(uint8_t __vec_num, void (*isr_call)(void *params), void *params)
{
    if ((__vec_num - SW_INTERRUPT_OFFSET) >= NO_SW_INTERRUPTS)
    {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vector[__vec_num - SW_INTERRUPT_OFFSET];
    handler->params = params;
    handler->_isrCall = isr_call;
}
void ISR_sw_deattach(uint8_t __vec_num)
{
    if ((__vec_num - SW_INTERRUPT_OFFSET) >= NO_SW_INTERRUPTS)
    {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vector[__vec_num - SW_INTERRUPT_OFFSET];
    handler->params = NULL;
    handler->_isrCall = NULL;
}
