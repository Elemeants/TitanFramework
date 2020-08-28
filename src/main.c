#include <avr/io.h>
#include "portable.h"
#include "gpio_driver.h"

// Make API HAL to control bus I2C
// Make API HAL to control bus UART
// Make API HAL to control bus SPI
// Make API HAL to control GPIo

int main()
{
    GPIO_Init(&GPIOB, 0xFF);
    GPIO_Write(&GPIOB, 0xFF);
    return 0;
}
