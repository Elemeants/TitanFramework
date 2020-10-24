#include "titan.h"

#define LED_BUILDINT A0

// Make API HAL to control bus UART
// Make API HAL to control bus SPI

int main()
{
    GPIO_PinMode(LED_BUILDINT, OUTPUT);
    GPIO_PinMode(D16, OUTPUT);

    while (1)
    {
        GPIO_DigitalWrite(D16, GPIO_DigitalRead(LED_BUILDINT));
        GPIO_DigitalToggle(LED_BUILDINT);
        delay_ms(100);
    }
    return 0;
}