/*
    FreeRTOS V8.2.1 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


/* BASIC INTERRUPT DRIVEN SERIAL PORT DRIVER. 

NOTE:  This driver is primarily to test the scheduler functionality.  It does
not effectively use the buffers or DMA and is therefore not intended to be
an example of an efficient driver. */

/* Standard include file. */
#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

#include "stdio.h"

/* Demo app include files. */
#include "serial.h"

/* Hardware setup. */
#define serOUTPUT						0
#define serINPUT						1
#define serLOW_SPEED					0
#define serONE_STOP_BIT					0
#define serEIGHT_DATA_BITS_NO_PARITY	0
#define serNORMAL_IDLE_STATE			0
#define serAUTO_BAUD_OFF				0
#define serLOOPBACK_OFF					0
#define serWAKE_UP_DISABLE				0
#define serNO_HARDWARE_FLOW_CONTROL		0
#define serSTANDARD_IO					0
#define serNO_IRDA						0
#define serCONTINUE_IN_IDLE_MODE		0
#define serUART_ENABLED					1
#define serINTERRUPT_ON_SINGLE_CHAR		0
#define serTX_ENABLE					1
#define serINTERRUPT_ENABLE				1
#define serINTERRUPT_DISABLE			0
#define serCLEAR_FLAG					0
#define serSET_FLAG						1


/* The queues used to communicate between tasks and ISR's. */
static QueueHandle_t xRxedChars=NULL; 
static QueueHandle_t xCharsForTx=NULL; 
static QueueHandle_t xCharsForTx_BT=NULL; 
static portBASE_TYPE xTxHasEnded;
static portBASE_TYPE xTxHasEnded_BT;
/*-----------------------------------------------------------*/
void USART2forBuetooth_init(unsigned long ulWantedBaud, unsigned portBASE_TYPE uxQueueLength )

{
    
    char cChar;
    /* colas compartidas con la UART1*/
    if (xRxedChars == NULL) xRxedChars=xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xCharsForTx_BT = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
    
        
    /* la línea PWM1H1 conectado a RX bluetooth por tanto es TX */
    /* la línea PWM1H2 conectado a TX bluetootx por lo tanto es RX */
    /* Setup PINs dspic33f Pascual Pérez */
    
    //PWM1H1 es RP14
    //PWM1H2 es RP12
    
	//U2RX input a RP19
	RPINR19bits.U2RXR=12;
    TRISBbits.TRISB12=1;
    TRISBbits.TRISB14=0; 
    
	//U2TX output a RP14
	RPOR7bits.RP14R=5;
    
    U2BRG=0x10a;
	
/* Setup the UART. */
	U2MODEbits.BRGH		= serLOW_SPEED;
	U2MODEbits.STSEL	= serONE_STOP_BIT;
	U2MODEbits.PDSEL	= serEIGHT_DATA_BITS_NO_PARITY;
	U2MODEbits.ABAUD	= serAUTO_BAUD_OFF;
	U2MODEbits.LPBACK	= serLOOPBACK_OFF;
	U2MODEbits.WAKE		= serWAKE_UP_DISABLE;
	U2MODEbits.UEN		= serNO_HARDWARE_FLOW_CONTROL;
	U2MODEbits.IREN		= serNO_IRDA;
	U2MODEbits.USIDL	= serCONTINUE_IN_IDLE_MODE;
	U2MODEbits.UARTEN	= serUART_ENABLED;

	U2BRG = (unsigned short)(( (float)configCPU_CLOCK_HZ / ( (float)16 * (float)ulWantedBaud ) ) - (float)0.5);

	U2STAbits.URXISEL	= serINTERRUPT_ON_SINGLE_CHAR;
	U2STAbits.UTXEN		= serTX_ENABLE;
	U2STAbits.UTXINV	= serNORMAL_IDLE_STATE;
	U2STAbits.UTXISEL0	= serINTERRUPT_ON_SINGLE_CHAR;
	U2STAbits.UTXISEL1	= serINTERRUPT_ON_SINGLE_CHAR;

	/* It is assumed that this function is called prior to the scheduler being
	started.  Therefore interrupts must not be allowed to occur yet as they
	may attempt to perform a context switch. */
	portDISABLE_INTERRUPTS();

	IFS1bits.U2RXIF = serCLEAR_FLAG;
	IFS1bits.U2TXIF = serCLEAR_FLAG;
	IPC7bits.U2RXIP = configKERNEL_INTERRUPT_PRIORITY;
	IPC7bits.U2TXIP = configKERNEL_INTERRUPT_PRIORITY;
	IEC1bits.U2TXIE = serINTERRUPT_ENABLE;
	IEC1bits.U2RXIE = serINTERRUPT_ENABLE;

       /* pascual */
    if (U2STAbits.OERR==1)
    {
        int t; 
        for (t=0;t<10;t++) cChar=U2RXREG;                    
        U2STAbits.OERR=0;        
    }
    
	/* Clear the Rx buffer. */
	while( U2STAbits.URXDA == serSET_FLAG )
	{
		cChar = U2RXREG;
	}

	xTxHasEnded_BT = pdTRUE;
 
}



xComPortHandle xSerialPortInitMinimal( unsigned long ulWantedBaud, unsigned portBASE_TYPE uxQueueLength )
{
char cChar;

	/* Create the queues used by the com test task. */
	if (xRxedChars == NULL) xRxedChars=xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
	xCharsForTx = xQueueCreate( uxQueueLength, ( unsigned portBASE_TYPE ) sizeof( signed char ) );
    

        /* Setup PINs dspic33f Pascual Pérez */
        
	//U1RX input a RP19
	RPINR18=19; // U1RX al RP19
	TRISCbits.TRISC3=1;

	//U1TX output a RP20
	RPOR10=(RPOR10&0xFF00)|0x0003;

	U1BRG=0x10a;
	

	


	/* Setup the UART. */
	U1MODEbits.BRGH		= serLOW_SPEED;
	U1MODEbits.STSEL	= serONE_STOP_BIT;
	U1MODEbits.PDSEL	= serEIGHT_DATA_BITS_NO_PARITY;
	U1MODEbits.ABAUD	= serAUTO_BAUD_OFF;
	U1MODEbits.LPBACK	= serLOOPBACK_OFF;
	U1MODEbits.WAKE		= serWAKE_UP_DISABLE;
	U1MODEbits.UEN		= serNO_HARDWARE_FLOW_CONTROL;
	U1MODEbits.IREN		= serNO_IRDA;
	U1MODEbits.USIDL	= serCONTINUE_IN_IDLE_MODE;
	U1MODEbits.UARTEN	= serUART_ENABLED;

	U1BRG = (unsigned short)(( (float)configCPU_CLOCK_HZ / ( (float)16 * (float)ulWantedBaud ) ) - (float)0.5);

	U1STAbits.URXISEL	= serINTERRUPT_ON_SINGLE_CHAR;
	U1STAbits.UTXEN		= serTX_ENABLE;
	U1STAbits.UTXINV	= serNORMAL_IDLE_STATE;
	U1STAbits.UTXISEL0	= serINTERRUPT_ON_SINGLE_CHAR;
	U1STAbits.UTXISEL1	= serINTERRUPT_ON_SINGLE_CHAR;

	/* It is assumed that this function is called prior to the scheduler being
	started.  Therefore interrupts must not be allowed to occur yet as they
	may attempt to perform a context switch. */
	portDISABLE_INTERRUPTS();

	IFS0bits.U1RXIF = serCLEAR_FLAG;
	IFS0bits.U1TXIF = serCLEAR_FLAG;
	IPC2bits.U1RXIP = configKERNEL_INTERRUPT_PRIORITY;
	IPC3bits.U1TXIP = configKERNEL_INTERRUPT_PRIORITY;
	IEC0bits.U1TXIE = serINTERRUPT_ENABLE;
	IEC0bits.U1RXIE = serINTERRUPT_ENABLE;

       /* pascual */
    if (U1STAbits.OERR==1)
    {
        int t; 
        for (t=0;t<10;t++) cChar=U1RXREG;                    
        U1STAbits.OERR=0;        
    }
    
	/* Clear the Rx buffer. */
	while( U1STAbits.URXDA == serSET_FLAG )
	{
		cChar = U1RXREG;
	}

	xTxHasEnded = pdTRUE;

	return NULL;
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialGetChar( xComPortHandle pxPort, signed char *pcRxedChar, TickType_t xBlockTime )
{
	/* Only one port is supported. */
	( void ) pxPort;

	/* Get the next character from the buffer.  Return false if no characters
	are available or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxedChars, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}
/*-----------------------------------------------------------*/

signed portBASE_TYPE xSerialPutChar( xComPortHandle pxPort, signed char cOutChar, TickType_t xBlockTime )
{
	/* Only one port is supported. */
	( void ) pxPort;

	/* Return false if after the block time there is no room on the Tx queue. */
	if( xQueueSend( xCharsForTx, &cOutChar, xBlockTime ) != pdPASS )
	{
		return pdFAIL;
	}

	/* A critical section should not be required as xTxHasEnded will not be
	written to by the ISR if it is already 0 (is this correct?). */
	if( xTxHasEnded )
	{
		xTxHasEnded = pdFALSE;
		
       // printf("activando trnasmision");
       // U2TXREG = 'B';;
        IFS0bits.U1TXIF = serSET_FLAG;
    }

    if( xQueueSend( xCharsForTx_BT, &cOutChar, xBlockTime ) != pdPASS )
	{
		return pdFAIL;
	}

	/* A critical section should not be required as xTxHasEnded will not be
	written to by the ISR if it is already 0 (is this correct?). */
	if( xTxHasEnded_BT )
	{
		xTxHasEnded_BT = pdFALSE;
		
       // printf("activando trnasmision");
       // U2TXREG = 'B';;
        IFS1bits.U2TXIF = serSET_FLAG;
	}

    
    
	return pdPASS;
}
/*-----------------------------------------------------------*/


void vSerialClose( xComPortHandle xPort )
{
}
/*-----------------------------------------------------------*/

/*pascual */
int numesc=0;

void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt( void )
{
char cChar;
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	/* Get the character and post it on the queue of Rxed characters.
	If the post causes a task to wake force a context switch as the woken task
	may have a higher priority than the task we have interrupted. */
	IFS0bits.U1RXIF = serCLEAR_FLAG;
    
      /* pascual */
    if (U1STAbits.OERR==1)
    {
        int t; 
        for (t=0;t<10;t++) cChar=U1RXREG;                    
        U1STAbits.OERR=0;        
    }
     
	while( U1STAbits.URXDA )
	{
		cChar = U1RXREG;
        
        if (cChar==27)
            numesc++;
        else
            numesc=0;
            
        if (numesc==3) asm("reset");  // vuelta a bootloader
        
		xQueueSendFromISR( xRxedChars, &cChar, &xHigherPriorityTaskWoken );
	}

	if( xHigherPriorityTaskWoken != pdFALSE )
	{
		taskYIELD();
	}
}
/*-----------------------------------------------------------*/

void __attribute__((__interrupt__, auto_psv)) _U1TXInterrupt( void )
{
signed char cChar;
portBASE_TYPE xTaskWoken = pdFALSE;

	/* If the transmit buffer is full we cannot get the next character.
	Another interrupt will occur the next time there is space so this does
	not matter. */
	IFS0bits.U1TXIF = serCLEAR_FLAG;
    
  
	while( !( U1STAbits.UTXBF ) )
	{
		if( xQueueReceiveFromISR( xCharsForTx, &cChar, &xTaskWoken ) == pdTRUE )
		{
			/* Send the next character queued for Tx. */
			U1TXREG = cChar;
		}
		else
		{
			/* Queue empty, nothing to send. */
			xTxHasEnded = pdTRUE;
			break;
		}
	}

	if( xTaskWoken != pdFALSE )
	{
		taskYIELD();
	}
}

void __attribute__((__interrupt__, auto_psv)) _U2RXInterrupt( void )
{
char cChar;
portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	/* Get the character and post it on the queue of Rxed characters.
	If the post causes a task to wake force a context switch as the woken task
	may have a higher priority than the task we have interrupted. */
	IFS1bits.U2RXIF = serCLEAR_FLAG;
    
      /* pascual */
    if (U2STAbits.OERR==1)
    {
        int t; 
        for (t=0;t<10;t++) cChar=U2RXREG;                    
        U2STAbits.OERR=0;        
    }
     
	while( U2STAbits.URXDA )
	{
		cChar = U2RXREG;
        
        if (cChar==27)
            numesc++;
        else
            numesc=0;
            
        if (numesc==3) asm("reset");  // vuelta a bootloader
        
		xQueueSendFromISR( xRxedChars, &cChar, &xHigherPriorityTaskWoken );
	}

	if( xHigherPriorityTaskWoken != pdFALSE )
	{
		taskYIELD();
	}
}
/*-----------------------------------------------------------*/

void __attribute__((__interrupt__, auto_psv)) _U2TXInterrupt( void )
{
signed char cChar;
portBASE_TYPE xTaskWoken = pdFALSE;

	/* If the transmit buffer is full we cannot get the next character.
	Another interrupt will occur the next time there is space so this does
	not matter. */
	IFS1bits.U2TXIF = serCLEAR_FLAG;
    
  
	while( !( U2STAbits.UTXBF ) )
	{
		if( xQueueReceiveFromISR( xCharsForTx_BT, &cChar, &xTaskWoken ) == pdTRUE )
		{
			/* Send the next character queued for Tx. */
			U2TXREG = cChar;
		}
		else
		{
			/* Queue empty, nothing to send. */
			xTxHasEnded_BT = pdTRUE;
			break;
		}
	}

	if( xTaskWoken != pdFALSE )
	{
		taskYIELD();
	}
}


