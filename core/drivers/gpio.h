#if !defined(GPIO_DRIVER_H)
#define GPIO_DRIVER_H

#include "platform.h"
#include "wiring.h"

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

// ---------------------- Base abstract functions ----------------------

void GPIO_Init(GPIO_Handler port, BaseType_t ddr_set);
void GPIO_InitPin(GPIO_Handler port, BaseType_t pin, uint8_t status);
void GPIO_Write(GPIO_Handler port, BaseType_t value);
void GPIO_WritePin(GPIO_Handler port, BaseType_t pin, BaseType_t value);
BaseType_t GPIO_Read(GPIO_Handler port);
uint8_t GPIO_ReadPin(GPIO_Handler port, BaseType_t pin);
void GPIO_Toggle(GPIO_Handler port, BaseType_t pin);

// ---------------------- Pin management functions ---------------------

void GPIO_PinInit(GPIO_Def_t gpio, uint8_t mode);
void GPIO_PinWrite(GPIO_Def_t gpio, uint8_t value);
uint8_t GPIO_PinRead(GPIO_Def_t gpio);
void GPIO_PinToggle(GPIO_Def_t gpio);

// ---------------------- High abstract level api ----------------------
void GPIO_PinMode(uint8_t pin, uint8_t mode);
void GPIO_DigitalWrite(uint8_t pin, uint8_t value);
uint8_t GPIO_DigitalRead(uint8_t pin);
void GPIO_DigitalToggle(uint8_t gpio);
void GPIO_PWMWrite(uint8_t pin, uint16_t value);

#ifdef __cplusplus
}
#endif // !__cplusplus


#endif  // GPIO_DRIVER_H
