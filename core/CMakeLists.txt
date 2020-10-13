##########################################################################
# executables in use
##########################################################################
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)

##########################################################################
# toolchain starts with defining mandatory variables
##########################################################################
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

##########################################################################
# Project specific microcontroller settings
##########################################################################
add_compile_options(
    -mmcu=${MCU_TYPE}
    -DF_CPU=${MCU_SPEED}
    -Wall
    -Os
    -g 
    -fsigned-char
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -fshort-enums
    -ffunction-sections
)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)

##########################################################################
# Project settings
##########################################################################
cmake_minimum_required(VERSION 3.0.0)
project(TitanCore VERSION 0.4.0)

##########################################################################
# Project source
##########################################################################
set(TITAN_CORE_SRC drivers/i2c.c drivers/gpio.c drivers/interrupts.c wiring.c)

if(MCU_TYPE MATCHES atmega32)
    list(APPEND TITAN_CORE_SRC mcus/atmega32/mcu_m32.c)
endif(MCU_TYPE MATCHES atmega32)

if(MCU_TYPE MATCHES atmega328p)
    list(APPEND TITAN_CORE_SRC mcus/atmega328p/mcu_m328p.c)
endif(MCU_TYPE MATCHES atmega328p)

##########################################################################
# Build titan library files
##########################################################################
add_library(TitanCore STATIC ${TITAN_CORE_SRC})

target_include_directories(TitanCore PUBLIC
                          "${PROJECT_SOURCE_DIR}"
                          )
