/**
 * @file mcu_m32.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Atmega32 microcontroller target header file
 * When Titan target is Atmega32 this headers includes and configures everything
 * to work, and defines high abstraction definitions
 * 
 * @date 2020-10-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_MCUS_ATMEGA32_H)
#define __TITAN_MCUS_ATMEGA32_H

#include "../mcu_common.h"

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

#ifdef __AVR_ATmega32__

// Enables I2C 1 peripheral
#define __TITAN_DRIVERS_I2C_ENABLE1 1
/**
 * @brief Number of digital pins in the microcontroller
 * 
 */
#define NO_DIGITAL_PINS 24
/**
 * @brief Number of analog pins in the microcontroller
 * 
 */
#define NO_ANALOG_PINS 8

#define NO_GPIO_PIN (NO_DIGITAL_PINS + NO_ANALOG_PINS)

// ------------------- MCU Pin macros -------------------
/**
 * @brief Digital pin 0 - GPIOD 0
 */
#define D0 0

/**
 * @brief Digital pin 1 - GPIOD 1
 */
#define D1 1

/**
 * @brief Digital pin 2 - GPIOD 2
 */
#define D2 2

/**
 * @brief Digital pin 3 - GPIOD 3
 */
#define D3 3

/**
 * @brief Digital pin 4 - GPIOD 4
 */
#define D4 4

/**
 * @brief Digital pin 5 - GPIOD 5
 */
#define D5 5

/**
 * @brief Digital pin 6 - GPIOD 6
 */
#define D6 6

/**
 * @brief Digital pin 7 - GPIOD 7
 */
#define D7 7

/**
 * @brief Digital pin 8 - GPIOC 0
 */
#define D8 8

/**
 * @brief Digital pin 9 - GPIOC 1
 */
#define D9 9

/**
 * @brief Digital pin 10 - GPIOC 2
 */
#define D10 10

/**
 * @brief Digital pin 11 - GPIOC 3
 */
#define D11 11

/**
 * @brief Digital pin 12 - GPIOC 4
 */
#define D12 12

/**
 * @brief Digital pin 13 - GPIOC 5
 */
#define D13 13

/**
 * @brief Digital pin 14 - GPIOC 6
 */
#define D14 14

/**
 * @brief Digital pin 15 - GPIOC 7
 */
#define D15 15

/**
 * @brief Digital pin 16 - GPIOB 0
 */
#define D16 16

/**
 * @brief Digital pin 17 - GPIOB 1
 */
#define D17 17

/**
 * @brief Digital pin 18 - GPIOB 2
 */
#define D18 18

/**
 * @brief Digital pin 19 - GPIOB 3
 */
#define D19 19

/**
 * @brief Digital pin 20 - GPIOB 4
 */
#define D20 20

/**
 * @brief Digital pin 21 - GPIOB 5
 */
#define D21 21

/**
 * @brief Digital pin 22 - GPIOB 6
 */
#define D22 22

/**
 * @brief Digital pin 23 - GPIOB 7
 */
#define D23 23

/**
 * @brief Analog 0 | Digital 24 - GPIOA 0
 */
#define A0 NO_DIGITAL_PINS

/**
 * @brief Analog 1 | Digital 25 - GPIOA 1
 */
#define A1 (NO_DIGITAL_PINS + 1)

/**
 * @brief Analog 2 | Digital 26 - GPIOA 2
 */
#define A2 (NO_DIGITAL_PINS + 2)

/**
 * @brief Analog 3 | Digital 27 - GPIOA 3
 */
#define A3 (NO_DIGITAL_PINS + 3)

/**
 * @brief Analog 4 | Digital 28 - GPIOA 4
 */
#define A4 (NO_DIGITAL_PINS + 4)

/**
 * @brief Analog 5 | Digital 29 - GPIOA 5
 */
#define A5 (NO_DIGITAL_PINS + 5)

/**
 * @brief Analog 6 | Digital 30 - GPIOA 6
 */
#define A6 (NO_DIGITAL_PINS + 6)

/**
 * @brief Analog 7 | Digital 31 - GPIOA 7
 */
#define A7 (NO_DIGITAL_PINS + 7)

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
 * @brief SPI SS | Digital 20
 */
#define SPI_SS_PIN D20
/**
 * @brief SPI MOSI | Digital 21
 */
#define SPI_MOSI_PIN D21
/**
 * @brief SPI MISO | Digital 22
 */
#define SPI_MISO_PIN D22
/**
 * @brief SPI SCK | Digital 23
 */
#define SPI_SCK_PIN D23

/**
 * @brief I2C SCL | Digital 8
 */
#define I2C_SCL_PIN D8
/**
 * @brief I2C SDA | Digital 9
 */
#define I2C_SDA_PIN D9

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
 * @brief INT2 Hardware interrupt pin reference
 * 
 */
#define HW_INT2_PIN D18

    /**
 * @brief Atmega32 Microcontroller specific hardware interrupt control register
 * 
 */
    typedef struct
    {
        __IO BaseType_t en_int0 : 1;
        __IO BaseType_t en_int1 : 1;
        __IO BaseType_t en_int2 : 1;
        __IO BaseType_t RESERVED : 5;
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

#endif  // __TITAN_MCUS_ATMEGA32_H
