#ifndef __THREAD_ECAN_H__
#define __THREAD_ECAN_H__

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

//public 

//Comunicaciones
#define CANID_ECAN     ((long int)(ID_NODO|0x08))
#define CANID_ECAN_IN  ((long int)(ID_NODO|0x09))

#define BUFFER_CAN_ECAN_IN  9   /* 8 <= 15 buffer de recepción */ 
#define BUFFER_CAN_ECAN     3    /* hasta el <8 número buffer de transmisión  */
#define FILTRO_CAN_ECAN_IN 11    /* < 16 número de filtro de aceptacion de recepcion  */


void Thread_ecan_Init( void);


// private 
#define vECAN_HP_Task_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define vECAN_LP_Task_PRIORITY				( tskIDLE_PRIORITY + 3 )

#define vECAN_HP_Task_PERIOD				( ( portTickType ) 3000 / portTICK_RATE_MS )
#define vECAN_LP_Task_PERIOD				( ( portTickType ) 3000 / portTICK_RATE_MS )

#define vECAN_HP_Task_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )
#define vECAN_LP_Task_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )


 void vECAN_LP_Task( void *pvParameters );
 void vECAN_HP_Task( void *pvParameters );


 // definiciones de mensajes a nivel de aplicación

#define ID_PT_PROC	 0x0300   // identificador de baja prioridad para realizar operaciones sobre SFR
#define ID_PT_PROC_R 0x0301   // identificador de baja prioridad para realizar operaciones sobre SFR

#define ID_LED_LP   0x0200   // ejemplo: LP para escribir en los leds
#define ID_LED_HP	0x0150	 // ejemplo: mensaje de HP



#define ID_CAD1	    ID_NODO|0x00   /* identificador de baja prioridad para realizar operaciones sobre SFR*/
#define ID_PWM1     ID_NODO|0x01
#define ID_QEI1     ID_NODO|0x02


void procesa_pt(int nbuf);
void escribe_led_lp(int value);
void escribe_led_hp(int value);

#define OP_NORMAL_NOP 	0x00
#define OP_NORMAL_RD 	0x01
#define OP_NORMAL_WR 	0x02
#define OP_MASK			0x0F
#define TYPE_MASK		0xF0
#define TYPE_BYTE		0x10 // tipo de dato para copiar 1 2 3, 4 o mas valores
#define TYPE_16BIT		0x20
#define TYPE_32BIT		0x30
#define TYPE_FLOAT		0x40
#define TYPE_ADDRESS	0x50

#endif
