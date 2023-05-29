#ifndef __THREAD_CAD_H__
#define __THREAD_CAD_H__

#include "thread_ecan.h"

//Comunicaciones
#define CANID_CAD     ((long int)(ID_NODO|0x01))
#define CANID_CAD_IN  ((long int)(ID_NODO|0x02))

#define BUFFER_CAN_CAD_IN 12   /* 8 <= 15 buffer de recepción */ 
#define BUFFER_CAN_CAD    7    /* hasta el <8 número buffer de transmisión  */
#define FILTRO_CAN_CAD_IN 10    /* < 16 número de filtro de aceptacion de recepcion  */

//Tarea

#define CAD_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_CAD 	10 /* periodo 50 ms 20Hz */
extern void vMAIN_Task_CAD ( void *pvParameters ); /* thread */

extern float CAD_getGrados_X();
extern float CAD_getGrados_Y();


#endif
