#if !defined(I2C_DRIVER_H)
#define I2C_DRIVER_H

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

#define I2C_BUS_ID 0x01

#ifndef I2C_BUS_FREQ
#define I2C_BUS_FREQ 100000L
#endif

#ifndef I2C_BUFFER_LENGTH
#define I2C_BUFFER_LENGTH 64U
#endif

#define I2C_READY 0
#define I2C_MRX 1
#define I2C_MTX 2
#define I2C_SRX 3
#define I2C_STX 4

#define I2C_SPEED_100k 100000UL
#define I2C_SPEED_400k 400000UL

// -------------------------- I2C BUS STRUCTURE --------------------------
struct I2C_BusHandler
{
    TWI_Handler port;

    
    __IO uint8_t state;
    __IO uint8_t send_stop;
    __IO uint8_t in_rep_start;
    __IO uint8_t error;

    __IO union {
        struct
        {
            __IO uint8_t r_flag : 1;
            __IO uint8_t addr : 7;
        };
        __IO uint8_t raw;
    } sla_rw;

    uint8_t masterBuffer[I2C_BUFFER_LENGTH];
    uint8_t masterBuffer_index;
    uint8_t masterBuffer_lenght;

    uint8_t txBuffer[I2C_BUFFER_LENGTH];
    uint8_t txBuffer_index;
    uint8_t txBuffer_lenght;

    uint8_t rxBuffer[I2C_BUFFER_LENGTH];
    uint8_t rxBuffer_index;
    uint8_t rxBuffer_lenght;

    uint8_t rxEventBuff[I2C_BUFFER_LENGTH];
    uint8_t rxEventBuff_index;
    uint8_t rxEventBuff_lenght;

    void (*rxEvent)(uint8_t lenght);
    void (*txEvent)(void);

    void (*Init)();
    void (*DeInit)();
    void (*SetAddress)(uint8_t addr);
    void (*SetFrequency)(uint32_t frec);
    uint8_t (*ReadFrom)(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);
    uint8_t (*WriteTo)(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);
    uint8_t (*Transmit)(const uint8_t *data, uint8_t length);
    void (*AttachSlaveRxEvent)(void (*function)(uint8_t len));
    void (*AttachSlaveTxEvent)(void (*function)(void));
    void (*Reply)(uint8_t ack);
    void (*Stop)();
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

void I2C_SetAddress(I2C_BusHandler *bus, uint8_t addr);
void I2C_SetFrequency(I2C_BusHandler *bus, uint32_t frec);
uint8_t I2C_ReadFrom(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);
uint8_t I2C_WriteTo(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);
uint8_t I2C_Transmit(I2C_BusHandler *bus, const uint8_t *data, uint8_t length);
void I2C_AttachSlaveRxEvent(I2C_BusHandler *bus, void (*function)(uint8_t lenght));
void I2C_AttachSlaveTxEvent(I2C_BusHandler *bus, void (*function)(void));
void I2C_Reply(I2C_BusHandler *bus, uint8_t ack);
void I2C_Stop(I2C_BusHandler *bus);
void I2C_ReleaseBus(I2C_BusHandler *bus);

uint8_t I2C_ReadNextByte(I2C_BusHandler *bus);
void I2C_ReadNextBytes(I2C_BusHandler *bus, uint8_t *buffer, uint8_t len);

void I2C_rxEventHandler(I2C_BusHandler *bus, uint8_t *inBytes, int numBytes);
void I2C_txEventHandler(I2C_BusHandler *bus);

void I2C_ISR_Call(void *params);
void I2C_ISR_Handler(I2C_BusHandler *bus);

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif  // I2C_DRIVER_H
