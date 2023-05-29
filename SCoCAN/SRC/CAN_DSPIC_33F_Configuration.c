#include <CANTypes.h>
#include "can_scocan.h"
#include "FreeRTOS.h"
#include "util.h"

#include "CAN_DSPIC_33F_Stack.h"


	// Configura el DMA para las transferencias automatizadas a los 32 bufferes 
	// TX buffer de 0-7
	// RX buffer de 8-31
	// RX buffer 8-15 HP filter de 0-7 asociados a buffer 8-15 manejados por una thread HP
	// RX buffer 16-31 LP

	// Buffers de transmisión como máximo pueden ser de 0 al 7
	// Buffers de recepcion como buzon pueden ser de 8-14
	// fifo de recepción sólo hasta a partir de 15-

	// Una vez configurado los 0-7 bufferes como transmisores,
	// que un filtro se mande a la fifo o a un buzon 
	// debe de ser en funcion de la configuracion de la funcion:
	// 



PT_HD id_func_handlers[CAN_NUM_OF_MODULES][MAX_MESSAGES_FUNC];

unsigned int id_variables[CAN_NUM_OF_MODULES][MAX_MESSAGES_FUNC_FIFO];
PT_HD id_variables_ptfunc[CAN_NUM_OF_MODULES][MAX_MESSAGES_FUNC_FIFO];

PT_HD id_default_ptfunc[CAN_NUM_OF_MODULES];


 // como se pone esto en la memoria de DMA
CAN_DSPIC_33F_RX_TX_MESSAGE ECAN_DMA_AREA[32] __attribute__((space(dma)));
// 32*8*2 bytes


void CAN_DSPIC33_Init_Stack(void)
{
	int x,y;
	for (y=0;y<CAN_NUM_OF_MODULES;y++)
	{
        for (x=0;x<MAX_MESSAGES_FUNC;x++)
        {
    		id_variables[y][x]=-1;
    		id_func_handlers[y][x]=NULL;
    	}
        id_default_ptfunc[y]=NULL;
    }
}


/*******************************************************************
  This array stores the base address of each CAN module on the
  device.
  *******************************************************************/
const CAN_DSPIC_33F_REGISTERS * canModules[CAN_NUM_OF_MODULES] = 
{
	(CAN_DSPIC_33F_REGISTERS *)0x0400
	// de la 0x420 depende del bit del win
};


void CAN_DSPIC33_SetSpeed(CAN_MODULE module, int BPR,int PS,int PS1,int PS2,int SJW,int PHTS,int SAM )
{
	// This function sets up the CAN bit time quanta
	 // specifications and the CAN bus speed. 
// 20kbits CAN_DSPIC33_SetSpeed(module,39,7,7,7,CAN_BIT_3TQ,0,0);




	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
    
    // CANCK u TCy--> 40Mhz
    canRegisters->CONF.CTRL1.CANCKS=1;

	
	canRegisters->CONF.CFG2.SEG2PHTS=PHTS;
	canRegisters->CONF.CFG2.SAM=SAM;
	canRegisters->CONF.CFG2.SEG1PH = PS1;
	canRegisters->CONF.CFG2.SEG2PH = PS2;
	canRegisters->CONF.CFG2.PRSEG 		= PS;
	
	canRegisters->CONF.CFG1.SJW			= SJW;
    canRegisters->CONF.CFG1.BRP			= BPR;


}

void CAN_DSPIC33_SetOperatingMode(CAN_MODULE module, CAN_OP_MODE opmode)
{
	// This function sets the CAN module operating mode.

	volatile int res;
	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	res=C1CTRL1;

	canRegisters->CONF.CTRL1.REQOP = opmode;
res=C1CTRL1;

}

CAN_OP_MODE CAN_DSPIC33_GetOperatingMode (CAN_MODULE module)
{
	/* This function returns the current CAN 
	 * operating mode.
	 */

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];

	return(	canRegisters->CONF.CTRL1.OPMODE);

}



void CAN_DSPIC33_EnableModule(CAN_MODULE module, BOOL enable)
{
	// configurar los pines para conectar CAN

	//  RP24  --> c1tx   (pin 4) 
	//  RP25  --> c1rx   (pin 5)  

	// RP24R  ->    Output de 24 va a c1tx  (pag. 167 de DS70291D)
	// RP25R  ->    Input de 25 va a c1rx (pag 166 de DS70291D)
	// ECAN1 Receive CIRX RPINR26 CIRXR<4:0>


	if(enable == TRUE)
	{	
		RPINR26=25; // CAN input RP25;
		RPOR12bits.RP24R=0x10;  // CAN output RP24;		
	}
	else
	{		
	RPINR26=0; // CAN input RP25;
	RPOR12bits.RP24R=0x0;  // CAN output RP24;		
	}


}


int CAN_DSPIC33_First_Free_Filter_from (CAN_MODULE module,int n)
{
	int val;
	int mask;
	int ct;
	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	mask=1<<n;
	ct=n;
	val=canRegisters->CONF.FEN1;
	while (mask)
	{	
		if (val&mask) break;
		mask=mask<<1;
		ct++;
	}
	if (mask)
		 return ct;
	else
		return -1;
}

int CAN_DSPIC33_Filter (CAN_MODULE module,int nbuff,long int id,int n,int num_mask)
{
	int res;	
	int word;
	int mask,id_res;
int x;
	/* module numero de controlador CAN */
	/* nbuff número de buffer donde se almacenará el mensaje */	
	/* 15 IRÁ A FIFO */
	/* identificador para el filtro */
	/* numero de filtro */
	/* número de mascara */
	/* 0 exacta,2 besteffort, 1 no importa nada (peligrosa porque inhabilita el resto */ 
	/* BUFFERS */
	/* 0-7 TX BUffers, programado en BUFFER_TX */
	/* 8-14 RX buzones */
	/* 15 a fifo */

	/* FILTERS */
	/*  0-7 HP  buzones
	    8-14 LP buzones
		15 LP FIFO 
	*/
	/* MASCARAS */
	/* num_mask 
	   	0 exacta, todos los bits importan
		1 no importa ningun bit 
		2 best-effort
	*/
	mask=0xFFFF;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	if (nbuff<15) // HP y LP en buzones
		word=nbuff;
	else
		word=0xF; // a cola 0b1111

	//PARPADEO_valor_ret(0,word>>1,4);

	// en cada registro de FILTER hay cuatro punteros 
	// 13 --> 13%4 = 1  el filtro 13 va en los bits 4-7 
	// word<<4<<1-1 --> word<<4 
	res=n%4;
	switch (res)
	{
		case 0: word=word; break;
		case 1: word=word<<4; break;
		case 2: word=word<<8; break;
		case 3: word=word<<12; break;
	}	

//PARENTIzAR!!!!!!!!!

	//PARPADEO_valor_ret(0,word>>1,4);
	// cambiar a window 1
	canRegisters->CONF.CTRL1.WIN = 1;

	switch(n/4)
	{
		case 0: 
				canRegisters->WIN.W_1.BUFPNT1|=word; 
				break;
		case 1: canRegisters->WIN.W_1.BUFPNT2|=word;
				break;
		case 2: canRegisters->WIN.W_1.BUFPNT3|=word;
				break;
		case 3: canRegisters->WIN.W_1.BUFPNT4|=word;
				break;
	}
	
	// Una vez configurada la dirección donde van los datos 

	// asociación de filtro<->mascara 
	// hay 16 filtros y 3 mascaras  
	// por registro 16
	// n=0 word << (0 << 1) word <<0
	// n=1 word << (1 << 1) word <<2
 	word=num_mask&0x03;
	res=n%8;
	word=word<<(res<<1);
	
	switch(n/8)
	{
		case 0: canRegisters->CONF.FMSKSEL1|=word; 
				break;
		case 1: canRegisters->CONF.FMSKSEL2|=word;
				break;
	}
	
	/* modificación de la mascara 2 para best effort */	
	if (num_mask==2)
	{
	
		id_res=id;
		x=0;
		while(id_variables[ module][x]!=-1)
		{
  			 mask=mask&(~(id_res^id_variables[module][x]));	
			x++;
			if (x==MAX_MESSAGES_FUNC_FIFO)
				break;

		} 
		id_variables[ module][x]=id;
	}
	// programacion de las 2 mascaras siempre 
	// 0 exact filter
	// 1 variable
	
	// sólo mascaras estandar

	// MIDE 0;
	
	// cambiar a window 1
	canRegisters->CONF.CTRL1.WIN = 1;

	// los bits a 1 importan a 0 no importan 
	// Mascara 0 mascara exacta, todos los bits importan

	canRegisters->WIN.W_1.RXM[0].MASKbits.SID=0x7FF; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXM[0].MASKbits.EID_17_16=0; 
	canRegisters->WIN.W_1.RXM[0].MASKbits.MIME=0x1;
	canRegisters->WIN.W_1.RXM[0].MASKbits.EID_00_15=0;
	
	// Mascara 1 LP no importa ningun bit --> no debería emplearse
	
	canRegisters->WIN.W_1.RXM[1].MASKbits.SID=0x000; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXM[1].MASKbits.EID_17_16=0x0; 
	canRegisters->WIN.W_1.RXM[1].MASKbits.MIME=0x0;
	canRegisters->WIN.W_1.RXM[1].MASKbits.EID_00_15=0x0000;

	// Mascara 2 LP best-effort -> siempre pasa por un bucle que comprueba los id

	canRegisters->WIN.W_1.RXM[2].MASKbits.SID=mask&0xFFF; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXM[2].MASKbits.EID_17_16=0x0; 
	canRegisters->WIN.W_1.RXM[2].MASKbits.MIME=0x1;
	canRegisters->WIN.W_1.RXM[2].MASKbits.EID_00_15=0x0000;

	// programar el id 
	// se asume que son palabras consecutivas 
	
	canRegisters->WIN.W_1.RXF[n].IDbits.SID=id; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXF[n].IDbits.EID_17_16=0x0; 
	canRegisters->WIN.W_1.RXF[n].IDbits.EXIDE=0x0;
	canRegisters->WIN.W_1.RXF[n].IDbits.EID_00_15=0x0000;

	// habilitar filtro
	canRegisters->CONF.FEN1=(canRegisters->CONF.FEN1)|(1<<n);
	return  OK;
}

int CAN_DSPIC33_Association_Filter_to_Handle(CAN_MODULE module,int nbuff,PT_HD handle)
{

	if (id_func_handlers[module][nbuff]==NULL)
	{
		id_func_handlers[module][nbuff]=handle;
		return OK;
	}

	return ERROR;
}

int CAN_DSPIC33_Association_FIFO_ID_to_Handle(CAN_MODULE  module,unsigned long int id,PT_HD handle)
{
	int ctx;

		for (ctx=0;ctx<MAX_MESSAGES_FUNC_FIFO;ctx++)
		{
			if (id_variables[CAN1][ctx]==id)
				{
					id_variables_ptfunc[module][ctx]=handle;
					return OK;
				}
		}
	
	return ERROR;
}

int CAN_DSPIC33_Association_FIFO_Default_to_Handle(CAN_MODULE  module,PT_HD handle)
{
	int ctx;

    if (id_default_ptfunc[module]!=NULL)
        return ERROR;
    else
    {
        id_default_ptfunc[module]=handle;
        return OK;
    }
}



int CAN_DSPIC33_SetDMA (CAN_MODULE module)
{
	// Configura el DMA para las transferencias automatizadas a los 32 bufferes 
	// TX buffer de 0-7
	// RX buffer de 8-31
	// RX buffer 8-15 HP filter de 0-7 asociados a buffer 8-15 manejados por una thread HP
	// RX buffer 16-31 LP
	

	// 8-14 LP con filtro fijo a queue manejados por un thread LP
	// 15 con mascara variable 
	
	// FIFO CAN
		CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
    // la fifo empieza en el buffer 16
		canRegisters->CONF.FCTRL=0xC010;  // 32 bufferes para DMA 
										 // RX QUEUE comientza en el buffer 16;
	///////////////////////////////////////////////////////////////////////////////////////////	
	// ojo si hubiesen dos controladores ECAN se machacaría la configuración de los canales
	//////////////////////////////////////////////////////////////////////////////////////////

	// canales DMA 0 for TX
	
	// Data Transfer Size: Word Transfer Mode 
	DMA0CONbits.SIZE = 0x0;
	// Data Transfer Direction: DMA RAM to Peripheral 
	DMA0CONbits.DIR = 0x1;
	// DMA Addressing Mode: Peripheral Indirect Addressing mode 
	DMA0CONbits.AMODE = 0x2;   // la parte baja del inicio de transmision la pone el periferico,
							   // en este caso ECAN con el BPNT	
	// Operating Mode: Continuous, Ping-Pong modes disabled 
	DMA0CONbits.MODE = 0x0;
	// Assign ECAN1 Transmit event for DMA Channel 0 
	DMA0REQ = 70; // una interrupcion por peticion de transmision es equivalente a un DMA_REQ del canal al que se conecta ECAN
	// Set Number of DMA Transfer per ECAN message to 8 words */
	DMA0CNT = 7;
	// Peripheral Address: ECAN1 Transmit Register 
	DMA0PAD = (int) (&(canRegisters->WIN.W_0.TXD)); // aqui da igual como este el bit de Window (creo, una rayada de microchip)
	// Start Address Offset for ECAN1 Message Buffer 0x0000 
	DMA0STA = __builtin_dmaoffset(ECAN_DMA_AREA);
	
	// Channel Enable: Enable DMA Channel 0 
	DMA0CONbits.CHEN = 0x1;
	/* Channel Interrupt Enable: Enable DMA Channel 0 Interrupt */

	///////////////////////////////////////////////////////////////////////////////////////////	
	// ojo si hubiesen dos controladores ECAN se machacaría la configuración de los canales
	//////////////////////////////////////////////////////////////////////////////////////////

	// canales DMA 1 for RX

    // Data Transfer Size: Word Transfer Mode 
	DMA1CONbits.SIZE = 0x0;
	// Data Transfer Direction: Peripheral to DMA RAM 
	DMA1CONbits.DIR = 0x0;
	// DMA Addressing Mode: Peripheral Indirect Addressing mode 
	DMA1CONbits.AMODE = 0x2;
	// Operating Mode: Continuous, Ping-Pong modes disabled 
	DMA1CONbits.MODE = 0x0;
	// Assign ECAN1 Receive event for DMA Channel 0 
	DMA1REQ = 34;
	// Set Number of DMA Transfer per ECAN message to 8 words 
	DMA1CNT = 7;
	// Peripheral Address: ECAN1 Receive Register 
	DMA1PAD = (int) (&(canRegisters->WIN.W_0.RXD));
	// Start Address Offset for ECAN1 Message Buffer 0x0000 
	DMA1STA =__builtin_dmaoffset(ECAN_DMA_AREA);
	// Channel Enable: Enable DMA Channel 1 
	DMA1CONbits.CHEN = 0x1;

	return OK;	
}


int CAN_DSPIC33_Disable_Reset_interrupts_Stack(CAN_MODULE module)
{


	if (module==CAN1)
	{

		/* prioridades...muy importante en free rtos a la hora de manipular semaforos*/
	/* Setup interrupt priority. */
	IPC3bits.DMA1IP = configKERNEL_INTERRUPT_PRIORITY;

	IEC0bits.DMA0IE = 0;   // habilitar interrupcion por fin de transferencia TX, no quiere decir que haya sido transmitido
						   // ¿?
  	IEC0bits.DMA1IE = 0;   // habilitar interrupcion por fin de transferencia RX
	IEC2bits.C1IE = 0;     // habilitar interrupcion por eventos en CAN
	IEC2bits.C1RXIE = 0;   // deshabilitar interrupcion por RX, lo dirá el DMA
	IEC4bits.C1TXIE = 0;	// habilitar interrupcion por fin de transferencia TX, , lo dirá el DMA

    
    IFS0bits.DMA0IF=0;
    IFS0bits.DMA1IF=0;
    IFS2bits.C1IF=0;
    IFS2bits.C1RXIF=0;
    IFS4bits.C1TXIF=0;
    
    
    
    
    C1INTF=0x0000;
	C1INTE=0X0000; // todas las interrupciones habilitadas si se habilitan aqui
					   // y en el controlador de interrupciones están habilitadas 
					   // se produce una interrupción y salta al vector de interrupciones asociado al
					   // controlador.
    
    
    
	return OK;
	}
	else
	return ERROR;
}


int CAN_DSPIC33_Enable_interrupts_Stack(CAN_MODULE module)
{


	if (module==CAN1)
	{

		/* prioridades...muy importante en free rtos a la hora de manipular semaforos*/
	/* Setup interrupt priority. */
	IPC3bits.DMA1IP = configKERNEL_INTERRUPT_PRIORITY;

	IEC0bits.DMA0IE = 1;   // habilitar interrupcion por fin de transferencia TX, no quiere decir que haya sido transmitido
						   // ¿?
  	IEC0bits.DMA1IE = 1;   // habilitar interrupcion por fin de transferencia RX
	IEC2bits.C1IE = 1;     // habilitar interrupcion por eventos en CAN
	IEC2bits.C1RXIE = 0;   // deshabilitar interrupcion por RX, lo dirá el DMA
	IEC4bits.C1TXIE = 0;	// habilitar interrupcion por fin de transferencia TX, , lo dirá el DMA

	return OK;
	}
	else
	return ERROR;
}


int CAN_DSPIC33_Enable_interrupts_Devices(CAN_MODULE module)
{

	if (module==CAN1)
	{
		C1INTF=0x0000;
		C1INTE=0X000C; // todas las interrupciones habilitadas si se habilitan aqui
					   // y en el controlador de interrupciones están habilitadas 
					   // se produce una interrupción y salta al vector de interrupciones asociado al
					   // controlador.
	return OK;
	// si las trasnferencias son por dma habilitar la interrupciones
	}
	else
	return ERROR;
	
}




int CAN_DSPIC33_Stack_SetBitRate(CAN_MODULE module, int modBitRate)
{
  // se asume una frecuancia deprocesador de 80 Mhz
  // para emplear el preescale 
	int res;
   
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_CONFIGURATION)
		return ERROR;

	switch (modBitRate)
	{
		case BR_1Mbit:

// This code example shows how to configure the CAN module to obtain a 
// specific bit rate. 
// This example implements the configuration shown in Example 34-16. 
// Fsys = System Clock Frequency = 80000000; 
// Fbaud = CAN bit rate = 1000000; 
// N = Time Quanta (Tq) per bit = 10; 
// Prop Segment = 3Tq 
// Phase Seg 1 = 3Tq 
// Phase Seg 2 = 3Tq 
// Sync Jump Width = 2Tq 

//Pascual 
		//(CAN_MODULE module, int BPR,int PS,int PS1,int PS2,int SJW,int PHTS,int SAM )
		// 1Mbit/s 12Mhz CAN_DSPIC33_SetSpeed(module,1,CAN_BIT_1TQ,CAN_BIT_4TQ,CAN_BIT_4TQ,CAN_BIT_3TQ,1,0);
		
		CAN_DSPIC33_SetSpeed(module,1,0,3,2,CAN_BIT_1TQ,0,0);
		res=OK;	
		break;
		case BR_500kbits:
             CAN_DSPIC33_SetSpeed(module,3,0,3,2,CAN_BIT_1TQ,0,0);
             res=OK;	
			
			 break;
        case BR_250kbits:
             CAN_DSPIC33_SetSpeed(module,7,0,3,2,CAN_BIT_1TQ,0,0);
             res=OK;	
			
			 break;
        case BR_125kbits:
            CAN_DSPIC33_SetSpeed(module,15,0,3,2,CAN_BIT_1TQ,0,0);
             res=OK;	
			 break;
        
        case BR_20kbits:
             CAN_DSPIC33_SetSpeed(module,39,7,7,7,CAN_BIT_3TQ,0,0);
			 res=OK;
			 break;
		
        case BR_10kbits:
             //no llega 
             //CAN_DSPIC33_SetSpeed(module,7,7,7,7,CAN_BIT_3TQ,0,0);
			 res=ERROR;
			 break;
		default:
			 res=ERROR;
	};
     if (res==ERROR) printf("Error en bitrate, velocidad no permitida\n");
   
	return res;
}





int CAN_DSPIC33_Set_TX_BUFFERS (CAN_MODULE module)
{

	int ct;
	// los 8 buffers de tx *7
		CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	// el buffer 0 el más prioritario (3);
    // el buffer 3,4,5,6,7 prioridad  (0)

	

	canRegisters->CONF.CTRL1.WIN = 0;



	for (ct=0;ct<8;ct++)
	{
		canRegisters->WIN.W_0.TRmnCON[ct].TXEN=1;
		canRegisters->WIN.W_0.TRmnCON[ct].TXPRI=0;
	}


	canRegisters->WIN.W_0.TRmnCON[0].TXPRI=3;
	canRegisters->WIN.W_0.TRmnCON[1].TXPRI=2;
	canRegisters->WIN.W_0.TRmnCON[2].TXPRI=1;

	return OK;
}
