/**
 * @file i2c.h
 * @author Daniel Polanco (jdanypa@gmail.com)
 * @brief I2C driver implementation header
 * @date 2020-10-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#if !defined(__TITAN_DRIVERS_I2C_H)
#define __TITAN_DRIVERS_I2C_H

#include "i2c_defs.h"
#include "i2c_utils.h"
#include "platform.h"

#ifndef I2C_BUS_FREQ
/**
 * @brief I2C bus frequency in Hz
 * 
 */
#define I2C_BUS_FREQ 100000L
#endif

#ifndef I2C_BUFFER_LENGTH
/**
 * @brief I2C bus buffer length in bytes, for RX/TX
 * 
 */
#define I2C_BUFFER_LENGTH 64U
#endif

#define I2C_READY 0
#define I2C_MRX 1
#define I2C_MTX 2
#define I2C_SRX 3
#define I2C_STX 4

#define I2C_SPEED_100k 100000UL
#define I2C_SPEED_400k 400000UL

#ifdef __cplusplus
extern "C"
{
#endif  // !__cplusplus

    // -------------------------- I2C BUS STRUCTURE --------------------------

    /**
     * @brief Structure that represents a I2C bus
     * 
     */
    struct I2C_BusHandler
    {
        /**
         * @brief Primitive port handler
         * 
         */
        TWI_Handler port;

        /**
         * @brief I2C state
         * 
         */
        __IO uint8_t state;

        /**
         * @brief Flag - Send stop condition
         * 
         */
        __IO uint8_t send_stop;

        /**
         * @brief Flag - when repeated start condition
         * 
         */
        __IO uint8_t in_rep_start;

        /**
         * @brief Flag - on error condition
         * 
         */
        __IO uint8_t error;

        /**
         * @brief Represents an union for slave read or write control
         * 
         */
        __IO union
        {
            struct
            {
                /**
                 * @brief read flag
                 * 
                 */
                __IO uint8_t r_flag : 1;

                /**
                 * @brief slave address
                 * 
                 */
                __IO uint8_t addr : 7;
            };
            __IO uint8_t raw;
        } sla_rw;

        /**
         * @brief Master I2C Buffer used as circular buffer
         * 
         */
        uint8_t masterBuffer[I2C_BUFFER_LENGTH];
        /**
         * @brief Master I2C Buffer circular buffer index
         * 
         */
        uint8_t masterBuffer_index;
        /**
         * @brief Master I2C Buffer circular length
         * 
         */
        uint8_t masterBuffer_length;

        /**
         * @brief Tx I2C Buffer used as circular buffer
         * 
         */
        uint8_t txBuffer[I2C_BUFFER_LENGTH];
        /**
         * @brief Tx I2C Buffer circular buffer index
         * 
         */
        uint8_t txBuffer_index;
        /**
         * @brief Tx I2C Buffer circular buffer length
         * 
         */
        uint8_t txBuffer_length;

        /**
         * @brief Rx I2C Buffer used as circular buffer
         * 
         */
        uint8_t rxBuffer[I2C_BUFFER_LENGTH];
        /**
         * @brief Rx I2C Buffer circular buffer index
         * 
         */
        uint8_t rxBuffer_index;
        /**
         * @brief Rx I2C Buffer circular buffer length
         * 
         */
        uint8_t rxBuffer_length;

        /**
         * @brief Rx event I2C Buffer used as circular buffer
         * 
         */
        uint8_t rxEventBuff[I2C_BUFFER_LENGTH];
        /**
         * @brief Rx event I2C Buffer circular buffer index
         * 
         */
        uint8_t rxEventBuff_index;
        /**
         * @brief Rx event I2C Buffer circular buffer length
         * 
         */
        uint8_t rxEventBuff_length;

        /**
         * @brief Pointer to Rx event function
         * 
         * @param length Number of bytes received
         */
        void (*rxEvent)(uint8_t length);

        /**
         * @brief Pointer to Tx event function
         * 
         */
        void (*txEvent)(void);

        /**
         * @brief Initializes the I2C peripheral
         * 
         */
        void (*Init)();

        /**
         * @brief Deinitialize the port
         * 
         */
        void (*DeInit)();

        /**
         * @brief Sets the I2C device address
         * 
         * @param addr Address to set the I2C device
         */
        void (*SetAddress)(uint8_t addr);

        /**
         * @brief Sets the I2C bus frequency
         * 
         * @param frec Frequency in Hz
         */
        void (*SetFrequency)(uint32_t frec);

        /**
         * @brief Reads from a devices a number of bytes
         * 
         */
        uint8_t (*ReadFrom)(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);

        /**
         * @brief Writes to a device a buffer
         * 
         */
        uint8_t (*WriteTo)(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);

        /**
         * @brief 
         * 
         */
        uint8_t (*Transmit)(const uint8_t *data, uint8_t length);

        /**
         * @brief Sets the rx event callback
         * 
         */
        void (*AttachSlaveRxEvent)(void (*function)(uint8_t len));

        /**
         * @brief Sets the tx event callback
         * 
         */
        void (*AttachSlaveTxEvent)(void (*function)(void));

        /**
         * @brief Sends the ack byte
         * 
         */
        void (*Reply)(uint8_t ack);

        /**
         * @brief Stops transmit
         * 
         */
        void (*Stop)();

        /**
         * @brief As masters release the I2C bus
         * 
         */
        void (*ReleaseBus)();
    };
    typedef struct I2C_BusHandler I2C_BusHandler;

    // ----------------------------- Generic API -----------------------------

    /**
 * @brief Begins the I2C Bus
 * 
 * @param bus bus handler struct
 */
    void I2C_Init(I2C_BusHandler *bus);

    /**
 * @brief Ends the I2C Bus
 * 
 * @param bus bus handler struct
 */
    void I2C_DeInit(I2C_BusHandler *bus);

    /**
 * @brief Sets the device address for I2C
 * 
 * @param bus bus handler struct
 * @param addr Device address to be set
 */
    void I2C_SetAddress(I2C_BusHandler *bus, uint8_t addr);

    /**
 * @brief Sets the I2C bus frequency
 * 
 * @param bus bus handler struct
 * @param frec Frequency in Hz
 */
    void I2C_SetFrequency(I2C_BusHandler *bus, uint32_t frec);

    /**
 * @brief Read a number of bytes from a device connected to the I2C bus.
 * 
 * @param bus bus handler structs
 * @param address slave device address
 * @param data buffer of bytes
 * @param length length of the buffer
 * @param sendStop send stop flag
 * @return uint8_t number of bytes readed
 */
    uint8_t I2C_ReadFrom(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);

    /**
 * @brief Writes bytes to a device
 * 
 * @param bus bus handler structs
 * @param address slave device address
 * @param data buffer of bytes
 * @param length length of the buffer
 * @param wait 
 * @param sendStop send stop flag
 * @return uint8_t number of bytes writted
 */
    uint8_t I2C_WriteTo(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @param data buffer of bytes
 * @param length length of the buffer
 * @return uint8_t number of bytes writted
 */
    uint8_t I2C_Transmit(I2C_BusHandler *bus, const uint8_t *data, uint8_t length);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @param function rx event on received
 */
    void I2C_AttachSlaveRxEvent(I2C_BusHandler *bus, void (*function)(uint8_t length));

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @param function tx event on request
 */
    void I2C_AttachSlaveTxEvent(I2C_BusHandler *bus, void (*function)(void));

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @param ack ack flag
 */
    void I2C_Reply(I2C_BusHandler *bus, uint8_t ack);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 */
    void I2C_Stop(I2C_BusHandler *bus);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 */
    void I2C_ReleaseBus(I2C_BusHandler *bus);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @return uint8_t next buffer byte
 */
    uint8_t I2C_ReadNextByte(I2C_BusHandler *bus);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @param buffer 
 * @param len 
 */
    void I2C_ReadNextBytes(I2C_BusHandler *bus, uint8_t *buffer, uint8_t len);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 * @param inBytes 
 * @param numBytes 
 */
    void I2C_rxEventHandler(I2C_BusHandler *bus, uint8_t *inBytes, int numBytes);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 */
    void I2C_txEventHandler(I2C_BusHandler *bus);

    /**
 * @brief 
 * 
 * @param params 
 */
    void I2C_ISR_Call(void *params);

    /**
 * @brief 
 * 
 * @param bus bus handler structs
 */
    void I2C_ISR_Handler(I2C_BusHandler *bus);

#if __TITAN_DRIVERS_I2C_ENABLE1
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
#endif

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // __TITAN_DRIVERS_I2C_H
