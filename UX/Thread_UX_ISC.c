#ifndef __dsPIC33FJ64MC804__
    #ifndef __dsPIC33FJ128MC804__
        #error "Include file does not match processor setting"
    #else
        #include <p33FJ128MC804.h>
    #endif
#else
    #include <p33FJ64MC804.h>
#endif


#define _CAN1 //sólo un controlador es necesario para los defines de CAN


/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

#include "can_scocan.h"
#include "CANTypes.h"

#include "CAN_DSPIC_33F_Stack.h"
#include "CAN_DSPIC_33F_Stack_Overflow.h"
#include "CAN_DSPIC_33F_Configuracion.h"
#include "util.h"
#include "handlers_can.h"

#include "message_id.h"
#include <stdio.h>


//DETECCION DE DISTANCIAS 

// when P1TMR reach P1TPER reset itself. (pulses of 3ms as maximum)
#define PWMRESOLUTION 12500LL  /* 20ms*/
#define MAX_WIDTH         2680 /* en microsegundos*/
#define MIN_WIDTH         720 /* en microsegundos  */      
#define MAX_DEGREE        160  /**/
#define MIN_DEGREE        0  /**/
#define CENTER 0            /* offset en centesimas de grado*/

static unsigned int ServoPOS[4]; // raw value
static unsigned int ServoPOS_cdegree[4]; // raw value
static unsigned long int Distance;
static int st=-1; // estado de la cabeza
static int autost=0; // automatic

unsigned int delay_motor;
unsigned int delay_auto;




//int INFRA_Buffer[16];
//int INFRA_Buffer_sin_emision[16];


//unsigned char Serial_MSG_buf[11*2]; // en hex
//int SerialMSG_pos=0; // posicion
//int SerialMSG_rev=0; // receiving


unsigned char  UX_HEAD_CAN_Buffer[8];


void byte2hex(unsigned char d,char * buf);   /*prepara los caracteres del fichero para su envio*/
void UX_HEAD_procesa_CAN(int nbuff);
void BRIDGE_procesa_CAN(int nbuff);
#define UX_ISC_MAIN_TASK	50 /* periodo 10 ms */




void UX_HEAD_Init_CAN()
{
    //CAN_DSPIC_33F_SetupMessage(CAN1,UX_HEAD_BUFFER_CAN,0x00,8,0, (char *)UX_HEAD_CAN_Buffer);
    //reception hardcoded
    return;
    
}

void UX_HEAD_CAN_TX(int nbuff)
{
	 int t;
    char buf[2];
    unsigned long int id;
    int len;
    
    
    id=CAN_DSPIC_33F_Get_Message_ID_in_FIFO(CAN1,nbuff);
	
    
	xSerialPutChar(  0, '>' , UX_ISC_MAIN_TASK);
    xSerialPutChar(  0, 'R' , UX_ISC_MAIN_TASK);
    
	byte2hex((id&0xff00)>>8,buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , UX_ISC_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , UX_ISC_MAIN_TASK);
    byte2hex((id&0xff),buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , UX_ISC_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , UX_ISC_MAIN_TASK);
    
    len=CAN_DSPIC_33F_Get_Message_DLC_in_FIFO(CAN1,nbuff);
    //printf("Long %x \n",len);
    byte2hex(len,buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , UX_ISC_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , UX_ISC_MAIN_TASK);
    
    for (t=0;t<len;t++)
    {
    byte2hex((unsigned char)CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN1,nbuff,t),buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , UX_ISC_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , UX_ISC_MAIN_TASK);  
    }
    xSerialPutChar(  0, '<' , UX_ISC_MAIN_TASK);
    //xSerialPutChar(  0, '\n' , BRIDGE_MAIN_TASK);
    
}


void UX_HEAD_procesa_CAN(int nbuff)
{
    int t;
    char buf[2];
    unsigned long int id;
    int len;
	unsigned int pos,posa,pos_ant,dist;
    char num_servo;
    
    id=CAN_DSPIC_33F_Get_Message_ID_in_FIFO(CAN1,nbuff);
	len=CAN_DSPIC_33F_Get_Message_DLC_in_FIFO(CAN1,nbuff);    
    
    
    num_servo=(unsigned int)(unsigned char)CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN1,nbuff,0);
    pos=((unsigned int)CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN1,nbuff,1))&0x00FF;  
    
    pos=pos&0xFF;
    posa=((unsigned int)CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN1,nbuff,2))&0x00FF;
    posa=posa&0xff;
    pos=pos*(unsigned int)0x100+posa;
            
    switch (num_servo)
    {
        case 3: autost=0;
                //printf("NO AUTO\n");
                //printf("Disparando en %x\n",pos);
                
                putPosition(num_servo,pos);
                
                st=1; // nuevo disparo;
                break;
        case 5: //printf("Configuring AUTO\n");
                st=0;
                autost=((unsigned int)((unsigned int)CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN1,nbuff,1)))&0xFF;
                
                break;
        case 6: 
                delay_motor=pos;  
                printf("Delay_motor %x \n",delay_motor);              
                break;
     
        case 7: delay_auto=pos;
                printf("Delay_auto %x\n",delay_auto);
                break; 
        default:
            printf("\nERROR: Numero de servo %x no programado\n",num_servo);
            
    }

    CAN_DSPIC_33F_SetupMessage(CAN1,UX_HEAD_BUFFER_CAN,CANID_UX_HEAD,8,0, (char *)UX_HEAD_CAN_Buffer);
    CAN_DSPIC_33F_SendMessage(CAN1,UX_HEAD_BUFFER_CAN);

    
}


void UX_HEAD_procesa_CAN_BUFF(char * nbuff)
{
    int t;
    char buf[2];
    unsigned long int id;
    int len;
	unsigned int pos,posa,pos_ant,dist;
    char num_servo;

    num_servo=(unsigned int)nbuff[0];
    pos=((unsigned int)nbuff[1])&0x00FF;  
    posa=((unsigned int)nbuff[2])&0x00FF; 
    posa=posa&0xff;
    pos=pos*(unsigned int)0x100+posa;
    
    switch (num_servo)
    {
        case 3: autost=0;
                //printf("Disparando en %x\n",pos);
                putPosition(num_servo,pos);
                
                st=1; // nuevo disparo;
                break;
        case 5: printf("Configuring AUTO\n");
                st=0;
                autost=((unsigned int)nbuff[1])&0xFF;                
                break;
        case 6: 
                delay_motor=pos;  
                printf("Delay_motor %x \n",delay_motor);              
                break;
        case 7: delay_auto=pos;
                printf("Delay_auto %x\n",delay_auto);
                break;        
        default:
            printf("\nERROR: Numero de servo %x no programado\n",num_servo);
            
    }
    

}



unsigned long int getDistance(void)
{
    return Distance;
}

int getPosition(unsigned int num_servo) //centesimas de grado 
{
    if (num_servo>3)
        return -1; // identificador de servo erroneo
    return ServoPOS_cdegree[num_servo];
}


int putPosition(unsigned int num_servo,unsigned int pos /* centesimas de grado */ )                          
{
    //1,5ms 0 grados
    unsigned long int value,ancho;
    unsigned long int raw;
    
    
    value=(((unsigned long int)pos+CENTER)*(MAX_WIDTH-MIN_WIDTH))/(MAX_DEGREE-MIN_DEGREE); // ancho en us   
    ancho=MIN_WIDTH+value; // en us
    raw=((ancho*PWMRESOLUTION)/20000LL)*2; // por  2 porque el contador sube y baja
    
    if (num_servo>3)
        return -1; // identificador de servo erroneo
    if (raw>PWMRESOLUTION) 
        return -2; // math error
    
    ServoPOS_cdegree[num_servo]=pos; // raw value
    ServoPOS[num_servo]=raw;
    return 0;
    
}


void Configure_UXHEAD(void)
{
    // Contador 3 
    // configuración de la entrada del IC1 en el pin PWM2L1 que es RP23+
      // Puertos como salida
    TRISCbits.TRISC6=0; //  PWM2H1  // Puertos como salida
    TRISCbits.TRISC7=1; //  PWM2L1  // como entrada   
    RPINR7bits.IC1R=23;
    
    // Timer3
    T3CONbits.TCS=0;
    T3CONbits.TGATE=0;
    T3CONbits.TCKPS=2; // 40Mhz /64
    T3CONbits.TON=1; // 
    
    // capture 
     IC1CONbits.ICTMR=0;
     IC1CONbits.ICI=1; // cuando baje
     IC1CONbits.ICM=0x1; // tanto cuando sube como cuando baja
     
}
void Init_CAD_DSPIC33F128MC804 (void)
{
     /* adquisición de 3 canales simultaneos */
	 /* Configuracion:*/
	// Select port pins as analog inputs (AD1PCFGH<15:0> or AD1PCFGL<15:0>).
	// todos los pins se pueden emplear como entrada anlogica.


	// donde esta AN0-AN3? 
	// RA0,RA1,RB0,RB1	
    // fisicamente en los pines 19,20,21,22
	
	TRISA=TRISA|0x0002; // pin configured as input 1
	
	AD1PCFGL=0xFFFD;  // PIN AN1 como analogico
    //AD1PCFGH=0xFFFF;

	// Select voltage reference source to match expected range on analog inputs (AD1CON2<15:13>).

    AD1CON1bits.AD12B = 1; // 10-bit ADC operation
	AD1CON1bits.FORM = 0; // 00 = Integer (DOUT= 0000 00dd dddd dddd)
	AD1CON1bits.SSRC = 7; // 111 = Internal counter ends sampling and starts conversion (auto-convert)
	AD1CON1bits.ASAM = 0; // disparo por programa
	// disparo 
    // AD1CON1bits.DONE=0;
	// AD1CON1bits.SAMP=1;  // Se dispara   

    
    
	AD1CON2bits.VCFG=0; // tension  dereferncia 
	AD1CON2bits.CSCNA=0; // no se escanea
  
	AD1CON2bits.ALTS=0;
	// Select the analog conversion clock to match the desired data rate with the processor clock (AD1CON3<7:0>).

	AD1CON3bits.ADRC = 0; // ADC Clock is derived from Systems Clock
	AD1CON3bits.SAMC = 20; // Auto Sample Time = 0 * TAD
	AD1CON3bits.ADCS = 3; // ADC Conversion Clock TAD = TCY * (ADCS + 1) = (1/40M) * 3 =
// 75 ns (13.3 MHz)
// ADC Conversion Time for 10-bit Tconv = 12 * TAD = 900 ns (1.1 MHz)
//AD1CON1bits.ADDMABM = 1; // DMA buffers are built in conversion order mode

	

	// configuracion de la entrada y la tension de referencia 
	//AD1CHS0/AD1CHS123: A/D Input Select Register
	
	// El esquema no es muy preciso.
	//, la entrada positivca es la tension a convertir
	//  La entrada negativa es la tensión de referencia.
	
	// S/H0  AN3, Vrefl
	// S/H1  AN0, Vrefl
	// S/H2  AN1, Vrefl
	// S/H3  AN2, Vrefl

	AD1CHS0bits.CH0SA = 1; // MUXA +ve input selection (AIN0) for CH0
	AD1CHS0bits.CH0NA = 0; // MUXA -ve input selection (VREF-) for CH0


	// La direccion de  los bufferes en el dspic33F32MC204
	// es fija ADC1BUF0, ADC1BUF3,... ADC1BUFF
	
	// orden de transferencia
	AD1CON1bits.ADDMABM=1; /* se transfieren en orden de conversion */
    



	AD1CON1bits.ADON = 1; // el desplazamiento depende de la línea ANx no del pin


}


void Configure_PWM_UXHEAD(void)
{
    // PWM I/O  independent OutputMode
    //PWM1CON1bits.PMOD1=1;
    //PWM1CON1bits.PMOD2=1;
    PWM1CON1bits.PMOD3=1;
    
    // habilitación   PEN Enable=1
    PWM1CON1bits.PEN1H=0;
    PWM1CON1bits.PEN2H=0;
    PWM1CON1bits.PEN3H=1;
    PWM1CON1bits.PEN1L=0;
    PWM1CON1bits.PEN2L=0;
    PWM1CON1bits.PEN3L=0;
    //sincronización y eventos 
    PWM1CON2=0; // value after reset;
    // Deadtime
    P1DTCON1=0; // value after reset;
    P1DTCON2=0; // value after reset;
    // Fault lines
    P1FLTACON=0; // value after reset;
    // Override PWM lines
    P1OVDCON=0xFF00; // value after reset;
    
    // duty cycle 
    P1DC1=0; // value after reset;
    P1DC2=0; // value after reset;
    P1DC3=0; // value after reset;
    
    // Power On control
    // FPOR register controlado por bits de configuracion
    
    // Time Base
    //Period //resolution
    P1TPER=12500; // when P1TMR reach P1TPER reset itself. (pulses of 3ms as maximum)
    // valor del contador ¿Cuando se recarga o actual(R/W)?
    P1TMR=0x0000; // value after reset
    // PWM MAIN Time Base Configuration 
    // OSC_DSPIC33F_70186c.pdf TCY es en principio crystal div 2  es 40Mhz
    P1TCONbits.PTCKPS=0x3; // 1:4 --> 0,1 us
    P1TCONbits.PTOPS=0x7; // 1:8 --> postscale;
    P1TCONbits.PTSIDL=0; //In idle PWM of Value after reset;
    P1TCONbits.PTMOD=0x0; // freerunning mode                          // 0x01 single event
    P1TCONbits.PTEN=0; // deshabilitado hace un disparo.  
    TRISBbits.TRISB10=0; // PWM1H3
    
    
    
    AD1PCFGL=0b0000000000; // 
        
}

void Enable_PWM_UXHEAD(void)
{
    P1TCONbits.PTEN=1; // deshabilitado hace un disparo.
    //P2TCONbits.PTEN=1; // deshabilitado hace un disparo.
    
}

void vHeadTask_AUTO( void *pvParameters )
{

    TickType_t xLastExecutionTime;

    unsigned int ct1,ct2,ct3,ct4;

    int nm;
    int c;
    int pos;
    int step=20;
    delay_auto=100;
        
    pos=0;
    
    while(1)
    {
        
        if (autost)
        {
            
            switch (st)
            {
                case 0:    putPosition(3,pos);
                           //printf("AUTO: %d\n",getPosition(3));
                           pos=pos+step;
                           if (pos>=MAX_DEGREE) { step=-step; pos=pos+2*step;}
                           if (pos<0) { step=-step; pos=pos+2*step;}
                           st=1;
                           break;
                default:   ;
            };
            vTaskDelayUntil( &xLastExecutionTime, delay_auto );
        }
        else
            vTaskDelayUntil( &xLastExecutionTime, 1000 );
    c++;
	}	

    
}
void vHeadTask( void *pvParameters )
{
/* Used to wake the task at the correct frequency. */
TickType_t xLastExecutionTime;




/* The message that is sent on the queue to the LCD task.  The first
parameter is the minimum time (in ticks) that the message should be
left on the LCD without being overwritten.  The second parameter is a pointer
to the message to display itself. */
/* Set to pdTRUE should an error be detected in any of the standard demo tasks. */

unsigned int ct1,ct2,ct3,ct4;


int nm;
int c;

unsigned int dif;
 int ct,aux;
 
	/* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
	works correctly. */

    // Configurar el PWM y las líneas
    //TRISB=0x1FFF;
    Configure_UXHEAD();
    Configure_PWM_UXHEAD();
    
    printf("Setting CAD for INFRA\r\n");
    Init_CAD_DSPIC33F128MC804 ();
    
    	
    UX_HEAD_Init_CAN();
    
    delay_motor=10;

    xLastExecutionTime = xTaskGetTickCount();
   
    c=0;

    
    putPosition(3,MAX_DEGREE/2);
    Enable_PWM_UXHEAD();
    for (ct=0;ct<10;ct++) aux=IC1BUF;

    st=0;
    c=0;            
    nm=0;
    for( ;; )
	{
        
        // siempre esta operativo la señal pwm otra cosa es que se mueva el servo
     
        if (st>0) P1DC3=ServoPOS[3]; // raw value

        
        switch (st)
        {
            case 0:   // idle
                        c=0;
                        break;
            case 1:   // se esta generando la señal del servo
                        if (c>delay_motor) {
                            for (ct=0;ct<8;ct++) aux=IC1BUF;
                            c=0;
                            st=2;
                            // se empieza el disparo 
                            PORTCbits.RC6=1;
                            // DISPAR0 CAD for INFRA
                             AD1CON1bits.DONE=0;
                             AD1CON1bits.SAMP=1;  // Se dispara   c=0;
                            
                        }// retardo máximo hasta que se posiciona y se estabiliza 
                        break;
                        
            case 2:     c=0;
                        PORTCbits.RC6=0;
                        for (ct=0;ct<3;ct++) aux=IC1BUF;
                        TMR3=0;                   
                        nm++;
                        st=3;
                        break;
            case 3:     if (c>3)
                        {
                        ct1=IC1BUF;
                        ct2=IC1BUF;
                        ct3=IC1BUF;
                        ct4=IC1BUF;
                        if (ct1>ct2) 
                            dif=ct1-ct2;
                        else
                            dif=ct2-ct1;
                        
                        //printf("%x %x %x %x\n",ct1,ct2,ct3,ct4);
                        Distance=((unsigned long int)dif*(unsigned long int)130)/(unsigned long int)0x1dd;
                        st=4;
                        }
                        break;
                        
            case 4:     c=0;
                
                        // si hay que transmitir se transmite
                        UX_HEAD_CAN_Buffer[0]=3;
                        UX_HEAD_CAN_Buffer[1]=getPosition(3)>>8;
                        UX_HEAD_CAN_Buffer[2]=getPosition(3)&0xff;
                        UX_HEAD_CAN_Buffer[3]=Distance>>8;
                        UX_HEAD_CAN_Buffer[4]=Distance&0xFF;
                        UX_HEAD_CAN_Buffer[5]=ADC1BUF0>>8;
                        UX_HEAD_CAN_Buffer[6]=ADC1BUF0&0xFF;
                        
                        CAN_DSPIC_33F_SetupMessage(CAN1,UX_HEAD_BUFFER_CAN,CANID_UX_HEAD,7,0, (char *)UX_HEAD_CAN_Buffer);
                        //printf("enviando por serie");
                        UX_HEAD_CAN_TX(UX_HEAD_BUFFER_CAN);
                        //printf("Diferencia %d %x %x %d \r\n",nm,dif,TMR3,(unsigned int)Distance);
                        //printf("DISTANCIA: %d %d \r\n",getPosition(3),(unsigned int)Distance);
                        //printf("trama can aqui por serieDISTANCIA: \r\n");
                        
                       
                        CAN_DSPIC_33F_SendMessage(CAN1,UX_HEAD_BUFFER_CAN);
                        
                        st=0;
                        
                        break;
        };
        
        /* Wait until it is time for the next cycle. */
		vTaskDelayUntil( &xLastExecutionTime, 10 );
        c++;
		
	}
}
void vHeadINFRATask( void *pvParameters )
{
/* Used to wake the task at the correct frequency. */
TickType_t xLastExecutionTime;
int st_interno;



/* The message that is sent on the queue to the LCD task.  The first
parameter is the minimum time (in ticks) that the message should be
left on the LCD without being overwritten.  The second parameter is a pointer
to the message to display itself. */
/* Set to pdTRUE should an error be detected in any of the standard demo tasks. */

unsigned int ct1,ct2,ct3,ct4;


int nm;
int c;

unsigned int dif;
 int ct,aux;
 
  printf("tHREAD cad \r\n");
    Init_CAD_DSPIC33F128MC804 ();
    xLastExecutionTime = xTaskGetTickCount();
   
    c=0;
    st_interno=0;
  
    
    for( ;; )
	{
              
        switch (st_interno)
        {
            case 0:     // idle
                        AD1CON1bits.DONE=0;
                        AD1CON1bits.SAMP=1;  // Se dispara   c=0;
                        st_interno=1;
                        break;
            case 1:   // se esta generando la señal del servo
                        // se crecoge la muestra
                        printf("Diferencia %X \r\n",ADC1BUF0);
            
            default:        
                        st_interno=0;
                    break;
        };
        
        /* Wait until it is time for the next cycle. */
		vTaskDelayUntil( &xLastExecutionTime, 1000 );
        c++;
		
	}
}
