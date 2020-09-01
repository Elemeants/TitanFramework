#include "wiring.h"

#include "drivers/gpio.h"
#include "utils/loop_utils.h"


#define __HW_INTERRUPT_DEF(__pin, __vector) \
    {                                       \
        .pin = __pin,                       \
        ._isrCall = NULL,                   \
        .__isr_count = 0,                   \
        .__vector_num = __vector,           \
        .params = NULL                      \
    }

HWInterrupt_Handler_t hw_isr_vectors[NO_HW_INTERRUPTS] = {
    __HW_INTERRUPT_DEF(HW_INT0_PIN, INT0_vect_num),
    __HW_INTERRUPT_DEF(HW_INT1_PIN, INT1_vect_num),
};

#undef __HW_INTERRUPT_DEF

#define __SW_INTERRUPT_DEF(__vector) \
    {                                \
        ._isrCall = NULL,            \
        .__isr_count = 0,            \
        .__vector_num = __vector     \
    }

SWInterrupt_Handler_t sw_isr_vector[NO_SW_INTERRUPTS] = {
    __SW_INTERRUPT_DEF(TIMER2_OVF_vect_num),
    __SW_INTERRUPT_DEF(TIMER1_CAPT_vect_num),
    __SW_INTERRUPT_DEF(TIMER1_COMPA_vect_num),
    __SW_INTERRUPT_DEF(TIMER1_COMPB_vect_num),
    __SW_INTERRUPT_DEF(TIMER1_OVF_vect_num),
    __SW_INTERRUPT_DEF(TIMER0_OVF_vect_num),
    __SW_INTERRUPT_DEF(SPI_STC_vect_num),
    __SW_INTERRUPT_DEF(USART_UDRE_vect_num),
    __SW_INTERRUPT_DEF(ADC_vect_num),
    __SW_INTERRUPT_DEF(TWI_vect_num),
};

uint8_t index_isr_vector(uint8_t __vector_num)
{
    for_in_range(uint8_t, _index, 0, NO_SW_INTERRUPTS)
    {
        if (sw_isr_vector[_index].__vector_num == __vector_num)
        {
            return _index;
        }
    }
    return -1;
}

static void sw_isr_wrapper(uint8_t __vector_num)
{
    if ((__vector_num - SW_INTERRUPT_OFFSET) >= NO_SW_INTERRUPTS)
    {
        return;
    }
    uint8_t index = index_isr_vector(__vector_num);
    if (index == (uint8_t)-1) {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vector[index];
    handler->__isr_count++;
    if (handler->_isrCall)
        handler->_isrCall(handler->params);
}

static void hw_isr_wrapper(uint8_t __vector_num)
{
    if ((__vector_num - HW_INTERRUPT_OFFSET) >= NO_HW_INTERRUPTS)
    {
        return;
    }
    HWInterrupt_Handler_t *handler = &hw_isr_vectors[__vector_num - HW_INTERRUPT_OFFSET];
    handler->__isr_count++;
    if (handler->_isrCall)
        handler->_isrCall(handler->params);
}

const char *ISR_VectorNumName(uint8_t __vec_num)
{
    switch (__vec_num)
    {
    case TIMER2_OVF_vect_num:
        return "TIMER2_OVF_vect";
    case TIMER1_CAPT_vect_num:
        return "TIMER1_CAPT_vect";
    case TIMER1_COMPA_vect_num:
        return "TIMER1_COMPA_vect";
    case TIMER1_COMPB_vect_num:
        return "TIMER1_COMPB_vect";
    case TIMER1_OVF_vect_num:
        return "TIMER1_OVF_vect";
    case TIMER0_OVF_vect_num:
        return "TIMER0_OVF_vect";
    case SPI_STC_vect_num:
        return "SPI_STC_vect";
    case USART_UDRE_vect_num:
        return "USART_UDRE_vect";
    case ADC_vect_num:
        return "ADC_vect";
    case TWI_vect_num:
        return "TWI_vect";
    }
    return "";
}

#define SW_ISR_Wrapper(__vector_num)  \
    ISR(_VECTOR(__vector_num))        \
    {                                 \
        sw_isr_wrapper(__vector_num); \
    }

#define HW_ISR_Wrapper(__vector_num)  \
    ISR(_VECTOR(__vector_num))        \
    {                                 \
        hw_isr_wrapper(__vector_num); \
    }

HW_ISR_Wrapper(INT0_vect_num);
HW_ISR_Wrapper(INT1_vect_num);

SW_ISR_Wrapper(TIMER2_OVF_vect_num);
SW_ISR_Wrapper(TIMER1_CAPT_vect_num);
SW_ISR_Wrapper(TIMER1_COMPA_vect_num);
SW_ISR_Wrapper(TIMER1_COMPB_vect_num);
SW_ISR_Wrapper(TIMER1_OVF_vect_num);
SW_ISR_Wrapper(TIMER0_OVF_vect_num);
SW_ISR_Wrapper(SPI_STC_vect_num);
SW_ISR_Wrapper(USART_UDRE_vect_num);
SW_ISR_Wrapper(ADC_vect_num);
SW_ISR_Wrapper(TWI_vect_num);

#undef SW_ISR_Wrapper
#undef HW_ISR_Wrapper

HWInterrupt_Handler_t *ISR_PinToHandler(uint8_t pin)
{
    switch (pin)
    {
    case HW_INT0_PIN:
        return &hw_isr_vectors[0];

    case HW_INT1_PIN:
        return &hw_isr_vectors[1];

    default:
        return NULL;
    }
}

static void ISR_INT0_Init(uint8_t mode)
{
    GPIO_PinMode(HW_INT0_PIN, INPUT);
    INT_ControlRegister->INT0_type = mode;
    INT_EnableRegister->en_int0 = 0b1;
}
static void ISR_INT1_Init(uint8_t mode)
{
    GPIO_PinMode(HW_INT1_PIN, INPUT);
    INT_ControlRegister->INT1_type = mode;
    INT_EnableRegister->en_int1 = 0b1;
}

static void ISR_INT0_DeInit()
{
    INT_ControlRegister->INT0_type = 0b00;
    INT_EnableRegister->en_int0 = 0b0;
}
static void ISR_INT1_DeInit()
{
    INT_ControlRegister->INT1_type = 0b00;
    INT_EnableRegister->en_int1 = 0b0;
}

void ISR_hw_deinit(uint8_t pin)
{
    switch (pin)
    {
    case HW_INT0_PIN:
        ISR_INT0_DeInit();
        break;
    case HW_INT1_PIN:
        ISR_INT1_DeInit();
        break;
    }
    sei();
}

void ISR_hw_init(uint8_t pin, uint8_t mode)
{
    switch (pin)
    {
    case HW_INT0_PIN:
        ISR_INT0_Init(mode);
        break;
    case HW_INT1_PIN:
        ISR_INT1_Init(mode);
        break;
    }
    sei();
}