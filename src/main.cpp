#include "titan.h"

#define LED_BUILDINT A0

// Make API HAL to control bus UART
// Make API HAL to control bus SPI

int main()
{
    pinMode(LED_BUILDINT, OUTPUT);
    pinMode(D16, OUTPUT);

    while (1)
    {
        digitalWrite(D16, digitalRead(LED_BUILDINT));
        digitalToggle(LED_BUILDINT);
        delay_ms(100);
    }
    return 0;
}