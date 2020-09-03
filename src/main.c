#include <avr/io.h>
#include "titan.h"

#define LED_BUILDINT A1

// Make API HAL to control bus UART
// Make API HAL to control bus SPI

int main()
{
    I2C_Init(&I2CBus);
    I2C_SetAddress(&I2CBus, 0x11);
    GPIO_Init(GPIOA, 0xFF);
    while(1) {
        GPIO_Write(GPIOA, 0xFF);
        delay_ms(500);
        GPIO_Write(GPIOA, 0x00);
        delay_ms(500);
    }
    return 0;
}
