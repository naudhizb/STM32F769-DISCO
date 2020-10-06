/*
 * Command_Utility.c
 *
 *  Created on: 2020. 10. 6.
 *      Author: naudh
 */

#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "CLI_defs.h"

#include "cpu_utils.h"

CLI_FUNCTION_DEF(CPU_Usage)
{
	const char *pcParameterString;
//	uint8_t *pcEndString;
//	uint32_t del = 1;
	uint32_t num_of_param = 0;
	portBASE_TYPE xParameterStringLength;

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
//			del = strtoul(pcParameterString, (char **)&pcEndString, 10); // [0 24]
			break;
		default:
			break;
		}
	}

	sprintf(pcWriteBuffer,"CPU Usage:%u\r\n", osGetCPUUsage());

	return pdFALSE;
}


void vRegisterUtilityCommands(){
	CLI_COMMAND_DEF(CPU_Usage, Print Current CPU Usage, 0);
	CLI_REGISTER_FUNCTION(CPU_Usage);
}

