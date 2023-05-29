#include "CAN_DSPIC_33F_Stack.h"
#include "can_scocan.h"
#include "FreeRTOS.h"
#include "CAN_DSPIC_33F_Stack.h"
int ga1,gb1,ga2,gb2;

int CAN_DSPIC_33F_Overflow(CAN_MODULE module)
{

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;
	
	// cambiar a window 0
	canRegisters->CONF.CTRL1.WIN = 0;
	ga1=canRegisters->WIN.W_0.RXOVF1;
	gb1=canRegisters->WIN.W_0.RXOVF2;

	canRegisters->WIN.W_0.RXOVF1=0x0000;
	canRegisters->WIN.W_0.RXOVF2=0x0000;

	ga2=canRegisters->WIN.W_0.RXOVF1;
	gb2=canRegisters->WIN.W_0.RXOVF2;


	
	return OK;

}

