##########################################################################
# executables in use
##########################################################################
find_program(AVR_CC avr-gcc)
find_program(AVR_CXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE_TOOL avr-size)
find_program(AVR_OBJDUMP avr-objdump)
find_program(AVR_UPLOADER avrdude)

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
set(MCU_SPEED 1000000)
set(MCU_TYPE atmega32)
set(MCU_PROGRAMMER usbasp)
set(MCU_LFUSE 0xE4)
set(MCU_HFUSE 0xD1)

##########################################################################
# Project specific microcontroller settings
##########################################################################
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)
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
set(PROGRAMMER_FLAGS -p ${MCU_TYPE} -c ${MCU_PROGRAMMER} -v)

##########################################################################
# Project settings
##########################################################################
cmake_minimum_required(VERSION 3.1.0)
project(ExampleTitan VERSION 1.0.0)
set(PROJECT_NAME ExampleTitan)
set(FIRMWARE_HEX firmware.hex)

##########################################################################
# Build titan core
##########################################################################
add_subdirectory(core)

##########################################################################
# Additional helper targets 
##########################################################################
add_custom_target(
    flash
    COMMAND ${AVR_UPLOADER} ${PROGRAMMER_FLAGS} -Uflash:w:${FIRMWARE_HEX}:i
)

add_custom_target(
    fuse
    COMMAND ${AVR_UPLOADER} ${PROGRAMMER_FLAGS} -Uhfuse:w:${MCU_HFUSE}:m -Ulfuse:w:${MCU_LFUSE}:m
)

##########################################################################
# Build project
##########################################################################
add_executable(ExampleTitan src/main.cpp)

target_link_libraries(ExampleTitan PUBLIC TitanCore)
target_include_directories(ExampleTitan PUBLIC
                          "${PROJECT_SOURCE_DIR}"
                          "${PROJECT_SOURCE_DIR}/core"
                          )

add_custom_command(
    TARGET ExampleTitan POST_BUILD
    COMMAND ${AVR_OBJCOPY} -j .text -j .data -O ihex ExampleTitan ${FIRMWARE_HEX}
    COMMAND ${AVR_SIZE_TOOL} -C ExampleTitan --mcu=${MCU_TYPE}
)