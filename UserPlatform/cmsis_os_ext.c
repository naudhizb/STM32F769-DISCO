/*
 * cmsis_os_ext.c
 *
 *  Created on: 2019. 6. 23.
 *      Author: naudh
 */

#include <string.h>
#include "cmsis_os.h"

/*
 * ARM Compiler 4/5
 */
#if   defined ( __CC_ARM )

  #define __ASM            __asm
  #define __INLINE         __inline
  #define __STATIC_INLINE  static __inline

  #include "cmsis_armcc.h"

/*
 * GNU Compiler
 */
#elif defined ( __GNUC__ )

  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */
  #define __STATIC_INLINE  static inline

  #include "cmsis_gcc.h"


/*
 * IAR Compiler
 */
#elif defined ( __ICCARM__ )

  #ifndef   __ASM
    #define __ASM                     __asm
  #endif
  #ifndef   __INLINE
    #define __INLINE                  inline
  #endif
  #ifndef   __STATIC_INLINE
    #define __STATIC_INLINE           static inline
  #endif

  #include <cmsis_iar.h>
#endif


static int inHandlerMode (void)
{
  return __get_IPSR() != 0;
}

/**
* @brief Put a Message to a Queue.
* @param  queue_id  message queue ID obtained with \ref osMessageCreate.
* @param  info      message information.
* @param  millisec  timeout value or 0 in case of no time-out.
* @retval status code that indicates the execution status of the function.
* @note   MUST REMAIN UNCHANGED: \b osMessagePut shall be consistent in every CMSIS-RTOS.
*/
osStatus osQueuePut (osMessageQId queue_id, uint32_t *info, uint32_t millisec)
{
  portBASE_TYPE taskWoken = pdFALSE;
  TickType_t ticks;

  ticks = millisec / portTICK_PERIOD_MS;
  if (ticks == 0) {
    ticks = 1;
  }

  if (inHandlerMode()) {
    if (xQueueSendFromISR(queue_id, info, &taskWoken) != pdTRUE) {
      return osErrorOS;
    }
    portEND_SWITCHING_ISR(taskWoken);
  }
  else {
    if (xQueueSend(queue_id, info, ticks) != pdTRUE) {
      return osErrorOS;
    }
  }

  return osOK;
}

/**
* @brief Get a Message or Wait for a Message from a Queue.
* @param  queue_id  message queue ID obtained with \ref osMessageCreate.
* @param  millisec  timeout value or 0 in case of no time-out.
* @retval event information that includes status code.
* @note   MUST REMAIN UNCHANGED: \b osMessageGet shall be consistent in every CMSIS-RTOS.
*/
osEvent osQueueGet (osMessageQId queue_id, uint32_t *value, uint32_t millisec)
{
  portBASE_TYPE taskWoken;
  TickType_t ticks;
  osEvent event;

  event.def.message_id = queue_id;
  event.value.v = 0;

  if (queue_id == NULL) {
    event.status = osErrorParameter;
    return event;
  }

  taskWoken = pdFALSE;

  ticks = 0;
  if (millisec == osWaitForever) {
    ticks = portMAX_DELAY;
  }
  else if (millisec != 0) {
    ticks = millisec / portTICK_PERIOD_MS;
    if (ticks == 0) {
      ticks = 1;
    }
  }

  if (inHandlerMode()) {
    if (xQueueReceiveFromISR(queue_id, value, &taskWoken) == pdTRUE) {
      /* We have mail */
      event.status = osEventMessage;
      event.value.p = value;
    }
    else {
      event.status = osOK;
    }
    portEND_SWITCHING_ISR(taskWoken);
  }
  else {
    if (xQueueReceive(queue_id, value, ticks) == pdTRUE) {
      /* We have mail */
      event.status = osEventMessage;
      event.value.p = value;
    }
    else {
      event.status = (ticks == 0) ? osOK : osEventTimeout;
    }
  }

  return event;
}
