#ifndef __THREAD_BRIDGE_H__
#define __THREAD_BRIDGE_H__

#include "FreeRTOS.h"

//Tarea

#define BRIDGE_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
void BRIDGE_vMAIN_Task_TX(void *pvParameters );

#define BRIDGE_MAIN_TASK	50 /* periodo 10 ms */


//comunicaciones 

void BRIDGE_procesa_CAN(int nbuff);
void BRIDGE_Init0(void);
void BRIDGE_Escribe_BUFFER(void); // actualiza buffers

//internal
#define Serial_MSG_MAXBUFFER (11*2)
unsigned char hex(int x,int y);   /*prepara los caracteres del fichero para su envio*/
int BRIDGE_Analysis_Serial_MSG(void);
#endif 
