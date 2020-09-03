#include "wiring.h"

#include "utils/loop_utils.h"
#include <util/delay.h>

uint8_t index_isr_vector(uint8_t __vector_num)
{
    for_in_range(uint8_t, _index, 0, NO_SW_INTERRUPTS)
    {
        if (sw_isr_vectors[_index].__vector_num == __vector_num)
        {
            return _index;
        }
    }
    return -1;
}

uint8_t index_hw_isr_vector(uint8_t __vector_num)
{
    for_in_range(uint8_t, _index, 0, NO_HW_INTERRUPTS)
    {
        if (hw_isr_vectors[_index].__vector_num == __vector_num)
        {
            return _index;
        }
    }
    return -1;
}

void sw_isr_wrapper(uint8_t __vector_num)
{
    uint8_t index = index_isr_vector(__vector_num);
    if (index == (uint8_t)-1) {
        return;
    }
    SWInterrupt_Handler_t *handler = &sw_isr_vectors[index];
    handler->__isr_count++;
    if (handler->_isrCall)
        handler->_isrCall(handler->params);
}

void hw_isr_wrapper(uint8_t __vector_num)
{
    uint8_t index = index_hw_isr_vector(__vector_num);
    if (index == (uint8_t)-1) {
        return;
    }
    HWInterrupt_Handler_t *handler = &hw_isr_vectors[index];
    handler->__isr_count++;
    if (handler->_isrCall)
        handler->_isrCall(handler->params);
}

void I2CBus_Init()
{
    I2C_Init(&I2CBus);
}
void I2CBus_DeInit()
{
    I2C_DeInit(&I2CBus);
}
void I2CBus_SetAddress(uint8_t addr)
{
    I2C_SetAddress(&I2CBus, addr);
}
void I2CBus_SetFrequency(uint32_t frec)
{
    I2C_SetFrequency(&I2CBus, frec);
}
uint8_t I2CBus_ReadFrom(uint8_t address, uint8_t *data, uint8_t length, uint8_t sendStop)
{
    return I2C_ReadFrom(&I2CBus, address, data, length, sendStop);
}
uint8_t I2CBus_WriteTo(uint8_t address, uint8_t *data, uint8_t length, uint8_t wait, uint8_t sendStop)
{
    return I2C_WriteTo(&I2CBus, address, data, length, wait, sendStop);
}
uint8_t I2CBus_Transmit(const uint8_t *data, uint8_t length)
{
    return I2C_Transmit(&I2CBus, data, length);
}
void I2CBus_AttachSlaveRxEvent(void (*function)(uint8_t len))
{
    I2C_AttachSlaveRxEvent(&I2CBus, function);
}
void I2CBus_AttachSlaveTxEvent(void (*function)(void))
{
    I2C_AttachSlaveTxEvent(&I2CBus, function);
}
void I2CBus_Reply(uint8_t ack)
{
    I2C_Reply(&I2CBus, ack);
}
void I2CBus_Stop()
{
    I2C_Stop(&I2CBus);
}
void I2CBus_ReleaseBus()
{
    I2C_ReleaseBus(&I2CBus);
}

I2C_BusHandler I2CBus = {
    .port = TWI0_Register,
    .state = 0b00,
    .send_stop = 0b0,
    .in_rep_start = 0b0,
    .error = 0b0,
    .sla_rw.raw = 0x00,
    .Init = I2CBus_Init,
    .DeInit = I2CBus_DeInit,
    .SetAddress = I2CBus_SetAddress,
    .SetFrequency = I2CBus_SetFrequency,
    .ReadFrom = I2CBus_ReadFrom,
    .WriteTo = I2CBus_WriteTo,
    .Transmit = I2CBus_Transmit,
    .AttachSlaveRxEvent = I2CBus_AttachSlaveRxEvent,
    .AttachSlaveTxEvent = I2CBus_AttachSlaveTxEvent,
    .Reply = I2CBus_Reply,
    .Stop = I2CBus_Stop,
    .ReleaseBus = I2CBus_ReleaseBus,
};

void delay_ms(uint32_t _ms) {
    while (_ms --) {
        _delay_ms(1);
    }
}

void delay_us(uint32_t _us) {
    while (_us --) {
        _delay_ms(1);
    }
}