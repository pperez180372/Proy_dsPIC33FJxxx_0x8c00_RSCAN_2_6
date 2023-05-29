#ifndef __CAN_DSPIC_33F_STACK_OVERFLOW_H__
#define __CAN_DSPIC_33F_STACK_OVERFLOW_H__
/* Este fichero contiene las funciones de la pila CAN para tratar 
el estado de overflow */

#include "CAN_DSPIC_33F_Stack.h"
#include "can_scocan.h"
#include "FreeRTOS.h"
#include "CAN_DSPIC_33F_Stack.h"


int CAN_DSPIC_33F_Overflow(CAN_MODULE module);
#endif
