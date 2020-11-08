/*
 * Command_registercmd.c
 *
 *  Created on: 2019. 6. 14.
 *      Author: mjlee2
 */

#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "CLI_defs.h"

CLI_FUNCTION_DEF(hello)
{
	const char *pcParameterString;
//	uint8_t *pcEndString;
//	uint32_t del = 1;
	uint32_t num_of_param = 0;
	portBASE_TYPE xParameterStringLength;

	(void) pcParameterString;

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
	strcpy(pcWriteBuffer,"Hello world!\r\n");

	return pdFALSE;
}


void vRegisterCLICommands(){
	CLI_COMMAND_DEF(hello, Print Hello world string, 0);
	CLI_REGISTER_FUNCTION(hello);

	extern void vRegisterUtilityCommands();
	vRegisterUtilityCommands();
}

