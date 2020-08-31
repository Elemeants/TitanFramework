#include <avr/io.h>
#include "platform.h"
#include "drivers/gpio.h"
#include "drivers/i2c.h"

// Make API HAL to control bus UART
// Make API HAL to control bus SPI

int main()
{
    I2CBus.Init();
    GPIO_PinInit(gpio_pins[0], INPUT);
    GPIO_DigitalWrite(2, HIGH);

    while(1) {

    }
    return 0;
}
