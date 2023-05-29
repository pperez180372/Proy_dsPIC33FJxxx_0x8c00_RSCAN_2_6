#ifndef __THREAD_YAIR_VEL_H__
#define __THREAD_YAIR_VEL_H__

#include "thread_ecan.h"


//Tarea

#define YAIR_VEL_Task_PRIORITY	(tskIDLE_PRIORITY + 4 )
#define MAIN_TASK_YAIR_VEL	10 /* periodo 50 ms */
extern void vMAIN_Task_YAIR_VEL( void *pvParameters ); /* thread */


//comunicaciones 
void YAIR_VEL_procesa_CAN(int nbuff);
void Init_YAIR_VEL_DSPIC33F128MC804(void);
void YAIR_VEL_Escribe_BUFFER(void); // actualiza buffers


// CONVERSION 
#define FREQ_TIMER3		((unsigned long int)1000) // frecuencia en microsegundos

//variables 



extern float YAIR_VEL_0_ACT_MM_s;
extern float YAIR_VEL_0_ANT_MM_s;
extern float YAIR_VEL_0_AC_MM_s;

extern float YAIR_VEL_1_ACT_MM_s;
extern float YAIR_VEL_1_ANT_MM_s;
extern float YAIR_VEL_1_AC_MM_s;

extern long int YAIR_VEL_POS_1_ACT;
extern long int YAIR_VEL_POS_1_ANT;

extern long int YAIR_VEL_POS_0_ACT;
extern long int YAIR_VEL_POS_0_ANT;


void YAIR_VEL_Init_CAN();
void YAIR_VEL_Envia_CAN_1(int mapa);
void YAIR_VEL_procesa_CAN(int nbuff);
void YAIR_VEL_Escribe_CAN_generico_2_int(int a1,int a2);
void YAIR_VEL_Escribe_CAN_generico_float_int(float a1,int a2);
void YAIR_VEL_Escribe_CAN_generico_float_float(float a1,int a2);
void YAIR_VEL_Escribe_CAN_generico(int type,void * a1,void * a2);
void YAIR_VEL_Init_var(void);
void Init_Lineas_de_puenteH_1(void);
void Init_YAIR_VEL_1_DSPIC33F32MC204 (void);
void Init_Lineas_de_puenteH_2(void);
void Init_YAIR_VEL_2_DSPIC33F32MC204 (void);
void setOrientation_1(int value);
void setPotencia_1(int value);
void setOrientation_2(int value);
void setPotencia_2(int value);


#endif
