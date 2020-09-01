#if !defined(PLATFORM_WIRING_H)
#define PLATFORM_WIRING_H

#include "platform.h"

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
#define NO_DIGITAL_GPIO_PIN 20
extern GPIO_Def_t gpio_pins[NO_DIGITAL_GPIO_PIN];

// ------------------- MCU Pin macros -------------------
/**
 * @brief Digital pin 0 - GPIO D 0
 */
#define D0 0

/**
 * @brief Digital pin 1 - GPIO D 1
 */
#define D1 1

/**
 * @brief Digital pin 2 - GPIO D 2
 */
#define D2 2

/**
 * @brief Digital pin 3 - GPIO D 3
 */
#define D3 3

/**
 * @brief Digital pin 4 - GPIO D 4
 */
#define D4 4

/**
 * @brief Digital pin 5 - GPIO D 5
 */
#define D5 5

/**
 * @brief Digital pin 6 - GPIO D 6
 */
#define D6 6

/**
 * @brief Digital pin 7 - GPIO D 7
 */
#define D7 7

/**
 * @brief Digital pin 8 - GPIOB 0
 */
#define D8 8

/**
 * @brief Digital pin 9 - GPIOB 1
 */
#define D9 9

/**
 * @brief Digital pin 10 - GPIOB 2
 */
#define D10 10

/**
 * @brief Digital pin 11 - GPIOB 3
 */
#define D11 11

/**
 * @brief Digital pin 12 - GPIOB 4
 */
#define D12 12

/**
 * @brief Digital pin 13 - GPIOB 6
 */
#define D13 13

/**
 * @brief Analog 0 | Digital 14 - GPIOC 0
 */
#define A0 0

/**
 * @brief Analog 1 | Digital 15 - GPIOC 1
 */
#define A1 1

/**
 * @brief Analog 2 | Digital 16 - GPIOC 2
 */
#define A2 2

/**
 * @brief Analog 3 | Digital 17 - GPIOC 3
 */
#define A3 3

/**
 * @brief Analog 4 | Digital 18 - GPIOC 4
 */
#define A4 4

/**
 * @brief Analog 5 | Digital 19 - GPIOC 5
 */
#define A5 5

// ------------------- MCU Bus macros -------------------
/**
 * @brief UART TX | Digital 0
 */
#define UART_TX_PIN D0
/**
 * @brief UART RX | Digital 1
 */
#define UART_RX_PIN D1

/**
 * @brief SPI SS | Digital 10
 */
#define SPI_SS_PIN D10
/**
 * @brief SPI MOSI | Digital 11
 */
#define SPI_MOSI_PIN D11
/**
 * @brief SPI MISO | Digital 12
 */
#define SPI_MISO_PIN D12
/**
 * @brief SPI SCK | Digital 13
 */
#define SPI_SCK_PIN D13

/**
 * @brief I2C SCL | Analog 4
 */
#define I2C_SCL_PIN A4
/**
 * @brief I2C SDA | Analog 5
 */
#define I2C_SDA_PIN A5

// ------------------- MCU I2C Conf -------------------

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

// ------------- MCU HW Interrupt Conf ----------------
#define NO_HW_INTERRUPTS 2
#define HW_INTERRUPT_OFFSET 0x1

#define HW_INT0_PIN D2
#define HW_INT1_PIN D3

#include <avr/io.h>
#include <avr/interrupt.h>

#define INT_ControlRegister ((volatile HW_INT_CtrlRegister_t*)(0x69)) 
#define INT_EnableRegister ((volatile HW_INT_EnRegister_t*)(0x1D))

extern HWInterrupt_Handler_t hw_isr_vectors[NO_HW_INTERRUPTS];

uint8_t index_isr_vector(uint8_t __vector_num);

#define NO_SW_INTERRUPTS 10

#define SW_INTERRUPT_OFFSET 0x3
extern SWInterrupt_Handler_t sw_isr_vector[NO_SW_INTERRUPTS];

#endif  // PLATFORM_WIRING_H
