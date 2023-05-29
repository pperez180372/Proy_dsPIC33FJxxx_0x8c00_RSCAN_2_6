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
#include "Thread_INFRA.h"
#include "infra_io.h"
//#include "infra_int.h"
#include <math.h>

word INFRA_datos[4][16];
word INFRA_media[4][16];

static byte INFRA_Contador;
static byte INFRA_Contador_buf;
static byte INFRA_Funcion;                              /* 1,2 se capturan secuencialmente 
                                                         todos los canales
                                                         0 desconectado */
/*extern int contador_int;
extern int datos_int[1024][5];*/
void INFRA_Seleccion_canal(int cont,int hab);


void INFRA_Cambio(void)
{
   INFRA_Contador++;
   if (INFRA_Contador==0x10) 
       INFRA_Contador=0;
   INFRA_Seleccion_canal(INFRA_Contador,1);
}
   
void INFRA_Disparo_captura0(void)
{
	AD1CON1bits.SAMP=1;
}                           

void INFRA_Seleccion_canal(int cont,int hab)
{
	/* pone el canal y habilita la transmision */
   int puertob;
   puertob=(PORTB&0xFFF0)|(cont&0xF);
	PORTB=puertob;
	//PORTB=0;
    
	PORTCbits.RC0=hab; 
	//PORTCbits.RC0=1; 
}

void INFRA_Activacion(byte estado)
{
    if (estado!=INFRA_OFF)
    {
      INFRA_Contador=0;
      PORTCbits.RC0=1;  //	P44=1; /* placa activada */
      IEC0bits.AD1IE=1; // EAD=ENABLE; interrupcion habilitada
    }
    else
    {
      PORTCbits.RC0=0;  //	P44=0; /* placa desactivada */
      IEC0bits.AD1IE=0; // EAD=DISABLE interrupcion  deshabilitada
    
    }
}


void __attribute__((__interrupt__,auto_psv)) _ADC1Interrupt(void)
{
   byte puerto;                             word t;   int ty;
	t=ADC1BUF0;
   //LED(INFRA_Contador);
    switch (INFRA_Funcion)
	{
		case INFRA_SENYAL:   		    //printf("0:Cont: %x ,Dat: %x \n",(unsigned int)INFRA_Contador,t);		    INFRA_datos[INFRA_Contador_buf][INFRA_Contador]=t;    	   	    INFRA_Contador++;        	if (INFRA_Contador>=0x10)
	   		{ 
				INFRA_Contador=0;
				INFRA_Contador_buf++;
				if (INFRA_Contador_buf>0x03) INFRA_Contador_buf=0;
	   		}       		INFRA_Funcion=INFRA_PROMEDIANDO;	   		INFRA_Seleccion_canal(INFRA_Contador,0); // P4=(INFRA_Contador);    /* selecciona canal y desactiva la emisión */   			break;
		case INFRA_PROMEDIANDO:   		   	INFRA_media[INFRA_Contador_buf][INFRA_Contador]=t;    		INFRA_Funcion=INFRA_SENYAL;       		INFRA_Seleccion_canal(INFRA_Contador,1); // P4=(INFRA_Contador);    /* selecciona canal   P4=(INFRA_Contador)|16;    /* selecciona canal y activa la emisión */
			break;
		case INFRA_OFF:	
			break;
   }
 	IFS0bits.AD1IF = 0;
}

int INFRA_Set_mode(int estado){

	int aux;
	aux=INFRA_Funcion;
	INFRA_Funcion=estado;
	return aux;
						
}

inline int INFRA_Get_Senyal(byte b,byte canal){return INFRA_datos[b][canal]; }
inline int INFRA_Get_Enviroment(byte b,byte canal){return INFRA_media[b][canal]; }

int INFRA_Get_buffer(void ){ return INFRA_Contador_buf;}



word INFRA_Media(byte canal)
{
   return (INFRA_datos[canal]);/*-INFRA_media[canal]);*/
}

word INFRA_Offset(byte canal)
{
   word datos;
   datos=INFRA_media[canal-16];              
   return datos;
}

