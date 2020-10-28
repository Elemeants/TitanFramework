#include "gpio.h"

#include "mcus/include.h"

extern GPIO_Def_t gpio_pins[NO_GPIO_PIN];

void GPIO_HAL_PortInit(GPIO_Handler port, BaseType_t ddr_set)
{
    port->ddr = ddr_set;
}

void GPIO_HAL_PinInit(GPIO_Handler port, BaseType_t pin, uint8_t status)
{
    switch (status)
    {
    case INPUT:
        _clear_bit(port->ddr, pin);
        break;
    case OUTPUT:
        _set_bit(port->ddr, pin);
        break;
    case PULL_UP:
        _clear_bit(port->ddr, pin);
        GPIO_HAL_PinWrite(port, pin, HIGH);
        break;
    }
}

void GPIO_HAL_PortWrite(GPIO_Handler port, BaseType_t port_value)
{
    port->port = port_value;
}

void GPIO_HAL_PinWrite(GPIO_Handler port, BaseType_t pin, uint8_t value)
{
    if (value == 0)
    {
        port->port &= ~_BV(pin);
    }
    else
    {
        port->port |= _BV(pin);
    }
}

void GPIO_HAL_PinToggle(GPIO_Handler port, BaseType_t pin)
{
    GPIO_HAL_PinWrite(port, pin, !GPIO_HAL_PinRead(port, pin));
}

BaseType_t GPIO_HAL_PortRead(GPIO_Handler port)
{
    return port->pin;
}

uint8_t GPIO_HAL_PinRead(GPIO_Handler port, BaseType_t pin)
{
    return (GPIO_HAL_PortRead(port) & _BV(pin)) > 0;
}

void GPIO_PinInit(GPIO_Def_t gpio, uint8_t mode)
{
    GPIO_HAL_PinInit(gpio.port, gpio.no_pin, mode);
}

void GPIO_PinWrite(GPIO_Def_t gpio, uint8_t value)
{
    GPIO_HAL_PinWrite(gpio.port, gpio.no_pin, value);
}

uint8_t GPIO_PinRead(GPIO_Def_t gpio)
{
    return GPIO_HAL_PinRead(gpio.port, gpio.no_pin);
}

void GPIO_PinToggle(GPIO_Def_t gpio)
{
    GPIO_HAL_PinToggle(gpio.port, gpio.no_pin);
}

void pinMode(uint8_t pin, uint8_t mode)
{
    if (pin >= NO_GPIO_PIN)
    {
        return;
    }
    GPIO_PinInit(gpio_pins[pin], mode);
}
void digitalWrite(uint8_t pin, uint8_t value)
{
    if (pin >= NO_GPIO_PIN)
    {
        return;
    }
    GPIO_PinWrite(gpio_pins[pin], value);
}

uint8_t digitalRead(uint8_t pin)
{
    if (pin >= NO_GPIO_PIN)
    {
        return (uint8_t)-1;
    }
    return GPIO_PinRead(gpio_pins[pin]);
}

void digitalToggle(uint8_t pin)
{
    if (pin >= NO_GPIO_PIN)
    {
        return;
    }
    GPIO_PinToggle(gpio_pins[pin]);
}

void analogWrite(uint8_t pin, uint16_t value)
{
    if (pin >= NO_GPIO_PIN || !IS_GPIO_PWM(gpio_pins[pin].gpio_type))
    {
        return;
    }
}
