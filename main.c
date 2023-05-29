/* cambios 250kbits*/
/* Standard includes. */
/* soporte para bluetooth, aunque puede emplear dos puertos serie emplea el mismo y conmuta  */
#include <stdio.h>

#ifndef __dsPIC33FJ64MC804__
    #ifndef __dsPIC33FJ128MC804__
        #error "Include file does not match processor setting"
    #else
        #include <p33FJ128MC804.h>
    #endif
#else
    #include <p33FJ64MC804.h>
#endif

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"


// customize
#include "BRIDGE/INC/Thread_BRIDGE.h"
#include "Thread_UX_ISC.h"


_FGS(GWRP_OFF & GCP_OFF);
// _FOSCSEL tipo de oscilador //_FOSCSEL(FNOSC_PRI);
// IESO_ON arranque con dos osciladores arranque con el interno y despues conmutacion
// y después hacer una conmutacion a clock+pllmaxima frecuencia 80Mhz
_FOSCSEL(FNOSC_FRC & IESO_OFF);
//_FOSCSEL(FNOSC_PRI & IESO_OFF);
// _FOSC(x) comportamiento del oscilador
_FOSC(POSCMD_HS & FCKSM_CSECME &IOL1WAY_OFF&OSCIOFNC_OFF);
//_FWDT comportamiento watchdog
_FWDT(FWDTEN_OFF);
// comportamiento del icd
_FICD(ICS_PGD3 &JTAGEN_OFF );





/* Demo task priorities. */
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainCOM_TEST_PRIORITY				( 2 )

/* The check task may require a bit more stack as it calls sprintf(). */
#define mainCHECK_TAKS_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )

/* The execution period of the check task. */
#define mainCHECK_TASK_PERIOD				( ( TickType_t ) 3000 / portTICK_PERIOD_MS )

/* The number of flash co-routines to create. */
#define mainNUM_FLASH_COROUTINES			( 5 )

/* Baud rate used by the comtest tasks. */
#define mainCOM_TEST_BAUD_RATE				( 19200 )

/* The LED used by the comtest tasks.  mainCOM_TEST_LED + 1 is also used.
See the comtest.c file for more information. */
#define mainCOM_TEST_LED					( 6 )

/* The frequency at which the "fast interrupt test" interrupt will occur. */
#define mainTEST_INTERRUPT_FREQUENCY		( 20000 )

/* The number of processor clocks we expect to occur between each "fast
interrupt test" interrupt. */
#define mainEXPECTED_CLOCKS_BETWEEN_INTERRUPTS ( configCPU_CLOCK_HZ / mainTEST_INTERRUPT_FREQUENCY )

/* The number of nano seconds between each processor clock. */
#define mainNS_PER_CLOCK ( ( unsigned short ) ( ( 1.0 / ( double ) configCPU_CLOCK_HZ ) * 1000000000.0 ) )

/* Dimension the buffer used to hold the value of the maximum jitter time when
it is converted to a string. */
#define mainMAX_STRING_LENGTH				( 20 )

/*-----------------------------------------------------------*/

/*
 * The check task as described at the top of this file.
 */
static void vCheckTask( void *pvParameters );
static void vCheckTask_1( void *pvParameters );
static void vCheckTask_2( void *pvParameters );

 /* Setup the processor ready for the demo.
 */
static void prvSetupHardware_FRC80MHz( void );

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

/*
 * Create the demo tasks then start the scheduler.
 */
/* Demo app include files. */
#include "serial.h"
 xComPortHandle fd;
 xComPortHandle fd1_bluetooth;
 

void Thread_ecan_Init(void);
void vHeadTask_AUTO( void *pvParameters );

void vHeadINFRATask( void *pvParameters );
 
int main( void )
{
     // Como es para bootloader y hay que emplear la AIVT configurar para que sea asÃ­ 
            asm volatile ("disi #0x3FFF");
	/* Configure any hardware required for this demo. */
        INTCON1=0;
        IFS0=0;
        IFS1=0;
        IFS2=0;
        IFS3=0;
        IFS4=0;
        IEC0=0;
        IEC1=0;
        IEC2=0;
        IEC3=0;
        IEC4=0;
        
       INTCON2bits.ALTIVT=1;
    
	/* Configure any hardware required for this demo. */

    
        fd=xSerialPortInitMinimal( 115200, 100 );
        USART2forBuetooth_init( 115200, 100 );

        prvSetupHardware_FRC80MHz();
        /*TRISCbits.TRISC6=0;
       while(1){
           
        PORTCbits.RC6=1;
        PORTCbits.RC6=0;
       }*/
//#define NAMEPRJ 231298309128dfsafkasdflka
    // errata de MPLABX pero funciona
        #define DDD(ed)      #ed
        #define NUMw(n)      DDD(n)
        
        printf(NUMw(NAMEPRJ)"\n");
        printf(__DATE__"*"__TIME__"\n");
        
        Thread_ecan_Init();
        printf("CAN on\n");
        printf("Second USART for Bluetooth on\n");
        
        //xTaskCreate( vHeadINFRATask, "INFRA", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
        //xTaskCreate( vHeadTask, "UXHEAD", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
        //xTaskCreate( vHeadTask_AUTO, "UXHEADAUTO", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
        xTaskCreate( BRIDGE_vMAIN_Task_TX, "BRIDGE_TX", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
        xTaskCreate( vCheckTask_1 , "status", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
       
	    /* Finally start the scheduler. */
     	vTaskStartScheduler();

 
	/* Will only reach here if there is insufficient heap available to start
	the scheduler. */
	return 0;
}
/*-----------------------------------------------------------*/


static void prvSetupHardware_FRC80MHz( void )
{
	/* El simulador si tiene en cuenta los bits que se programan en el
       PLL aunque no está implementado el PLL
	*/

	volatile unsigned int res;

    
    // Calibrar el oscilador interno 
    // Debería generar una señal de 1Mhz ...1 pulso arriba y 3 abajo
    //(4 ciclos , 2 instruccione normales y una de salto 2 ciclos
    OSCTUN=16; // saltos de aprox32KHz 
    
    //TRISAbits.TRISA7=0;  //bit 0;
    /*while(1){
        
            PORTAbits.RA7=1;
            PORTAbits.RA7=0;     
            
        }
      */  
    
    
//	resistencia de 1 megaomio en paralelo
//	y el pin de salida no puede ser digital.
//	cambio de oscilador en ....

/* 
//	 80 MHz 
// fin= 20Mhz 
//n1=/5 --> 4Mhz 
// m=40 --> 160Mhz 
// n2=2 --> 80Mhz 

	res=OSCCON;
	OSCCON=res;
	CLKDIVbits.PLLPRE=3; //--> +2 --> 5 -> 0 es 2
	PLLFBD=38; // --> +2 --> 40 -> 0 es 2
	CLKDIVbits.PLLPOST=0; // --> +2 --> 2 -> 0 es 2
  */
 

//	 80 MHz 
// Fin=8MHz FRC regulado a 8MHz TUN=16
// FRCDIV/2 
//n1=/5 --> 4Mhz 
// m=40 --> 160Mhz 
// n2=2 --> 80Mhz 

    
    CLKDIVbits.FRCDIV=0; // dividido por 1
    /*TRISAbits.TRISA7=0;  //bit 0;
    while(1){
            PORTAbits.RA7=1;
            PORTAbits.RA7=0;     
            
        }
   */
	res=OSCCON;
	OSCCON=res;
	CLKDIVbits.PLLPRE=0; //--> +2 --> 5 -> 0 es 2
	PLLFBD=38; // --> +2 --> 40 -> 0 es 2
	CLKDIVbits.PLLPOST=0; // --> +2 --> 2 -> 0 es 2

  
 
  /*
    // XT with pll
    
	__builtin_write_OSCCONH(0x03);
	__builtin_write_OSCCONL(0x01);

	res=OSCCON;

	while(OSCCONbits.COSC!=0b011);//PARPADEO_valor(0,1);
	while(OSCCONbits.LOCK!=1);//PARPADEO_valor(0,2);
	res=OSCCON;
*/
    // FRC with PLL
    
	__builtin_write_OSCCONH(0x01);
	__builtin_write_OSCCONL(0x01);

	res=OSCCON;

	while(OSCCONbits.COSC!=0b001);//PARPADEO_valor(0,1);
	while(OSCCONbits.LOCK!=1);//PARPADEO_valor(0,2);
	res=OSCCON;
    
    // señal periodica de 100ns 
      /*while(1){
            PORTAbits.RA7=1;
            //PORTAbits.RA8=OSCCONbits.CF;
            PORTAbits.RA7=0;     
            
        }*/
    //TCY=25ns     // cada instruccion son dos ciclos de OSC ¿RISC? o como redefinir los ciclos 
    //TOSC=12,5ns // 80MHz
    
    
    
}



/*-----------------------------------------------------------*/

static void vCheckTask( void *pvParameters )
{
/* Used to wake the task at the correct frequency. */
TickType_t xLastExecutionTime;

/* The maximum jitter time measured by the fast interrupt test. */
extern unsigned short usMaxJitter ;

/* Buffer into which the maximum jitter time is written as a string. */
static char cStringBuffer[ mainMAX_STRING_LENGTH ];

/* The message that is sent on the queue to the LCD task.  The first
parameter is the minimum time (in ticks) that the message should be
left on the LCD without being overwritten.  The second parameter is a pointer
to the message to display itself. */


/* Set to pdTRUE should an error be detected in any of the standard demo tasks. */
unsigned short usErrorDetected = pdFALSE;

	/* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
	works correctly. */

        char car;
        int res;
        int fl;

	xLastExecutionTime = xTaskGetTickCount();
        TRISB=0x1FFF;
        fl=1;
        int ct=0;
	for( ;; )
	{
                ct++;
                car='*';
                res=xSerialGetChar( fd, &car, mainCHECK_TASK_PERIOD/30); // 100ms
                if (res>0) {
                                PORTBbits.RB13=0;
                                ct=1;
                                //printf("el caracter que he recibido es %x \n",car);
                                xSerialPutChar(  fd, car   , mainCHECK_TASK_PERIOD );
                              }
                   if ((ct%2)==0) PORTBbits.RB13=1;
		/* Wait until it is time for the next cycle. */
		
                

	}
}



static void vCheckTask_1( void *pvParameters )
{
/* Used to wake the task at the correct frequency. */
TickType_t xLastExecutionTime;

/* The maximum jitter time measured by the fast interrupt test. */
extern unsigned short usMaxJitter ;

/* Buffer into which the maximum jitter time is written as a string. */
static char cStringBuffer[ mainMAX_STRING_LENGTH ];

/* The message that is sent on the queue to the LCD task.  The first
parameter is the minimum time (in ticks) that the message should be
left on the LCD without being overwritten.  The second parameter is a pointer
to the message to display itself. */


/* Set to pdTRUE should an error be detected in any of the standard demo tasks. */
unsigned short usErrorDetected = pdFALSE;

	/* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
	works correctly. */
 int t;unsigned long int t1;

	xLastExecutionTime = xTaskGetTickCount();
    LEDA(0X00);
    t1=0;
	for( ;; )
	{
        t1++;
        t++;
        if ((t1%1000)==0) LEDA(0);
        if (t==2) t=0;
        switch (t)
        {
            case 0: LED3(1); break;
            case 1: LED3(0); break;
            case 2: LED2(1); break;
            case 3: LED2(0); break;
            
        };
   
        
		/* Wait until it is time for the next cycle. */
		vTaskDelayUntil( &xLastExecutionTime, 30);
          

	}
}



static void vCheckTask_2( void *pvParameters )
{
/* Used to wake the task at the correct frequency. */
TickType_t xLastExecutionTime;

/* The maximum jitter time measured by the fast interrupt test. */
extern unsigned short usMaxJitter ;

/* Buffer into which the maximum jitter time is written as a string. */
static char cStringBuffer[ mainMAX_STRING_LENGTH ];

/* The message that is sent on the queue to the LCD task.  The first
parameter is the minimum time (in ticks) that the message should be
left on the LCD without being overwritten.  The second parameter is a pointer
to the message to display itself. */


/* Set to pdTRUE should an error be detected in any of the standard demo tasks. */
unsigned short usErrorDetected = pdFALSE;

	/* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
	works correctly. */
	xLastExecutionTime = xTaskGetTickCount();
        TRISB=0x1FFF;
	for( ;; )
	{
		/* Wait until it is time for the next cycle. */
		vTaskDelayUntil( &xLastExecutionTime, mainCHECK_TASK_PERIOD/10 );
        PORTBbits.RB14=1;
        vTaskDelayUntil( &xLastExecutionTime, mainCHECK_TASK_PERIOD/10 );
        PORTBbits.RB14=0;

	}
}



/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* Schedule the co-routines from within the idle task hook. */
	vCoRoutineSchedule();
}
/*-----------------------------------------------------------*/

