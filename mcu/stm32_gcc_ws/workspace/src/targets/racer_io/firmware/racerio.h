/* 
 * racerio.h
 * 
 * Created on: Feb 18, 2018 14:49
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef RACERIO_H
#define RACERIO_H

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

/* RacerIO includes. */
#include "racerio_driver.h"

/* Debugging */
#include "jlink_rtt.h"

#define TASK_PRIORITY_HIGHEST   4
#define TASK_PRIORITY_HIGH      3
#define TASK_PRIORITY_MID       2
#define TASK_PRIORITY_LOW       1

#endif /* RACERIO_H */
