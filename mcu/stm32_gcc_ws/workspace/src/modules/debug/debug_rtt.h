/*
 * rtt_debug.h
 *
 *  Created on: Oct 27, 2016
 *      Author: rdu
 */

#ifndef SRC_USER_RTT_DEBUG_H_
#define SRC_USER_RTT_DEBUG_H_

// Add additional functions supported by RRT here
#ifdef ENABLE_SEGGER_RTT
#include "SEGGER_RTT.h"
#define RTT_printf SEGGER_RTT_printf
#else
#define RTT_printf
#endif

#endif /* SRC_USER_RTT_DEBUG_H_ */
