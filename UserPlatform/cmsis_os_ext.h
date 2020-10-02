/*
 * cmsis_os_ext.h
 *
 *  Created on: 2019. 6. 23.
 *      Author: naudh
 */

#ifndef INC_CMSIS_OS_EXT_H_
#define INC_CMSIS_OS_EXT_H_

#include "cmsis_os.h"

osStatus osQueuePut (osMessageQId queue_id, uint32_t *info, uint32_t millisec);
osEvent osQueueGet (osMessageQId queue_id, uint32_t *value, uint32_t millisec);



#endif /* INC_CMSIS_OS_EXT_H_ */
