#ifndef __THREAD_SERVOS_H__
#define __THREAD_SERVOS_H__

#include "thread_ecan.h"


//Tarea

#define SERVOS_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_SERVOS	1000 /* periodo 50 ms */ 
extern void vMAIN_Task_SERVOS( void *pvParameters ); /* thread */

//  COMUNICACIONES 
void SERVOS_procesa_CAN(int nbuff);
void Init_SERVOS(void);



#endif
