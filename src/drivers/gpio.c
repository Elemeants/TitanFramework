#include "gpio.h"

void GPIO_Init(GPIO_Handler port, BaseType_t ddr_set)
{
    port->ddr = ddr_set;
}

void GPIO_InitPin(GPIO_Handler port, BaseType_t pin, uint8_t status)
{
    status == 0 ? _clear_bit(port->ddr, pin) : _set_bit(port->ddr, pin);
}

void GPIO_Write(GPIO_Handler port, BaseType_t port_value)
{
    port->port = port_value;
}

void GPIO_WritePin(GPIO_Handler port, BaseType_t pin, uint8_t value)
{
    value == 0 ? _clear_bit(port->port, pin) : _set_bit(port->port, pin);
}

BaseType_t GPIO_Read(GPIO_Handler port)
{
    return port->pin;
}

uint8_t GPIO_ReadPin(GPIO_Handler port, BaseType_t pin)
{
    return _mask_bit(port->pin,pin);
}

void GPIO_PinInit(GPIO_Def_t gpio, uint8_t mode)
{
    GPIO_InitPin(gpio.port, gpio.no_pin, mode);
}

void GPIO_PinWrite(GPIO_Def_t gpio, uint8_t value)
{
    GPIO_WritePin(gpio.port, gpio.no_pin, value);
}

uint8_t GPIO_PinRead(GPIO_Def_t gpio)
{
    return GPIO_ReadPin(gpio.port, gpio.no_pin);
}

void GPIO_PinMode(uint8_t pin, uint8_t mode)
{
    if (pin >= NO_GPIO_PIN) { return; }
    GPIO_PinInit(gpio_pins[pin], mode);
}
void GPIO_DigitalWrite(uint8_t pin, uint8_t value)
{
    if (pin >= NO_GPIO_PIN) { return; }
    GPIO_PinWrite(gpio_pins[pin], value);
}
uint8_t GPIO_DigitalRead(uint8_t pin)
{
    if (pin >= NO_GPIO_PIN) { return (uint8_t)-1; }
    return GPIO_PinRead(gpio_pins[pin]);
}
void GPIO_PWMWrite(uint8_t pin, uint16_t value)
{
    if (pin >= NO_GPIO_PIN || !IS_GPIO_PWM(gpio_pins[pin].gpio_type)) { return; }
}