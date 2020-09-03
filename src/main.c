#include <avr/io.h>

#include "titan.h"

#define LED_BUILDINT A0

// Make API HAL to control bus UART
// Make API HAL to control bus SPI

int main()
{
    GPIO_InitPin(GPIOB, 0, OUTPUT);
    GPIO_InitPin(GPIOA, 0, OUTPUT);

    while (1)
    {
        GPIO_WritePin(GPIOB, 0, GPIO_DigitalRead(LED_BUILDINT));
        GPIO_DigitalToggle(LED_BUILDINT);
        delay_ms(100);
    }
    return 0;
}