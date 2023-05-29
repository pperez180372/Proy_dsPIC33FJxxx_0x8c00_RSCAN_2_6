
#ifndef __THREAD_INFRA_H__
#define __THREAD_INFRA_H__

#include "thread_ecan.h"


//Tarea

#define INFRA_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_INFRA	50 /* periodo 10 ms */
extern void vMAIN_Task_INFRA( void *pvParameters ); /* thread */


//comunicaciones 
void INFRA_procesa_CAN(int nbuff);
void Init_INFRA_DSPIC33F128MC804(void);
void INFRA_Escribe_BUFFER(void); // actualiza buffers


// CONVERSION 
#define FREQ_TIMER3		((unsigned long int)1000) // frecuencia en microsegundos


#endif
