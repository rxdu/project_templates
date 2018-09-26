/*
 * debug_rtt.h
 *
 *  Created on: Oct 27, 2016
 *      Author: rdu
 */

#ifndef MODULES_DEBUG_DEBUG_RTT_H_
#define MODULES_DEBUG_DEBUG_RTT_H_

// Add additional functions supported by RRT here
#ifdef ENABLE_SEGGER_RTT
#include "SEGGER_RTT.h"
#define RTT_printf SEGGER_RTT_printf
#else
#define RTT_printf
#endif

#endif /* MODULES_DEBUG_DEBUG_RTT_H_ */
