/*
 * FreeRTOS_RuntimeStatistic.c
 *
 *  Created on: 2018. 8. 6.
 *      Author: mjlee2
 */
#include "main.h"
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"

// Min stack for : http://blog.atollic.com/how-to-debug-freertos-projects-on-arm-cortex-m-devices
// For Runtime Stat, please refer http://blog.atollic.com/visualizing-run-time-statistics-using-freertos
/* note : need to declare ulTotalRuntime as a volatile in tasks.c:419-420 */
/*  OR  : disable optimization tasks.c */
static TIM_HandleTypeDef htim5; // is one of 32bit timer in stm32f7
static TIM_HandleTypeDef *htim = &htim5;


static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 216-1;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}


void configureTimerForRunTimeStats(void)
{
	MX_TIM5_Init();
	HAL_TIM_Base_Start(htim);
}

unsigned long getRunTimeCounterValue(void)
{
	return htim->Instance->CNT;
}

