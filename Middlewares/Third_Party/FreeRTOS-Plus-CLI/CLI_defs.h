/*
 * CLI_defs.h
 *
 *  Created on: 2018. 7. 17.
 *      Author: mjlee2
 */

#ifndef INC_CLI_DEFS_H_
#define INC_CLI_DEFS_H_

//#include "cmsis_os.h"
#include "FreeRTOS_CLI.h"
#include <stdlib.h>


#define CLI_COMMAND_DEF(name, description, num_of_param) \
	static const CLI_Command_Definition_t x##name = \
	{\
		#name,\
		#name" : \r\n\t"#description"\r\n", \
		&prv##name, \
		num_of_param \
	}
#define CLI_COMMAND_DEF_ALIAS(alias, name, description, num_of_param) \
	static const CLI_Command_Definition_t x##alias = \
	{\
		#alias,\
		#alias" : "#description" acronyum of "#name, \
		&prv##name, \
		num_of_param \
	}
#define CLI_FUNCTION_DEF(name) static BaseType_t prv##name( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
#define CLI_REGISTER_FUNCTION(name) (void)FreeRTOS_CLIRegisterCommand(&x##name)

//#define CLI_PRINT_COPY(buf)			memcpy(pcWriteBuffer, 					 buf, strlen((char *)buf))
//#define CLI_PRINT_ATTACH(buf)		memcpy(pcWriteBuffer+strlen((char *)pcWriteBuffer), buf, strlen((char *)buf))
//#define CLI_SPRINTF_ATTACH(...) 	sprintf(pcWriteBuffer+strlen(pcWriteBuffer), __VA_ARGS__)
#endif /* INC_CLI_DEFS_H_ */
