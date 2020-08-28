#include "gpio_driver.h"

void GPIO_Init(PORT_RefControl_t* port, BaseType_t ddr_set) {
    port->ddr = ddr_set;
}

void GPIO_Write(PORT_RefControl_t* port, BaseType_t port_value) {
    port->port = port_value;
}

void GPIO_WritePin(PORT_RefControl_t* port, BaseType_t pin, BaseType_t value) {
    if (value == 0) {
        port->port &= (port->pin & ~_BV(pin));
    } else {
        port->port |= _BV(pin);
    }
}

BaseType_t GPIO_Read(PORT_RefControl_t* port) {
    return port->pin;
}

BaseType_t GPIO_ReadPin(PORT_RefControl_t* port, BaseType_t pin) {
    return port->pin & _BV(pin);
}