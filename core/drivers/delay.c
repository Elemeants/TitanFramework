#include "delay.h"

#include <util/delay.h>

void delay_ms(uint32_t _ms)
{
    while (_ms--)
    {
        _delay_ms(1);
    }
}

void delay_us(uint32_t _us)
{
    while (_us--)
    {
        _delay_ms(1);
    }
}