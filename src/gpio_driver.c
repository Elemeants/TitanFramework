#include "gpio_driver.h"

void GPIO_Init(PORT_RefControl_t* port, BaseType_t ddr_set) {
    port->ddr = ddr_set;
}

void GPIO_InitPin(PORT_RefControl_t* port, BaseType_t pin, BaseType_t status) {
    if (status == 0) {
        port->port = _clear_bit(port->port, pin);
    } else {
        port->port =_set_bit(port->port, pin);
    }
}

void GPIO_Write(PORT_RefControl_t* port, BaseType_t port_value) {
    port->port = port_value;
}

void GPIO_WritePin(PORT_RefControl_t* port, BaseType_t pin, BaseType_t value) {
    if (value == 0) {
        port->port = _clear_bit(port->port, pin);
    } else {
        port->port =_set_bit(port->port, pin);
    }
}

BaseType_t GPIO_Read(PORT_RefControl_t* port) {
    return port->pin;
}

BaseType_t GPIO_ReadPin(PORT_RefControl_t* port, BaseType_t pin) {
    return port->pin & _BV(pin);
}