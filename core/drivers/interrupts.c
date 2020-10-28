#include "interrupts.h"

#include "mcus/include.h"
#include "gpio.h"
#include "mcus/include.h"
#include "utils/loop_utils.h"

uint8_t index_isr_vector(uint8_t __vector_num)
{
    for_in_range(uint8_t, _index, 0, NO_SW_INTERRUPTS)
    {
        if (sw_isr_vectors[_index].__vector_num == __vector_num)
        {
            return _index;
        }
    }
    return -1;
}

uint8_t index_hw_isr_vector(uint8_t __vector_num)
{
    for_in_range(uint8_t, _index, 0, NO_HW_INTERRUPTS)
    {
        if (hw_isr_vectors[_index].__vector_num == __vector_num)
        {
            return _index;
        }
    }
    return -1;
}

void sw_isr_wrapper(uint8_t __vector_num)
{
    uint8_t index = index_isr_vector(__vector_num);
    if (index == (uint8_t)-1)
    {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vectors[index];
    handler->__isr_count++;
    if (handler->_isrCall)
        handler->_isrCall(handler->params);
}

void hw_isr_wrapper(uint8_t __vector_num)
{
    uint8_t index = index_hw_isr_vector(__vector_num);
    if (index == (uint8_t)-1)
    {
        return;
    }
    HWInterrupt_Handler_t *handler = &hw_isr_vectors[index];
    handler->__isr_count++;
    if (handler->_isrCall)
        handler->_isrCall(handler->params);
}

void ISR_hw_attach(uint8_t pin_num, void (*isr_call)(void *params), void *params, uint8_t isrMode)
{
    if (pin_num >= NO_GPIO_PIN || !IS_GPIO_INTERRUPT(gpio_pins[pin_num].gpio_type))
    {
        return;
    }
    HWInterrupt_Handler_t *handler = ISR_PinToHandler(pin_num);
    if (handler == NULL)
    {
        return;
    }
    handler->params = params;
    handler->_isrCall = isr_call;
    ISR_hw_init(pin_num, isrMode);
}

void ISR_hw_deattach(uint8_t pin_num)
{
    if (pin_num >= NO_GPIO_PIN || !IS_GPIO_INTERRUPT(gpio_pins[pin_num].gpio_type))
    {
        return;
    }
    HWInterrupt_Handler_t *handler = ISR_PinToHandler(pin_num);
    if (handler == NULL)
    {
        return;
    }
    handler->_isrCall = NULL;
    handler->params = NULL;
    ISR_hw_deinit(pin_num);
}

void ISR_sw_attach(uint8_t __vec_num, void (*isr_call)(void *params), void *params)
{
    uint8_t index = index_isr_vector(__vec_num);
    if (index == (uint8_t)-1)
    {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vectors[index];
    handler->params = params;
    handler->_isrCall = isr_call;
}

void ISR_sw_deattach(uint8_t __vec_num)
{
    uint8_t index = index_isr_vector(__vec_num);
    if (index == (uint8_t)-1)
    {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vectors[index];
    handler->params = NULL;
    handler->_isrCall = NULL;
}
