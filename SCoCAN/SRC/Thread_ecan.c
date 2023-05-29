#define _CAN1 //sólo un controlador es necesario para los defines de CAN


#include "FreeRTOS.h"
#include "semphr.h"


#include "message_id.h"

#include "can_scocan.h"
#include "CANTypes.h"

#include "CAN_DSPIC_33F_Stack.h"
#include "CAN_DSPIC_33F_Stack_Overflow.h"

#include "CAN_DSPIC_33F_Configuracion.h"
#include "util.h"
#include "handlers_can.h"
#include "Thread_ecan.h"

// MONITORIZAR EL LUGAR DE LA EXCEPCION
int g_LUGAR=0;


// Dos semaforos binarios ECAN_SemLP, ECAN_SemHP

xSemaphoreHandle ECAN_SemLP;
xSemaphoreHandle ECAN_SemHP;

int word_re1; // para depuración
int word_re2; // para depuración 

// funciones manejadoras de los mensajes 

int HP_Mesg_Proc_1(void * arg);
int LP_Mesg_Proc(void * arg);

void procesa_pt_WR(int nbuf);
void procesa_pt_RD(int nbuf);


 
// Dos semaforos binarios MAIN_Sem;
extern xSemaphoreHandle MAIN_Sem;

//unsigned int BufferSamplesA[4] __attribute__((space(dma)));

void ECAN_procesa_CAN(int nbuff);

/* Comunicaciones */
int ECAN_CAN_Buffer[4];
int ECAN_CAN_Buffer_in[4];

void ECAN_Init_CAN()
{
	/* recepción */
	CAN_DSPIC33_Filter (CAN1,BUFFER_CAN_ECAN_IN,CANID_ECAN_IN,FILTRO_CAN_ECAN_IN,0); // filtro 0, mask exacto a buzon
	CAN_DSPIC33_Association_Filter_to_Handle(CAN1,BUFFER_CAN_ECAN_IN,(PT_HD )ECAN_procesa_CAN);
	CAN_DSPIC_33F_SetupMessage(CAN1,BUFFER_CAN_ECAN,CANID_ECAN,8,0, (char *)ECAN_CAN_Buffer);
	
}

void ECAN_Envia_CAN()
{
	CAN_DSPIC_33F_SetupMessage_sort(CAN1,BUFFER_CAN_ECAN,8,(char*)ECAN_CAN_Buffer);
	CAN_DSPIC_33F_SendMessage(CAN1,BUFFER_CAN_ECAN);
}

void ECAN_procesa_CAN(int nbuff)
{
//	int ct;
//	for (ct=0;ct<=7;ct++) 
//		*(((char *)CAN_QEI_Buffer)+ct)=*(((char *)buffer_CAN.DATA)+ct);
//PARPADEO_valor(0,3);
PT_HD pt_func;

LED(5);
portDISABLE_INTERRUPTS();

pt_func=(PT_HD) 0x00000000;
(*pt_func)((void *)0x000000);

//void CAN_DSPIC_33F_Get_data_of_Message_buffer(CAN_MODULE module,int n_buff,int numini,int numfin,char * pt)
}
void ECAN_Escribe_CAN_samples()
{
	int fg;
	for (fg=0;fg<4;fg++) 
		ECAN_CAN_Buffer[fg]=0;//BufferSamplesA[fg];
}


int CAN_DSPIC33_Disable_Reset_interrupts_Stack(CAN_MODULE module);

void SCoCAN_Reinit_FSM(char car)
{
    static int FSM=0;
    static int BR=0;
    FSM_init:
    switch (FSM) 
    {
        case 0: if (car=='>') FSM=1;
                break;
        case 1: if (car=='I') FSM=2;
                else
                    {
                        FSM=0;
                        goto FSM_init;
                    }
                break;
        case 2: if ((car>='0')&&(car<='9')) {
            BR=car-48;
                FSM=3;
                }
                else
                {
                    FSM=0;
                    goto FSM_init;
                }
                break;
        case 3: if (car=='<')
                {
                    CAN_DSPIC33_Disable_Reset_interrupts_Stack(CAN1);
                    CAN_DSPIC33_SetOperatingMode(CAN1,CAN_CONFIGURATION);//CAN_NORMAL_OPERATION);
                    printf("Reinit_SCoCAN on %x BR\n",BR)	;
                    CAN_DSPIC_33F_Init(CAN1, BR);	
                    CAN_DSPIC33_SetOperatingMode(CAN1,CAN_NORMAL_OPERATION);
                    CAN_DSPIC33_Enable_interrupts_Devices(CAN1);
                    printf("ECAN Restarted\n")	;                
                    FSM=0;
                }
                else 
                {
                    FSM=0;
                    goto FSM_init;
                }
                break;
        default: FSM=0;
    }
}  
    
   

void Thread_ecan_Init( void)
{

// iniciliza el servicio de comunicaciones CAN
// crea las dos tareas 
//dos threads uno con una cola y otra que ejecute funciones en función del identificador.
// interfaz para dar de alta funciones y activar los filtros correspondientes.
// 4 de alta prioridad de 4 de baja prioridad

	vSemaphoreCreateBinary( ECAN_SemLP );
	if (ECAN_SemLP==NULL) // puede dar error 
		while(1);	
	vSemaphoreCreateBinary( ECAN_SemHP );	
	if (ECAN_SemHP==NULL) // puede dar error 
		while(1);


	CAN_DSPIC33_SetOperatingMode(CAN1,CAN_CONFIGURATION);
	while(CAN_DSPIC33_GetOperatingMode(CAN1)!=CAN_CONFIGURATION);
	
//    printf("INIT ECAN on 250Kbits\n");
//	CAN_DSPIC_33F_Init(CAN1,  BR_250kbits);	
    printf("INIT ECAN on 250Kbits\n");
	CAN_DSPIC_33F_Init(CAN1, BR_250kbits);	

	// configuración de los mensajes 
	// mensaje para transmitir, sirve de ejemplo, mensaje de longitud 0 en el buffer 0 
	//CAN_DSPIC_33F_SetupMessage(CAN1,0,0x301,0,0, NULL);
	// mensaje para recibir LP, las cola

	{
	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[CAN1];
	canRegisters->CONF.FEN1=0X0000;
	canRegisters->CONF.FMSKSEL1=0;
	canRegisters->CONF.FMSKSEL2=0;
	 
		canRegisters->CONF.CTRL1.WIN = 0;		

	canRegisters->WIN.W_0.RXFUL1=0;
	canRegisters->WIN.W_0.RXFUL2=0;

	}		

	/* Se asocia un filtro y una mascara */
    /* ENTRE 8-14 MASCARA EXACTA */ 
	//CAN_DSPIC33_Filter (CAN1,10,0x10,6,1); // filtro 0, mask exacto a buzon
	// BLOQUEO!!!!! Configurandolo en el buffer 10 y recibiendo dos mensajes consecutivos
	// salta la interrupción y se queda bloqueado. 

/*
	CAN_DSPIC33_Filter (CAN1,15,ID_CAD1,6,0); // filtro 0, mask exacto a buzon
	CAN_DSPIC33_Filter (CAN1,15,ID_PWM1,7,0); // filtro 0, mask exacto a buzon
	CAN_DSPIC33_Filter (CAN1,15,ID_QEI1,8,0); // filtro 0, mask exacto a buzon
*/

	//ff();

/* la mascara 1 (acepta todos) funciona 
	//CAN_DSPIC33_Filter (CAN1,15,0x301,11,1); // filtro 0, mask exacto a buzon
	PARPADEO_valor(0,2);

	//filter FEN1 parece que funciona 
	//CAN_DSPIC33_Filter (CAN1,15,0x310,1,2); // filtro 1, mask besteffor a fifo
	//PARPADEO_valor(0,3);
	//CAN_DSPIC33_Filter (CAN1,15,0x311,2,2); // filtro 2, mask besteffor a fifo.
	PARPADEO_valor(0,4);
	// revisar la interrupcion 
	// LAS INTERRUPCIONES SE PRODUCEN EN FUNCION DEL CONTENIDO DE LOS BUFFERS
	//	revisar esta funcion -->
	// asociar buffer a handle


	{ // asocia a los bufferes de 16-32 la misma funcion
	  // los bufferes de 16-32 son para FIFO
		int ct;
		for (ct=16;ct<32;ct++)
			CAN_DSPIC33_Association_Filter_to_Handle(CAN1,ct,LP_Mesg_Proc);
	}
*/
	// mensaje para recibir HP invocará a una función 
	//CAN_DSPIC33_Filter (CAN1,0,0x200);
	//CAN_DSPIC33_Association_Filter_to_Handle(CAN1,0,HP_Mesg_Proc_1);
	// mensaje para recibir LP con mascara general
	//CAN_DSPIC33_Filter (CAN1,15,0x310);
	//CAN_DSPIC33_Association_Filter_to_Handle(CAN1,15,LP_Mesg_Proc);

	xTaskCreate( vECAN_HP_Task, ( signed char * ) "ECAN_HP", vECAN_HP_Task_STACK_SIZE, NULL, vECAN_HP_Task_PRIORITY, NULL );
	xTaskCreate( vECAN_LP_Task, ( signed char * ) "ECAN_LP", vECAN_LP_Task_STACK_SIZE, NULL, vECAN_LP_Task_PRIORITY, NULL );

	// SI SE INICIALIZA EL CONTROLADOR LAS INTERRUPCIONES LLEGARAN ANTES DE QUE SE PUEDAN PROCESAR POR LAS TAREAS
	//CAN_DSPIC33_SetOperatingMode(CAN1,CAN_NORMAL_OPERATION);
	//CAN_DSPIC33_Enable_interrupts_Devices(CAN1);




	
}

void vECAN_LP_Task( void *pvParameters )
{
  	portBASE_TYPE res_sem;
	int nbuff,res;
//	char buffer[]={0,0xFC,2,3,4,2,1,0xfe,0x33};
	int c;
    int ctx;

c=0;
	//CAN_DSPIC_33F_SetupMessage(CAN1,0,0x029,8,0, buffer);

	CAN_DSPIC33_SetOperatingMode(CAN1,CAN_NORMAL_OPERATION);
	CAN_DSPIC33_Enable_interrupts_Devices(CAN1);


	/* crear una funcion para saltar al bootloader */
	ECAN_Init_CAN();
	
	for( ;; )
	{
		
		res_sem=xSemaphoreTake( ECAN_SemLP, 10000 / portTICK_RATE_MS );   // cada dos segundos se despierta por si acaso
		if (CAN_DSPIC33_GetOperatingMode(CAN1)!= CAN_NORMAL_OPERATION)
		{
            printf("LP: CAN en modo configuración\n");
        	continue; // no hace nada hasta que can no este operativo	
        }
		C1CTRL1bits.WIN=0x0;
		if (C1RXFUL2&0xFFFF)
			nbuff=CAN_DSPIC_33F_get_first_buffer_busy_in_FIFO(CAN1);
		else
			nbuff=ERROR;

		if (nbuff!=ERROR)
		{
			
			
			//PARPADEO_valor(0,(nbuff>>2));
		    //PARPADEO_valor(0,2);		
			//escribe_led_lp(nbuff%4);
			c=(c+1)%4;		
		/*		*(((int*)buffer)+0)=0xA0;
				*(((int*)buffer)+1)=nbuff;
				*(((int*)buffer)+2)=(int)((id_func_handlers[CAN1][8]))&0xFFFF;
				*(((int*)buffer)+3)=(((long int)(((id_func_handlers[CAN1][8]))))>>8)&0xFFFF;
				CAN_DSPIC_33F_SetupMessage_sort(CAN1,0,8,buffer);
				CAN_DSPIC_33F_SendMessage(CAN1,0);
		*/	
//deberia haber dos niveles el manejador para la fifo, 
//el manejador para el buffer por encima del 14 
//y una vez se salta a este se analiza el id y 
//si esta registrado se salta al manejador adecuado 
//vamos a ello
//1.- reducir los manejador a 16 uno por cada filtro, ahora hay 32 
//2.- crear un vector que el gestor de la fifo recorra para identificar los id en lp _ECAN, es decir aqui*/



//se ssupone que los id_func_handler pueden llegar a ser 32 es por los bufferes,
//son independientes, o es un error.

	// dado que por encima del buffer 15 va a una fifo fijarlo ahora se trata de ver si el ID del buffer
	// se ha de tratar 

		unsigned long IDFIFO=CAN_DSPIC_33F_Get_Message_ID_in_FIFO(CAN1,nbuff);

        
		for (ctx=0;ctx<MAX_MESSAGES_FUNC_FIFO;ctx++)
		{
			if (id_variables[CAN1][ctx]==IDFIFO)
				{
					res=(*id_variables_ptfunc[CAN1][ctx])((void *)nbuff);
                    break;
				}
		}
        
        // si la mascara asociada al filtro es la 1 es decir no importa debería saltarse si o si a una función generica
        // dos formas:  
        // 1 verificar la mascara y confirmar la 1 y saltar a la funcion generica
        // 2 si se ha aceptado un mensaje y no se corresponde con nigun id registrado saltar a la generica... entra en conflicto con la mascara best effort 2     
        

        // implmentado la segunda forma.
        
        if (ctx==MAX_MESSAGES_FUNC_FIFO)
        {
             if (id_default_ptfunc[CAN1]!=NULL)
                res=(*id_default_ptfunc[CAN1])((void *)nbuff);
        }
        
		CAN_DSPIC_33F_Release_buffer_in_FIFO(CAN1,nbuff); // se da como procesado 
		
		}

 	/*if (nbuff!=ERROR)
		{
		    PARPADEO_valor(0,nbuff);		
			CAN_DSPIC_33F_Release_buffer_in_FIFO(CAN1,nbuff); // se da como procesado 
		
		}	
*/
	}

}
extern 	int 	g_nint;
void vECAN_HP_Task( void *pvParameters )
{
	portBASE_TYPE res_sem;
	int nbuff;
	//INT res;
	int c;
	PT_HD pt_func;
	c=0;
	//CAN_DSPIC_33F_SetupMessage(CAN1,0,0x029,8,0, buffer);
	int word;
	

CAN_DSPIC33_SetOperatingMode(CAN1,CAN_NORMAL_OPERATION);
	CAN_DSPIC33_Enable_interrupts_Devices(CAN1);



	for( ;; )
	{
		//LED(4);
		res_sem=xSemaphoreTake( ECAN_SemHP, 10000 / portTICK_RATE_MS );   // cada dos segundos se despierta por si acaso
		g_nint--;
		//LED(3);

		if (CAN_DSPIC33_GetOperatingMode(CAN1)!= CAN_NORMAL_OPERATION)
		{
            printf("HP: CAN en modo configuración\n");
        	continue; // no hace nada hasta que can no este operativo	
        }
		C1CTRL1bits.WIN=0x0;
		if (C1RXFUL1&0xFF00)
		{
			C1CTRL1bits.WIN=0x0;
			word=C1RXFUL1;
			word_re1=word;

			nbuff=-1;
			if (word&0x8000) {C1RXFUL1=word&(~0x8000); nbuff=15; goto salto1;} 
			if 	(word&0x4000) {C1RXFUL1=word&(~0x4000); nbuff=14; goto salto1;} 
			if (word&0x2000) {C1RXFUL1=word&(~0x2000); nbuff=13; goto salto1;} 
			if (word&0x1000) {C1RXFUL1=word&(~0x1000); nbuff=12; goto salto1;} 
			if (word&0x0800) {C1RXFUL1=word&(~0x0800); nbuff=11; goto salto1;} 
			if (word&0x0400) {C1RXFUL1=word&(~0x0400); nbuff=10; goto salto1;} 
			if (word&0x0200) {C1RXFUL1=word&(~0x0200); nbuff=9; goto salto1;} 
			if (word&0x0100) {C1RXFUL1=word&(~0x0100); nbuff=8; goto salto1;} 
		
			salto1: 

	
			word_re2=nbuff;
     		if (nbuff!=-1)
			{
				//PARPADEO_valor(1,3);
				pt_func=(PT_HD) id_func_handlers[CAN1][nbuff];
				if (pt_func!=NULL) (*pt_func)((void *)nbuff);
			}
		}

	}

}



int HP_Mesg_Proc_1(void * arg)
{
   // funcion que maneja "1" mensaje de alta prioridad
   // observar que la prioridad depende de la tarea que lo invoca. 
	int nbuf;
	nbuf=(int)arg;	

 	escribe_led_hp(ECAN_DMA_AREA[nbuf].DATA[0]);
	//while(1);
	
//escribir en los leds el más a la izquierda a 1 y el resto dos bits sacarlos del mensaje
	return OK;
}
int LP_Mesg_Proc(void * arg)
{
   // Una función para manejar los mensajes de baja prioridad
   // observar que la prioridad depende de la tarea que lo invoca.
	int nbuf;
	nbuf=(int)arg;	
	//	PARPADEO_valor(0,3);
	switch (ECAN_DMA_AREA[nbuf].SID)
	{
/*		case ID_CAD1:    procesa_can_CAD(ECAN_DMA_AREA[nbuf]);   // lee o escribe, la lectura supone el envio de un mensaje. 
						 break;
		case ID_PWM1:    PWM_procesa_CAN(ECAN_DMA_AREA[nbuf]);   // lee o escribe, la lectura supone el envio de un mensaje. 
						 break;
		case ID_QEI1:    procesa_can_QEI(ECAN_DMA_AREA[nbuf]);   // lee o escribe, la lectura supone el envio de un mensaje. 
						 break;
*/		

/*		case ID_PT_PROC: procesa_pt(nbuf);   // lee o escribe, la lectura supone el envio de un mensaje. 
						 break;
		case ID_LED_LP:	 escribe_led_lp(ECAN_DMA_AREA[nbuf].DATA[0]);
					     break;
*/	}

	return OK;	
}


void procesa_pt(int nbuf)
{
	//determina que tipo de operacion y el tipo de dato.
	switch(ECAN_DMA_AREA[nbuf].DATA[0]&OP_MASK)
	{
		case OP_NORMAL_RD:  //ENVIO DE MENSAJE 
							// puede fallar son no hay buffers libres para la transmisión.
							procesa_pt_RD(nbuf);
							break;
		case OP_NORMAL_WR:  procesa_pt_WR(nbuf);
							// algunas escrituras suponen una parada de la CPU durante unos instantes 
							// buscar "cpu stalls" en 70291D capitulo 5.4.1 PROGRAMMING ALGORITHM FOR			
							// FLASH PROGRAM MEMORY

							break;
	}
}

void procesa_pt_WR(int nbuf)
{
	void * address;
	address=*((void * *)&(ECAN_DMA_AREA[nbuf].DATA[1]));
	switch(ECAN_DMA_AREA[nbuf].DATA[0]&TYPE_MASK)
	{
	
		case TYPE_32BIT:
		case TYPE_FLOAT: *(((unsigned char*)address)+3)=ECAN_DMA_AREA[nbuf].DATA[7];
		case TYPE_ADDRESS:
						 *(((unsigned char*)address)+2)=ECAN_DMA_AREA[nbuf].DATA[6];
		case TYPE_16BIT: *(((unsigned char*)address)+1)=ECAN_DMA_AREA[nbuf].DATA[5];
		case TYPE_BYTE:  *(unsigned char*)address=ECAN_DMA_AREA[nbuf].DATA[4];
	}
}



void procesa_pt_RD(int nbuf)
{
	// siempre lee 32 bits, es el cliente el que limpia el dato
	char buf[8];
	
	
	*((unsigned long int **)(buf+1))=*((void * *)&(ECAN_DMA_AREA[nbuf].DATA[1]));
	*((unsigned long int *)(buf+4))=*(*((unsigned long int  * *)&(ECAN_DMA_AREA[nbuf].DATA[1])));
	buf[0]=ECAN_DMA_AREA[nbuf].DATA[0];
	
	CAN_DSPIC_33F_SetupMessage_firstfree(CAN1,ID_PT_PROC_R,8,0, buf);
	
}



// interrupciones

//interrupcion ecan 

// los nombres de las funciones son predefinidos y de este modo no hay que origramar nada
// en los vectores de interrupciones
// sñolo hay tres vectores asociados al controlador CAN numero 1 en el dspic del proyecto

int numero_interrupciones;

// no se invoca si funciona con DMA
void __attribute__((__interrupt__, auto_psv)) _C1RxRdyInterrupt( void )
//CAN1 receive data ready
{ 
escribe_led_hp(1);while(1); }

  
// no se invoca si funciona con DMA           _C1TxReqInterrupt
//%·$%·$%·$% Esta es la funcion que da el warningn

void __attribute__((__interrupt__, auto_psv)) _C1TxReqInterrupt ( void )
//_AltC1TxReqInterrupt CAN1 transmit data request
{
escribe_led_hp(2); 
while(1); }


int ggt0,ggt1,ggt2,ggt3,ggt4;
int gge0,gge1,gge2,gge3,gge4;
int ggh0,ggh1;
	int gggt,gggt1;

void __attribute__((__interrupt__, auto_psv)) _C1Interrupt (void)
// si se produce algun evento en el controlador CAN salta a esta rutina
// Interrupción por eventos 
{
	
		int res;
	gggt=C1INTF;
			ggt0=IFS0;
			ggt1=IFS1;
			ggt2=IFS2;
			ggt3=IFS3;
			ggt4=IFS4;
		
			gge0=IEC0;
			gge1=IEC1;
			gge2=IEC2;
			gge3=IEC3;
			gge4=IEC4;

	numero_interrupciones++;
	if(gggt&0x04)
	{
		CAN_DSPIC_33F_Overflow(CAN1);
	   _RBOVIF=0;
		gggt1=C1INTF;
		//LED(3);
	}
	else
	if (gggt&0x02)
	{   //LED(2);
		_RBIF=0;
	}
	else
	if (gggt&0x01)
	{   //LED(1);
		_TBIF=0;
	}
	//LED(1);
	IFS2bits.C1IF = 0;		

}

// si se transmite un mensaje salta esta interrupción
void __attribute__((__interrupt__,auto_psv)) _DMA0Interrupt(void)
{
// canal 0 configurado para TX 
IFS0bits.DMA0IF = 0;
//escribe_led_lp(1);
//while(1);
}



int g_nint=0;

void __attribute__((__interrupt__,auto_psv)) _DMA1Interrupt(void)
{
	int nbuff;
	int word;
// canal 1 configurado para RX para el controlador CAN número 1
// Lo único que tiene que hacer es activar la tarea que procesará el mensaje que
// que buffer se ha llenado 
// que filtro ha tenido exito?

	//escribe_led_lp(2);
	//while(1);

    portBASE_TYPE xHigherPriorityTaskWoken_lp = pdFALSE; 
    portBASE_TYPE xHigherPriorityTaskWoken_hp = pdFALSE; 
	portBASE_TYPE res_lp=pdFAIL;
	portBASE_TYPE res_hp=pdFAIL;
	
	// 'Give' the semaphore to unblock the task. */
	// LA RECEPCION HACE REFERENCIA A LOS BUFFERES Y NO A LOS FILTROS 
		C1CTRL1bits.WIN=0x0;

//0xFF00 
// es porque los filtros de 0 al 7 son de transmision
// 8 al 15 son de alta prioridad
// 16 al 32 son de baja prioridad y van a la fifo
	if ((C1RXFUL1&0xFF00)!=0) // high priority		
	
	//ññññ%$$$%%% a partir de aqui aparece el problema del acceso a direccion no valida
	//demasiados gives? quizas? eso va con copias de colas de mensajes...
	{  //LED(3);
		g_nint++;
	g_LUGAR=3;
	  
/*			C1CTRL1bits.WIN=0x0;
			word=C1RXFUL1;
		

			nbuff=-1;
			if (word&0x8000) {C1RXFUL1=word&(~0x8000); nbuff=15; goto salto2;} 
			if 	(word&0x4000) {C1RXFUL1=word&(~0x4000); nbuff=14; goto salto2;} 
			if (word&0x2000) {C1RXFUL1=word&(~0x2000); nbuff=13; goto salto2;} 
			if (word&0x1000) {C1RXFUL1=word&(~0x1000); nbuff=12; goto salto2;} 
			if (word&0x0800) {C1RXFUL1=word&(~0x0800); nbuff=11; goto salto2;} 
			if (word&0x0400) {C1RXFUL1=word&(~0x0400); nbuff=10; goto salto2;} 
			if (word&0x0200) {C1RXFUL1=word&(~0x0200); nbuff=9; goto salto2;} 
			if (word&0x0100) {C1RXFUL1=word&(~0x0100); nbuff=8; goto salto2;} 
		
			salto2: 

			if (ECAN_SemHP==0){LED(2); while(1);}
*/

	res_hp=xSemaphoreGiveFromISR( ECAN_SemHP, &xHigherPriorityTaskWoken_hp );


	  //LED(6);
	}
	if (((C1RXFUL2&0xFFFF)!=0)) // low priority BUZONES Y FIFO.
		res_lp=xSemaphoreGiveFromISR( ECAN_SemLP, &xHigherPriorityTaskWoken_lp );
	
	// Giving the semaphore may have unblocked a task - if it did and the	
	// unblocked task has a priority equal to or above the currently executing
	// task then xHigherPriorityTaskWoken will have been set to pdTRUE and
	// portEND_SWITCHING_ISR() will force a context switch to the newly unblocked
	// higher priority task.
	// NOTE: The syntax for forcing a context switch within an ISR varies between
	// FreeRTOS ports. The portEND_SWITCHING_ISR() macro is provided as part of
	// the PIC32 port layer for this purpose. taskYIELD() must never be called
	// from an ISR! 
	
	// EN LA DEMO PARA dspic EMPLEA taskYIELD() de esta forma

	if ((res_lp==pdPASS)&&(xHigherPriorityTaskWoken_lp))
		//portEND_SWITCHING_ISR();
		taskYIELD();
	if ((res_hp==pdPASS)&&(xHigherPriorityTaskWoken_hp))
		//portEND_SWITCHING_ISR();
		taskYIELD();

	IFS0bits.DMA1IF = 0;
}




void __attribute__((__interrupt__,auto_psv)) _DefaultInterrupt(void)
{



	
	while(0);
	{
			ggt0=IFS0;
			ggt1=IFS1;
			ggt2=IFS2;
			ggt3=IFS3;
			ggt4=IFS4;
			
			gge0=IEC0;
			gge1=IEC1;
			gge2=IEC2;
			gge3=IEC3;
			gge4=IEC4;
			while(1);
			if (INTCON1&0x0008)
			{
				
				//LED(7);//PARPADEO_valor_ret(0,7,4);
					   //PARPADEO_valor_ret(0,6,4);	
				INTCON1=INTCON1&0xFFF7;
			}
	}
;

}
