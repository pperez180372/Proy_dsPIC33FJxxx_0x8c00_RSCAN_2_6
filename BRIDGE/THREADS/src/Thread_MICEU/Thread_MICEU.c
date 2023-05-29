#define _CAN1 //sólo un controlador es necesario para los defines de CAN

#include "FreeRTOS.h"
#include "semphr.h"
#include "CAN.h"
#include "CANTypes.h"

#include "CAN_DSPIC_33F_Stack.h"
#include "CAN_DSPIC_33F_Stack_Overflow.h"

#include "CAN_DSPIC_33F_Configuracion.h"
#include "util.h"
#include "handlers_can.h"



#include "Thread_MICEU.h"

// Dos semaforos binarios MICEU_SemLP, MICEU_SemHP

xSemaphoreHandle MICEU_SemLP;
xSemaphoreHandle MICEU_SemHP;

 

/* Comunicaciones */
int MICEU_CAN_Buffer[4];
int MICEU_CAN_Buffer_in[4];

void MICEU_Init_CAN()
{
	/* recepción */
	CAN_DSPIC33_Filter (CAN1,BUFFER_CAN_MICEU_IN,CANID_MICEU_IN,FILTRO_CAN_MICEU_IN,0); // filtro 0, mask exacto a buzon
	CAN_DSPIC33_Association_Filter_to_Handle(CAN1,BUFFER_CAN_MICEU_IN,(PT_HD )MICEU_procesa_CAN);
	CAN_DSPIC_33F_SetupMessage(CAN1,BUFFER_CAN_MICEU,CANID_MICEU,8,0, (char *)MICEU_CAN_Buffer);
}


void MICEU_Envia_CAN()
{
	CAN_DSPIC_33F_SetupMessage_sort(CAN1,BUFFER_CAN_MICEU,8,(char*)MICEU_CAN_Buffer);
	CAN_DSPIC_33F_SendMessage(CAN1,BUFFER_CAN_MICEU);
}

void MICEU_procesa_CAN(int nbuff)
{
//	int ct;
//	for (ct=0;ct<=7;ct++) 
//		*(((char *)CAN_QEI_Buffer)+ct)=*(((char *)buffer_CAN.DATA)+ct);
//PARPADEO_valor(0,3);
LED(5);
//void CAN_DSPIC_33F_Get_data_of_Message_buffer(CAN_MODULE module,int n_buff,int numini,int numfin,char * pt)
}
void MICEU_Escribe_CAN(void)
{
	int fg;
	for (fg=0;fg<4;fg++) 
		MICEU_CAN_Buffer[fg]=0;
}

void Thread_MICEU_Init( void)
{
	//portBASE_TYPE res_sem;
	int c;
	int fase;
	/* Used to wake the task at the correct frequency. */
	portTickType xLastExecutionTime;
    c=0;
	fase=0;

	//Init_CA();
	MICEU_Init_CAN();
	Init_MICEU_DSPIC33F128MC804();
	// debería dispararse constantemente 

	xLastExecutionTime = xTaskGetTickCount();
   	 
	fase=0;

	for( ;; )
	{	
		
		c++;		
		vTaskDelayUntil( &xLastExecutionTime, MAIN_TASK_MICEU );
	
		switch (fase)
		{

			case 0: // la fase 0 se desperdicia
					fase=1;
					break;
					
			case 1: // funcionamiento normal
					// Se programa el mensaje y se transmite
					// se interrupe la interrupciones
					portDISABLE_INTERRUPTS();
					// se copia el buffer
					// Se deberia filtrar 
					MICEU_Escribe_CAN(); // actualiza buffers
					// se habilita 
					portENABLE_INTERRUPTS();

					// se transmite
					MICEU_Envia_CAN();
					
					break;
		}

		
		c++;	
		
	}
}

void Init_MICEU_DSPIC33F128MC804(void)
{
//debe porgrsama para inicializar la conversion para que se realice periodicamente
}
