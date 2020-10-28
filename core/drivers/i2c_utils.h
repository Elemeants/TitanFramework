/**
 * @file i2c_utils.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief Some util macros for I2C driver
 * @date 2020-10-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_I2C_UTILS_H)
#define __TITAN_DRIVERS_I2C_UTILS_H

/**
 * @brief Default I2C control register flags 
 * 
 */
#define I2C_DEFAULT_FLAGS (_BV(TWIE) | _BV(TWEN) | _BV(TWEA))

/**
 * @brief Util for calculate I2C frequency bus flag value
 * 
 */
#define I2C_FREQUENCY_CALC(frec) (((F_CPU / frec) - 16U) / 2U)

#endif  // __TITAN_DRIVERS_I2C_UTILS_H
