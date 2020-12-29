/*
 * Task_consoleRx.c
 *
 *  Created on: 2019. 7. 6.
 *      Author: mjlee2
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

#include <stdio.h>
#include <memory.h>
#include <string.h>

#include "UserPlatform.h"

static UART_HandleTypeDef *huart = &USER_CONSOLE_UART_HANDLE;
static DMA_HandleTypeDef *hdma = &USER_CONSOLE_UART_DMA_RX_HANDLE;

extern osMessageQId console_Rx_queueHandle;
static uint8_t rxbuf[256];

void StartConsoleRxTask(void const * argument)
{
	/* USER CODE BEGIN StartConsoleRxTask */
	const int dma_size = 256;
	static uint32_t prev_len = 0;
	static uint32_t curr_len = 0;
	memset(rxbuf, 0, sizeof(rxbuf));
	HAL_StatusTypeDef status;
	do{
		status = HAL_UART_Receive_DMA(huart, rxbuf, dma_size);
	} while(status != HAL_OK);

	/* Infinite loop */
	for(;;)
	{
		uint32_t PreviousWakeTime = osKernelSysTick();
		curr_len = dma_size - hdma->Instance->NDTR; // [0 255]

//		printf("%3lu/%3lu\n",curr_len, prev_len);
		while(curr_len != prev_len){
			osMessagePut(console_Rx_queueHandle, rxbuf[prev_len], 1000);
			prev_len++;
			if(prev_len == dma_size){
				prev_len = 0;
			}
		}
		osDelayUntil(&PreviousWakeTime, 100);

	}
	/* USER CODE END StartConsoleRxTask */
}
