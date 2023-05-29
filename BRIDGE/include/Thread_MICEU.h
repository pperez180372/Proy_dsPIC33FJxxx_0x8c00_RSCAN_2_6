
#ifndef __THREAD_MICEU_H__
#define __THREAD_MICEU_H__

#include "thread_ecan.h"

//Comunicaciones
#define CANID_MICEU     ((long int)(ID_NODO|0x07))
#define CANID_MICEU_IN  ((long int)(ID_NODO|0x08))

#define BUFFER_CAN_MICEU_IN 14   /* buffer de recepción */ 
#define BUFFER_CAN_MICEU    1    /* número buffer de transmisión  */
#define FILTRO_CAN_MICEU_IN 6    /* número de filtro de aceptacion de recepcion  */

//Tarea

#define MICEU_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_MICEU	2 /* periodo 10 ms */
extern void vMAIN_Task_MICEU( void *pvParameters ); /* thread */


//comunicaciones 
void MICEU_procesa_CAN(int nbuff);
void Init_MICEU_DSPIC33F128MC804(void);



#endif
