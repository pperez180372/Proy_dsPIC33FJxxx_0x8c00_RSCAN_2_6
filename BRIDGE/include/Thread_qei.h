#ifndef __THREAD_QEI_H__
#define __THREAD_QEI_H__

#include "thread_ecan.h"

//Comunicaciones
#define CANID_QEI1     ((long int)(ID_NODO|0x05))
#define CANID_QEI2     ((long int)(ID_NODO|0x06))
#define CANID_QEI_IN   ((long int)(ID_NODO|0x07))

#define BUFFER_CAN_QEI_IN 10   /* buffer de recepción */ 
#define BUFFER_CAN_QEI1   4    /* número buffer de transmisión  */
#define BUFFER_CAN_QEI2   5    /* número buffer de transmisión  */
#define FILTRO_CAN_QEI_IN 8    /* número de filtro de aceptacion de recepcion  */

//Tarea

#define QEI_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_QEI 	10 /* periodo 10 ms */
extern void vMAIN_Task_QEI( void *pvParameters ); /* thread */

//Variables compartidas

void Init_Geometry(int pulsesperrevolution,float radio);
extern float QEI_getPosition(int value); 
int QEI_getVelocity(int value); /* positivo o negativo */

// funciones internas;
void QEI_Init_var(void);
void Escribe_CAN_QEI_milimetros(void);
void Escribe_CAN_QEI_aux(void);
void Escribe_CAN_QEI_pulsos(void);


void Init_QEI_2_DSPIC33F32MC204 (void);
void Init_QEI_DSPIC33F32MC204 (void);
#endif
