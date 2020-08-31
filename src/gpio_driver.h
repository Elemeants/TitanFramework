#if !defined(GPIO_DRIVER_H)
#define GPIO_DRIVER_H

#include "platform.h"
#include <avr/io.h>

void GPIO_Init(PORT_RefControl_t* port, BaseType_t ddr_set);
void GPIO_InitPin(PORT_RefControl_t* port, BaseType_t pin, BaseType_t status);
void GPIO_Write(PORT_RefControl_t* port, BaseType_t value);
void GPIO_WritePin(PORT_RefControl_t* port, BaseType_t pin, BaseType_t value);
BaseType_t GPIO_Read(PORT_RefControl_t* port);
BaseType_t GPIO_ReadPin(PORT_RefControl_t* port, BaseType_t pin);

#endif // GPIO_DRIVER_H
