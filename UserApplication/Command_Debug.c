/*
 * Command_Debug.c
 *
 *  Created on: 2019. 11. 5.
 *      Author: mjlee2
 */


#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>
#include "CLI_defs.h"

#include "printf.h"

CLI_FUNCTION_DEF(tasklist)
{
	const char *pcParameterString;
	uint8_t *pcEndString;
	portBASE_TYPE xParameterStringLength;
	int num_of_param = 0;

	for(int i = 1; i <= num_of_param; i++ ){
		/* Obtain the parameter string. */
		pcParameterString = FreeRTOS_CLIGetParameter
				(
						pcCommandString,		/* The command string itself. */
						i,						/* Return the first parameter. */
						&xParameterStringLength	/* Store the parameter string length. */
				);
		switch (i){
		case 1:
			strtoul(pcParameterString, (char **)&pcEndString, 10); // [0 115200]
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
	}

	memset(pcWriteBuffer, 0, xWriteBufferLen);

	strcat((char *) pcWriteBuffer, "\r\nName          State  Priority  Stack   Num" );
	strcat((char *) pcWriteBuffer, "\r\n---------------------------------------------\r\n");

	/* The list of tasks and their status */
	osThreadList((unsigned char *)(pcWriteBuffer + strlen(pcWriteBuffer)));
	strcat((char *) pcWriteBuffer, "\r\n\r\n---------------------------------------------");
	strcat((char *) pcWriteBuffer, "\r\nB : Blocked, R : Ready, D : Deleted, S : Suspended\r\n");

	return pdFALSE;
}

CLI_FUNCTION_DEF(heap){
	memset(pcWriteBuffer, 0, xWriteBufferLen);
	sprintf(pcWriteBuffer, "Minimal Heap Free size : %u", xPortGetMinimumEverFreeHeapSize());
	return pdFALSE;
}

CLI_FUNCTION_DEF(runtime){
	memset(pcWriteBuffer, 0, xWriteBufferLen);
	vTaskGetRunTimeStats(pcWriteBuffer+strlen(pcWriteBuffer));
	return pdFALSE;
}


void vRegisterCLICommands_Debug(){
	CLI_COMMAND_DEF(tasklist, Get task list and usage, 0);
	CLI_REGISTER_FUNCTION(tasklist);
	CLI_COMMAND_DEF(heap, Get minimal remaining heap size, 0);
	CLI_REGISTER_FUNCTION(heap);
	CLI_COMMAND_DEF(runtime, Get runtime stats, 0);
	CLI_REGISTER_FUNCTION(runtime);
}
