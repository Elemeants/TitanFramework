#if !defined(PIN_WIRING_H)
#define PIN_WIRING_H

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
#define EN_TWI0 1

#if EN_TWI0
#define TWI0_Register ((TWI_Handler)(0xB8))
#endif  // !EN_TWI0

#endif  // PIN_WIRING_H
