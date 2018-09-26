/*
    Some Device Drivers for ChibiOS/RT

    Copyright (C) 2014 Konstantin Oblaukhov
    Copyright (C) 2017 Ruixiang Du

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _NRF24L01_H_
#define _NRF24L01_H_

#include "ch.h"
#include "hal.h"

#include "nrf24l01x_reg.h"

#define NRF24L01_EVENT_IRQ 0x01

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/
// Struct for implementing Abstract Streams API
// (Not meant for external use)
struct NRF24L01ChannelVMT
{
    _base_asynchronous_channel_methods
};

struct dNRF24L01Driver;

struct NRF24L01Channel
{
    const struct NRF24L01ChannelVMT *vmt;
    struct NRF24L01Driver *nrfp;
    uint8_t rxBuf[32];
    uint8_t rxBufCount;
    _base_asynchronous_channel_data
};

// NRF24L01 driver config struct 
typedef struct
{
    SPIDriver             *spip;
    ioportid_t            cePort;
    uint16_t              cePad;
} NRF24L01Config;

// NRF24L01 driver struct
struct NRF24L01Driver
{
    struct NRF24L01Channel channels[6];
    event_source_t eventSource;
    const NRF24L01Config  *config;
};

typedef struct NRF24L01Driver NRF24L01Driver;

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
// IRQ handling functions (nrf24l01ExtIRQ() should be called by EXT interrupt handler)
void nrf24l01ExtIRQ(NRF24L01Driver *nrfp);
void nrf24l01ClearIRQ(NRF24L01Driver *nrfp, uint8_t irq);

// Driver initialization function
void nrf24l01ObjectInit(NRF24L01Driver *nrfp);
void nrf24l01Start(NRF24L01Driver *nrfp, const NRF24L01Config *config);

// Configuration functions
void nrf24l01SetRXAddress(NRF24L01Driver *nrfp, uint8_t pipe, const uint8_t addr[5]);
void nrf24l01SetTXAddress(NRF24L01Driver *nrfp,  const uint8_t addr[5]);
void nrf24l01SetPayloadSize(NRF24L01Driver *nrfp, uint8_t pipe, uint8_t size);
void nrf24l01EnablePipes(NRF24L01Driver *nrfp, uint8_t pipes);

void nrf24l01EnableDynamicSize(NRF24L01Driver *nrfp);
void nrf24l01EnableDynamicPipeSize(NRF24L01Driver *nrfp, uint8_t pipes);
void nrf24l01DisableDynamicSize(NRF24L01Driver *nrfp);
void nrf24l01DisableDynamicPipeSize(NRF24L01Driver *nrfp, uint8_t pipes);

void nrf24l01ToggleFeatures(NRF24L01Driver *nrfp);

void nrf24l01FlushRX(NRF24L01Driver *nrfp);
void nrf24l01FlushTX(NRF24L01Driver *nrfp);

void nrf24l01PowerUp(NRF24L01Driver *nrfp);
void nrf24l01PowerDown(NRF24L01Driver *nrfp);

// MCU-NRF24L01 Communication API
void nrf24l01WriteRegister(NRF24L01Driver *nrfp, uint8_t reg, uint8_t value);
uint8_t nrf24l01ReadRegister(NRF24L01Driver *nrfp, uint8_t reg);
void nrf24l01WriteAddressRegister(NRF24L01Driver *nrfp, uint8_t reg, const uint8_t value[5]);
void nrf24l01ReadAddressRegister(NRF24L01Driver *nrfp, uint8_t reg, uint8_t value[5]);

// Low-level functions 
// Generally you don't need to use these functions directly. If you don't want to
// use the abstract streams API, you could handle the interrupts and implement your
// own transmitting/receiving logic with these functions. 
uint8_t nrf24l01GetStatus(NRF24L01Driver *nrfp);
uint8_t nrf24l01GetFIFOStatus(NRF24L01Driver *nrfp);
uint8_t nrf24l01GetSize(NRF24L01Driver *nrfp);

void nrf24l01SetupRetransmit(NRF24L01Driver *nrfp, uint8_t delay, uint8_t count);
void nrf24l01SetChannel(NRF24L01Driver *nrfp, uint8_t channel);

void nrf24l01ReadPayload(NRF24L01Driver *nrfp, uint8_t size, uint8_t *data, uint8_t *pipe);
void nrf24l01WritePayload(NRF24L01Driver *nrfp, uint8_t size, const uint8_t *data);

void nrf24l01EnterRX(NRF24L01Driver *nrfp);
void nrf24l01EnterTX(NRF24L01Driver *nrfp);
void nrf24l01EnterStandby(NRF24L01Driver *nrfp);

#endif
