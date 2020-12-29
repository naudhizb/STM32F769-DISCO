/*
 * printf_platform.c
 *
 *  Created on: Oct 2, 2020
 *      Author: naudh
 */


#include "UserPlatform.h"


static UART_HandleTypeDef *huart = &USER_CONSOLE_UART_HANDLE;

void _putchar(char character)
{
	// send char to console etc.
	HAL_UART_Transmit(huart, (uint8_t *)&character, sizeof(character), USER_CONSOLE_TIMEOUT);
	if(character == '\n'){
		static const char cr = '\r';
		HAL_UART_Transmit(huart, (uint8_t *)&cr, sizeof(cr), USER_CONSOLE_TIMEOUT);
	}
}
