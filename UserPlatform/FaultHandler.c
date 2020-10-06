/*
 * FaultHandler.c
 *
 *  Created on: 2018. 8. 6.
 *      Author: mjlee2
 */

#include "main.h"
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "printf.h"
#include <stdio.h>
#include <string.h>


/* Low Level Fault Interrupt Hook */
#if 1
#define dt_dprintf(...) printf(__VA_ARGS__)
#else
#define dt_dprintf(...) {\
	extern UART_HandleTypeDef huart1;\
	char buf[160] = {0,};\
	sprintf(buf, __VA_ARGS__);\
	(&huart1)->Lock = HAL_UNLOCKED;\
	HAL_UART_Transmit(&huart1, (uint8_t *)buf, strlen(buf), 1000);\
}
#endif

void hard_fault_handler_c (unsigned int * hardfault_args)
{
 unsigned int stacked_r0;
 unsigned int stacked_r1;
 unsigned int stacked_r2;
 unsigned int stacked_r3;
 unsigned int stacked_r12;
 unsigned int stacked_lr;
 unsigned int stacked_pc;
 unsigned int stacked_psr;

 stacked_r0 = ((unsigned long) hardfault_args[0]);
 stacked_r1 = ((unsigned long) hardfault_args[1]);
 stacked_r2 = ((unsigned long) hardfault_args[2]);
 stacked_r3 = ((unsigned long) hardfault_args[3]);

 stacked_r12 = ((unsigned long) hardfault_args[4]);
 stacked_lr = ((unsigned long) hardfault_args[5]);
 stacked_pc = ((unsigned long) hardfault_args[6]);
 stacked_psr = ((unsigned long) hardfault_args[7]);

 dt_dprintf ("\r\n\r\n[Hard fault handler - all numbers in hex]\r\n");
 dt_dprintf ("R0  = 0x%08x\r\n", stacked_r0);
 dt_dprintf ("R1  = 0x%08x\r\n", stacked_r1);
 dt_dprintf ("R2  = 0x%08x\r\n", stacked_r2);
 dt_dprintf ("R3  = 0x%08x\r\n", stacked_r3);
 dt_dprintf ("R12 = 0x%08x\r\n", stacked_r12);
 dt_dprintf ("LR [R14] = 0x%08x  subroutine call return address\r\n", stacked_lr);
 dt_dprintf ("PC [R15] = 0x%08x  program counter\r\n", stacked_pc);
 dt_dprintf ("PSR  = 0x%08x\r\n", stacked_psr);
 dt_dprintf ("BFAR = 0x%08x\r\n", (*((volatile unsigned int *)(0xE000ED38))));
 dt_dprintf ("CFSR = 0x%08x\r\n", (*((volatile unsigned int *)(0xE000ED28))));
 dt_dprintf ("HFSR = 0x%08x\r\n", (*((volatile unsigned int *)(0xE000ED2C))));
 dt_dprintf ("MMAR = 0x%08x\r\n", (*((volatile unsigned int *)(0xE000ED34))));
 dt_dprintf ("AFSR = 0x%08x\r\n", (*((volatile unsigned int *)(0xE000ED3C))));
 dt_dprintf ("SCB_SHCSR = 0x%x\r\n", *((volatile unsigned int *)(&(SCB->SHCSR))));

while (1);
}

/* The prototype shows it is a naked function - in effect this is just an
assembly function. */
void HardFault_Handler( void ) __attribute__( ( naked ) );

void HardFault_Handler(void)
{
 __asm__ __volatile__ (
 "   tst     lr, #0x4            \n\t"
 "   ite     eq                  \n\t"
 "   mrseq   r0, msp             \n\t"
 "   mrsne   r0, psp             \n\t"
 "   b   hard_fault_handler_c           \n\t");
}







/* FreeRTOS Failure Hook */

void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
	printf("STACK OVERFLOW detected!\n");
}

void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
	printf("MALLOC FAILED detected!\n");
}
