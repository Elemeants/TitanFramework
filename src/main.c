#include "titan.h"

#define LED_BUILDINT A0

// Make API HAL to control bus SPI
#define array_size(__array) (sizeof(__array) / sizeof(__array[0]))

char hello_world_string[] = "Hello world USART Enabled!\n\r";

int main()
{
    USART_Init(1, 9600);
    pinMode(LED_BUILDINT, OUTPUT);

    while (1)
    {
        digitalToggle(LED_BUILDINT);
        USART_WriteBuffer(1, hello_world_string, array_size(hello_world_string));
    }
    return 0;
}