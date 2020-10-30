/**
 * @file mcu_m328p.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Atmega328p microcontroller target header file
 * When Titan target is Atmega328p this headers includes and configures everything
 * to work, and defines high abstraction definitions
 * 
 * @date 2020-10-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_MCUS_ATMEGA328P_H)
#define __TITAN_MCUS_ATMEGA328P_H

#include "../mcu_common.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

#ifdef __AVR_ATmega328P__

#define __USART_1_ENABLED 1
// Enables I2C 1 peripheral
#define __TITAN_DRIVERS_I2C_ENABLE1 1
/**
 * @brief Number of digital pins in the microcontroller
 * 
 */
#define NO_DIGITAL_PINS 14
/**
 * @brief Number of analog pins in the microcontroller
 * 
 */
#define NO_ANALOG_PINS 6

#define NO_GPIO_PIN (NO_DIGITAL_PINS + NO_ANALOG_PINS)

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
#define A0 NO_DIGITAL_PINS

/**
 * @brief Analog 1 | Digital 15 - GPIOC 1
 */
#define A1 (NO_DIGITAL_PINS + 1)

/**
 * @brief Analog 2 | Digital 16 - GPIOC 2
 */
#define A2 (NO_DIGITAL_PINS + 2)

/**
 * @brief Analog 3 | Digital 17 - GPIOC 3
 */
#define A3 (NO_DIGITAL_PINS + 3)

/**
 * @brief Analog 4 | Digital 18 - GPIOC 4
 */
#define A4 (NO_DIGITAL_PINS + 4)

/**
 * @brief Analog 5 | Digital 19 - GPIOC 5
 */
#define A5 (NO_DIGITAL_PINS + 5)

// ------------------- MCU Bus macros -------------------
/**
 * @brief UART TX | Digital 1
 */
#define UART_TX_PIN D1
/**
 * @brief UART RX | Digital 0
 */
#define UART_RX_PIN D0

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

// ------------- MCU HW Interrupt Conf ----------------
#define NO_HW_INTERRUPTS 3
#define NO_SW_INTERRUPTS 10

/**
 * @brief INT0 Hardware interrupt pin reference
 * 
 */
#define HW_INT0_PIN D2

/**
 * @brief INT1 Hardware interrupt pin reference
 * 
 */
#define HW_INT1_PIN D3

    /**
 * @brief Atmega328p Microcontroller specific hardware interrupt control register
 * 
 */
    typedef struct
    {
        __IO BaseType_t en_int0 : 1;
        __IO BaseType_t en_int1 : 1;
        __IO BaseType_t RESERVED : 6;
    } HW_INT_EnRegister_t;

#define INT_ControlRegister ((volatile HW_INT_CtrlRegister_t*)(0x69))
#define INT_EnableRegister ((volatile HW_INT_EnRegister_t*)(0x1D))

    /**
 * @brief Initalizes INT0 hardware interrupt
 * 
 * @param mode ISR Mode
 */
    void ISR_INT0_Init(uint8_t mode);

    /**
 * @brief Initalizes INT1 hardware interrupt
 * 
 * @param mode ISR Mode
 */
    void ISR_INT1_Init(uint8_t mode);

    /**
 * @brief Deinitializes INT0 hardware interrupt
 * 
 */
    void ISR_INT0_DeInit();

    /**
 * @brief Deinitializes INT1 hardware interrupt
 * 
 */
    void ISR_INT1_DeInit();

#endif

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_MCUS_ATMEGA328P_H