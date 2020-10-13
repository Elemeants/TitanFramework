#include "mcu_m32.h"

#ifdef __AVR_ATmega32__

#include <drivers/gpio.h>
#include <utils/loop_utils.h>

#include "../mcu_common.h"
#include "wiring.h"

// Arduino boards compatibility constants
GPIO_Def_t gpio_pins[NO_GPIO_PIN] = {
    __GPIO_DEF(GPIOD, 0, GPIO_GENERIC | GPIO_UART),       // Digital 0 - RX UART
    __GPIO_DEF(GPIOD, 1, GPIO_GENERIC | GPIO_UART),       // Digital 1 - TX UART
    __GPIO_DEF(GPIOD, 2, GPIO_GENERIC | GPIO_INTERRUPT),  // Digital 2 - INT0
    __GPIO_DEF(GPIOD, 3, GPIO_GENERIC | GPIO_INTERRUPT),  // Digital 3 - INT1
    __GPIO_DEF(GPIOD, 4, GPIO_GENERIC),                   // Digital 4
    __GPIO_DEF(GPIOD, 5, GPIO_GENERIC),                   // Digital 5
    __GPIO_DEF(GPIOD, 6, GPIO_GENERIC),                   // Digital 6
    __GPIO_DEF(GPIOD, 7, GPIO_GENERIC),                   // Digital 7

    __GPIO_DEF(GPIOC, 0, GPIO_GENERIC | GPIO_I2C),  // Digital 8 - SCL
    __GPIO_DEF(GPIOC, 1, GPIO_GENERIC | GPIO_I2C),  // Digital 9 - SDA
    __GPIO_DEF(GPIOC, 2, GPIO_GENERIC),             // Digital 10
    __GPIO_DEF(GPIOC, 3, GPIO_GENERIC),             // Digital 11
    __GPIO_DEF(GPIOC, 4, GPIO_GENERIC),             // Digital 12
    __GPIO_DEF(GPIOC, 5, GPIO_GENERIC),             // Digital 13
    __GPIO_DEF(GPIOC, 6, GPIO_GENERIC),             // Digital 14
    __GPIO_DEF(GPIOC, 7, GPIO_GENERIC),             // Digital 15

    __GPIO_DEF(GPIOB, 0, GPIO_GENERIC),                   // Digital 16
    __GPIO_DEF(GPIOB, 1, GPIO_GENERIC),                   // Digital 17
    __GPIO_DEF(GPIOB, 2, GPIO_GENERIC | GPIO_INTERRUPT),  // Digital 18
    __GPIO_DEF(GPIOB, 3, GPIO_GENERIC),                   // Digital 19
    __GPIO_DEF(GPIOB, 4, GPIO_GENERIC | GPIO_SPI),        // Digital 20 - SS
    __GPIO_DEF(GPIOB, 5, GPIO_GENERIC | GPIO_SPI),        // Digital 21 - MOSI
    __GPIO_DEF(GPIOB, 6, GPIO_GENERIC | GPIO_SPI),        // Digital 22 - MISO
    __GPIO_DEF(GPIOB, 7, GPIO_GENERIC | GPIO_SPI),        // Digital 23 - SCK

    __GPIO_DEF(GPIOA, 0, GPIO_GENERIC | GPIO_ADC),  // Analog 0 - Digital 24
    __GPIO_DEF(GPIOA, 1, GPIO_GENERIC | GPIO_ADC),  // Analog 1 - Digital 25
    __GPIO_DEF(GPIOA, 2, GPIO_GENERIC | GPIO_ADC),  // Analog 2 - Digital 26
    __GPIO_DEF(GPIOA, 3, GPIO_GENERIC | GPIO_ADC),  // Analog 3 - Digital 27
    __GPIO_DEF(GPIOA, 4, GPIO_GENERIC | GPIO_ADC),  // Analog 4 - Digital 28
    __GPIO_DEF(GPIOA, 5, GPIO_GENERIC | GPIO_ADC),  // Analog 5 - Digital 29
    __GPIO_DEF(GPIOA, 6, GPIO_GENERIC | GPIO_ADC),  // Analog 5 - Digital 30
    __GPIO_DEF(GPIOA, 7, GPIO_GENERIC | GPIO_ADC),  // Analog 5 - Digital 31
};

HWInterrupt_Handler_t hw_isr_vectors[NO_HW_INTERRUPTS] = {
    __HW_INTERRUPT_DEF(HW_INT0_PIN, INT0_vect_num),
    __HW_INTERRUPT_DEF(HW_INT1_PIN, INT1_vect_num),
    __HW_INTERRUPT_DEF(HW_INT2_PIN, INT2_vect_num),
};

SWInterrupt_Handler_t sw_isr_vectors[NO_SW_INTERRUPTS] = {
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

void ISR_INT0_Init(uint8_t mode)
{
    GPIO_PinMode(HW_INT0_PIN, INPUT);
    INT_ControlRegister->INT0_type = mode;
    INT_EnableRegister->en_int0 = 0b1;
}
void ISR_INT1_Init(uint8_t mode)
{
    GPIO_PinMode(HW_INT1_PIN, INPUT);
    INT_ControlRegister->INT1_type = mode;
    INT_EnableRegister->en_int1 = 0b1;
}

void ISR_INT0_DeInit()
{
    INT_ControlRegister->INT0_type = 0b00;
    INT_EnableRegister->en_int0 = 0b0;
}
void ISR_INT1_DeInit()
{
    INT_ControlRegister->INT1_type = 0b00;
    INT_EnableRegister->en_int1 = 0b0;
}

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

ISR(INT0_vect) { hw_isr_wrapper(INT0_vect_num); }
ISR(INT1_vect) { hw_isr_wrapper(INT1_vect_num); }
ISR(INT2_vect) { hw_isr_wrapper(INT2_vect_num); }

ISR(TIMER2_OVF_vect) { sw_isr_wrapper(TIMER2_OVF_vect_num); }
ISR(TIMER1_CAPT_vect) { sw_isr_wrapper(TIMER1_CAPT_vect_num); }
ISR(TIMER1_COMPA_vect) { sw_isr_wrapper(TIMER1_COMPA_vect_num); }
ISR(TIMER1_COMPB_vect) { sw_isr_wrapper(TIMER1_COMPB_vect_num); }
ISR(TIMER1_OVF_vect) { sw_isr_wrapper(TIMER1_OVF_vect_num); }
ISR(TIMER0_OVF_vect) { sw_isr_wrapper(TIMER0_OVF_vect_num); }
ISR(SPI_STC_vect) { sw_isr_wrapper(SPI_STC_vect_num); }
ISR(USART_UDRE_vect) { sw_isr_wrapper(USART_UDRE_vect_num); }
ISR(ADC_vect) { sw_isr_wrapper(ADC_vect_num); }
ISR(TWI_vect) { sw_isr_wrapper(TWI_vect_num); }

#endif