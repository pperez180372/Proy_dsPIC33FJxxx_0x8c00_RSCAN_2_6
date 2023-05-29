
#ifndef __THREAD_PWM_H__
#define __THREAD_PWM_H__

#include "thread_ecan.h"

//Comunicaciones
#define CANID_PWM     ((long int)(ID_NODO|0x03))
#define CANID_PWM_1   ((long int)(ID_NODO|0x0A))
#define CANID_PWM_IN  ((long int)(ID_NODO|0x04))

#define BUFFER_CAN_PWM_IN 11   /* buffer de recepción */ 
#define BUFFER_CAN_PWM    6    /* número buffer de transmisión  */
#define BUFFER_CAN_PWM_1  2    /* número buffer de transmisión  */
#define FILTRO_CAN_PWM_IN 9    /* número de filtro de aceptacion de recepcion  */

//Tarea

#define PWM_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_PWM 	2 /* periodo 10 ms */
extern void vMAIN_Task_PWM( void *pvParameters ); /* thread */

//Syncronization
 extern xSemaphoreHandle PWM_Sem;



extern void PWM_procesa_CAN(int nbuff);
extern void PWM_Escribe_CAN(void);
void PWM_Escribe_CAN_generico(int type,void * a1,void * a2);





extern int PWMresolution; /* almacena el valor máximo del duty cicle */
extern xSemaphoreHandle MAIN_Sem;

void Init_Lineas_de_puenteH_1(void);
void Init_Lineas_de_puenteH_2(void);
void Init_PWM_1_DSPIC33F32MC204 (void);
void Init_PWM_2_DSPIC33F32MC204 (void); 


void setOrientation_1(int value); /* entre 0 y 100 */
void setPotencia_1(int value); /* positivo o negativo */
void setOrientation_2(int value); /* entre 0 y 100 */
void setPotencia_2(int value); /* positivo o negativo */


/* Comunicaciones */
extern int PWM_CAN_Buffer[4];
extern int PWM_CAN_Buffer_1[4];
extern int PWM_CAN_Buffer_in[4];

// Variables

extern int num_messages_rec;

extern float PID_position_1_ref;
extern float PID_position_2_ref;
extern 	float error_2;
	extern float posicion_2;
	extern float error_1;
	extern float posicion_1;
	extern float vsenyal_1,vsenyal_2;




void vMAIN_Task_PWM_AJUSTE(void *pvParameters );
void vMAIN_Task_PWM_PID(void *pvParameters );
void vMAIN_Task_PWM_Pendulo(void *pvParameters );

void PWM_Init_var(void);
void PWM_Init_CAN();
void PWM_Envia_CAN();
void PWM_Envia_CAN_1(int mapa);
void PWM_procesa_CAN(int nbuff);


void PWM_Escribe_CAN_position();
void PWM_Escribe_CAN_generico();
void PWM_Escribe_CAN_accion_de_control();
void PWM_Escribe_CAN_error();
void PWM_Escribe_CAN_contador(int c,int t);
void PWM_Escribe_CAN_AJUSTE(void);




#endif
