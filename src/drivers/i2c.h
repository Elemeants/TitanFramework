#if !defined(I2C_DRIVER_H)
#define I2C_DRIVER_H

#include "platform.h"

#include "utils/ringbuffer.h"

#define I2C_BUS_ID 0x01

#ifndef I2C_BUS_FREQ
#define I2C_BUS_FREQ 100000L
#endif

#define I2C_READY 0
#define I2C_MRX 1
#define I2C_MTX 2
#define I2C_SRX 3
#define I2C_STX 4

typedef enum
{
    I2C_SPEED_100k,
    I2C_SPEED_400k,
} I2C_BusSpeed_e;

// -------------------------- I2C BUS STRUCTURE --------------------------
struct I2C_BusHandler
{
    TWI_Handler port;

    __IO struct
    {
        __IO uint8_t state : 2;
        __IO uint8_t send_stop : 1;
        __IO uint8_t in_rep_start : 1;
        __IO uint8_t error : 1;
    };

    __IO union {
        struct
        {
            __IO uint8_t r_flag : 1;
            __IO uint8_t addr : 7;
        };
        __IO uint8_t raw;
    } sla_rw;

    ring_buffer_t txBuffer;
    ring_buffer_t rxBuffer;

    void (*rxEvent)(uint8_t *, int);
    void (*txEvent)(void);


    void (*Init)();
    void (*DeInit)();
    void (*SetAddress)(uint8_t addr);
    void (*SetFrequency)(I2C_BusSpeed_e frec);
    uint8_t (*ReadFrom)(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);
    uint8_t (*WriteTo)(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);
    uint8_t (*Transmit)(const uint8_t *data, uint8_t length);
    void (*AttachSlaveRxEvent)(void (*function)(uint8_t *, int));
    void (*AttachSlaveTxEvent)(void (*function)(void));
    void (*Reply)(uint8_t ack);
    void (*Stop)();
    void (*ReleaseBus)();
};
typedef struct I2C_BusHandler I2C_BusHandler;

#if EN_TWI0
extern I2C_BusHandler I2CBus;
#endif  // !EN_TWI0

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
 * @brief 
 * 
 * @param bus 
 * @param addr 
 */
void I2C_SetAddress(I2C_BusHandler *bus, uint8_t addr);
void I2C_SetFrequency(I2C_BusHandler *bus, I2C_BusSpeed_e frec);
uint8_t I2C_ReadFrom(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop);
uint8_t I2C_WriteTo(I2C_BusHandler *bus, uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop);
uint8_t I2C_Transmit(I2C_BusHandler *bus, const uint8_t *data, uint8_t length);
void I2C_AttachSlaveRxEvent(I2C_BusHandler *bus, void (*function)(uint8_t *, int));
void I2C_AttachSlaveTxEvent(I2C_BusHandler *bus, void (*function)(void));
void I2C_Reply(I2C_BusHandler *bus, uint8_t ack);
void I2C_Stop(I2C_BusHandler *bus);
void I2C_ReleaseBus(I2C_BusHandler *bus);

#endif  // I2C_DRIVER_H
