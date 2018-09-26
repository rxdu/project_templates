/* 
 * racerio_can.h
 * 
 * Created on: Feb 18, 2018 00:49
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */ 

#ifndef RACERIO_CAN_H
#define RACERIO_CAN_H

#include "stdint.h"
#include "stdbool.h"

void RACERIO_InitCAN();
int32_t RACERIO_CAN_TxCANFrame(uint32_t id, bool is_id_ext, const uint8_t *data, uint8_t data_len);

#endif /* RACERIO_CAN_H */
