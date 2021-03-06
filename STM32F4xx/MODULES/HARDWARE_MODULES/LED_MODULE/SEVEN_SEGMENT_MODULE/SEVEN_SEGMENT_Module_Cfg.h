/*
 * 7SEGMENT_Module_Cfg.h
 *
 *  Created on: Sep 11, 2018
 *      Author: zsolt.balo
 */

#ifndef MODULES_HARDWARE_MODULES_LED_MODULE_SEVEN_SEGMENT_MODULE_SEVEN_SEGMENT_MODULE_CFG_H_
#define MODULES_HARDWARE_MODULES_LED_MODULE_SEVEN_SEGMENT_MODULE_SEVEN_SEGMENT_MODULE_CFG_H_

#include "SEVEN_SEGMENT_Module.h"

#define SEVEN_SEGMENT_MODULE_INTERFACE 							SEVEN_SEGMENT_MODULE_SHIFT_REGISTER_INTERFACE
#define SEVEN_SEGMENT_MODULE_INSTANCE_NUM 						((uint32)0x01)

typedef enum
{
	SEVEN_SEGMENT_MODULE_0
}
SEVEN_SEGMENT_Module_Instances;

#endif /* MODULES_HARDWARE_MODULES_LED_MODULE_SEVEN_SEGMENT_MODULE_SEVEN_SEGMENT_MODULE_CFG_H_ */
