/*
 * UserPlatform.h
 *
 *  Created on: Oct 2, 2020
 *      Author: naudh
 */

#ifndef USERPLATFORM_H_
#define USERPLATFORM_H_

#include "main.h"
#include "stm32f7xx_hal.h"

#include "printf.h"
#include "cmsis_os.h"
#include "cmsis_os_ext.h"


#define USER_CONSOLE_UART_HANDLE  			huart1
#define USER_CONSOLE_UART_DMA_RX_HANDLE 	hdma_usart1_rx
#define USER_CONSOLE_TIMEOUT				10

extern UART_HandleTypeDef USER_CONSOLE_UART_HANDLE;
extern DMA_HandleTypeDef USER_CONSOLE_UART_DMA_RX_HANDLE;
//static UART_HandleTypeDef *huart = &USER_CONSOLE_UART_HANDLE;

#endif /* USERPLATFORM_H_ */
