#if !defined(TITAN_WIRING_H)
#define TITAN_WIRING_H

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

#include "platform.h"
#ifdef __AVR_ATmega328P__
#include "mcus/atmega328p/mcu_m328p.h"
#elif __AVR_ATmega32__
#include "mcus/atmega32/mcu_m32.h"
#endif

// ------------------- MCU Ports macros -------------------
#ifdef PINA
#define GPIOA ((GPIO_Handler)(&PINA))
#endif
#ifdef PINB
#define GPIOB ((GPIO_Handler)(&PINB))
#endif
#ifdef PINC
#define GPIOC ((GPIO_Handler)(&PINC))
#endif
#ifdef PIND
#define GPIOD ((GPIO_Handler)(&PIND))
#endif
#ifdef PINE
#define GPIOD ((GPIO_Handler)(&PINE))
#endif
#ifdef PINF
#define GPIOD ((GPIO_Handler)(&PINF))
#endif
#ifdef PING
#define GPIOD ((GPIO_Handler)(&PING))
#endif
#ifdef PINH
#define GPIOD ((GPIO_Handler)(&PINH))
#endif
#ifdef PINI
#define GPIOD ((GPIO_Handler)(&PINI))
#endif

// ------------------- MCU Gpio list --------------------
extern GPIO_Def_t gpio_pins[NO_GPIO_PIN];

// ----------------- MCU Interruption -------------------
extern HWInterrupt_Handler_t hw_isr_vectors[NO_HW_INTERRUPTS];
extern SWInterrupt_Handler_t sw_isr_vectors[NO_SW_INTERRUPTS];
void sw_isr_wrapper(uint8_t __vector_num);
void hw_isr_wrapper(uint8_t __vector_num);
uint8_t index_isr_vector(uint8_t __vector_num);
uint8_t index_hw_isr_vector(uint8_t __vector_num);

// -------------------- MCU I2C Conf --------------------

#define TWI0_Register ((TWI_Handler)(&TWBR))

#include "drivers/i2c.h"

extern I2C_BusHandler I2CBus;

void I2CBus_Init();
void I2CBus_DeInit();
void I2CBus_SetAddress(uint8_t addr);
void I2CBus_SetFrequency(uint32_t frec);
uint8_t I2CBus_ReadFrom(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);
uint8_t I2CBus_WriteTo(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);
uint8_t I2CBus_Transmit(const uint8_t *data, uint8_t length);
void I2CBus_AttachSlaveRxEvent(void (*function)(uint8_t len));
void I2CBus_AttachSlaveTxEvent(void (*function)(void));
void I2CBus_Reply(uint8_t ack);
void I2CBus_Stop();
void I2CBus_ReleaseBus();

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif  // TITAN_WIRING_H
