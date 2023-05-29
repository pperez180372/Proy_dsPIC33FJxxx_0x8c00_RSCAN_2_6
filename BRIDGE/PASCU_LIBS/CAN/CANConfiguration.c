#include <can/CANTypes.h>
#include <can/CAN.h>
#include <p33FJ64MC804.h>

#include "can/CAN_DSPIC_33F_Stack.h"

#define MAX_MESSAGES_VAR 32
unsigned int id_variables[CAN_NUM_OF_MODULES][MAX_MESSAGES_VAR];
 // como se pone esto en la memoria de DMA
unsigned int ECAN_DMA_AREA[32][8] __attribute__((space(dma)));
// 32*8*2 bytes


void CAN_DSPIC33_Init_Stack(void)
{
	int x,y;
	for (y=0;y<CAN_NUM_OF_MODULES;y++)
	for (x=0;x<MAX_MESSAGES_VAR;x++)
	id_variables[y][x]=-1;
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

/*******************************************************************
  This array stores the mapping between a filter and its filter control
  register. 
  *******************************************************************/
/*const CAN_FLTCON_BYTES canFilterControlMap[CAN_NUM_OF_FILTERS] = 
{
	{CAN_FILTER_CONTROL0,0,0x80 	 },
	{CAN_FILTER_CONTROL0,1,0x8000 	 },
	{CAN_FILTER_CONTROL0,2,0x800000	 },
	{CAN_FILTER_CONTROL0,3,0x80000000},
	{CAN_FILTER_CONTROL1,0,0x80 	 },
	{CAN_FILTER_CONTROL1,1,0x8000 	 },
	{CAN_FILTER_CONTROL1,2,0x800000	 },
	{CAN_FILTER_CONTROL1,3,0x80000000},
	{CAN_FILTER_CONTROL2,0,0x80 	 },
	{CAN_FILTER_CONTROL2,1,0x8000 	 },
	{CAN_FILTER_CONTROL2,2,0x800000	 },
	{CAN_FILTER_CONTROL2,3,0x80000000},
	{CAN_FILTER_CONTROL3,0,0x80 	 },
	{CAN_FILTER_CONTROL3,1,0x8000 	 },
	{CAN_FILTER_CONTROL3,2,0x800000	 },
	{CAN_FILTER_CONTROL3,3,0x80000000},
	{CAN_FILTER_CONTROL4,0,0x80 	 },
	{CAN_FILTER_CONTROL4,1,0x8000 	 },
	{CAN_FILTER_CONTROL4,2,0x800000	 },
	{CAN_FILTER_CONTROL4,3,0x80000000},
	{CAN_FILTER_CONTROL5,0,0x80 	 },
	{CAN_FILTER_CONTROL5,1,0x8000 	 },
	{CAN_FILTER_CONTROL5,2,0x800000	 },
	{CAN_FILTER_CONTROL5,3,0x80000000},
	{CAN_FILTER_CONTROL6,0,0x80 	 },
	{CAN_FILTER_CONTROL6,1,0x8000 	 },
	{CAN_FILTER_CONTROL6,2,0x800000	 },
	{CAN_FILTER_CONTROL6,3,0x80000000},
	{CAN_FILTER_CONTROL7,0,0x80 	 },
	{CAN_FILTER_CONTROL7,1,0x8000 	 },
	{CAN_FILTER_CONTROL7,2,0x800000	 },
	{CAN_FILTER_CONTROL7,3,0x80000000}
};                        
*/

void CAN_DSPIC33_SetSpeed(CAN_MODULE module, const CAN_BIT_CONFIG * canBitConfig, UINT32 sysClock
                    , UINT32 canBusSpeed    )
{
	// This function sets up the CAN bit time quanta
	 // specifications and the CAN bus speed. 

    UINT totalTq;
	UINT prescalar;

	totalTq = (canBitConfig->phaseSeg1Tq + 1) + (canBitConfig ->phaseSeg2Tq + 1)
		     + (canBitConfig->propagationSegTq + 1) + 1;

	prescalar = (sysClock/(canBusSpeed * totalTq * 2)) - 1;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];

	canRegisters->CONF.CFG2.SEG2PHTS=canBitConfig->phaseSeg2TimeSelect;
	canRegisters->CONF.CFG2.SAM=canBitConfig->sample3Time;
	canRegisters->CONF.CFG2.SEG1PH = canBitConfig->phaseSeg1Tq;
	canRegisters->CONF.CFG2.SEG2PH 		= canBitConfig->phaseSeg2Tq;
	canRegisters->CONF.CFG2.PRSEG 		= canBitConfig->propagationSegTq;
	
	canRegisters->CONF.CFG1.SJW			= canBitConfig->syncJumpWidth;
    canRegisters->CONF.CFG1.BRP			= prescalar;	

}

void CAN_DSPIC33_SetOperatingMode(CAN_MODULE module, CAN_OP_MODE opmode)
{
	// This function sets the CAN module operating mode.
	 
	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	canRegisters->CONF.CTRL1.REQOP = opmode;
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
		RPINR26=0x19; // CAN input RP25;
		RPOR12bits.RP24R=0x10;  // CAN output RP24;		
	}
	else
	{		
	RPINR26=0x0; // CAN input RP25;
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

int CAN_DSPIC33_Filter (CAN_MODULE module,int n,long int id)
{
	int res;	
	int word;
	int mask,id_res;
int x;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	res=id%4;
	if (n<8) // HP
		word=8+n;
	else
		word=1111; // a cola
	word=word<<(res<<2); // de 4 en 4
	
	// cambiar a window 1
	canRegisters->CONF.CTRL1.WIN = 1;

	switch(id/4)
	{
		case 0: canRegisters->WIN.W_1.BUFPNT1|=word; 
				break;
		case 1: canRegisters->WIN.W_1.BUFPNT2|=word;
				break;
		case 2: canRegisters->WIN.W_1.BUFPNT3|=word;
				break;
		case 3: canRegisters->WIN.W_1.BUFPNT4|=word;
				break;
	}
	
	/* asociacion de mascara */
	
	res=id%8;
	if (n<15) 
		word=0; // fixed mask
	else      
		word=1; // // variable mask

	word=word<<(res<<1); // de 2 en 2
	
	switch(id/8)
	{
		case 0: canRegisters->CONF.FMSKSEL1|=word; 
				break;
		case 1: canRegisters->CONF.FMSKSEL1|=word;
				break;
	}
	
	/* modificación de la mascara */	
	mask=0xFFFF;
	id_res=-1;
	for (x=0;x<MAX_MESSAGES_VAR;x++)
		if (id_variables[ module][x]!=-1)
		{
			if (id_res==-1) // el primer id
				 id_res=id_variables[ module][x];
			else 
		    {
				 mask=mask&(~(id_res ^id_variables[module][x]));
		    }
		}

	// programacion de las 2 mascaras siempre 
	// 0 exact filter
	// 1 variable
	
	// sólo mascaras estandar

	// MIDE 0;
	
	// cambiar a window 1
	canRegisters->CONF.CTRL1.WIN = 1;

	canRegisters->WIN.W_1.RXM[0].MASKbits.SID=0x7FF; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXM[0].MASKbits.EID_17_16=0x3; 
	canRegisters->WIN.W_1.RXM[0].MASKbits.MIME=0x0;
	canRegisters->WIN.W_1.RXM[0].MASKbits.EID_00_15=0xFFFF;
	// mascara 1 LP no importa ningun bit
	
	canRegisters->WIN.W_1.RXM[1].MASKbits.SID=mask&0x7FF; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXM[1].MASKbits.EID_17_16=0x3; 
	canRegisters->WIN.W_1.RXM[1].MASKbits.MIME=0x0;
	canRegisters->WIN.W_1.RXM[1].MASKbits.EID_00_15=0xFFFF;

	// programar el id 
	// se asume que son palabras consecutivas 
	
	canRegisters->WIN.W_1.RXF[n].IDbits.SID=id&0x7FF; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
	canRegisters->WIN.W_1.RXF[n].IDbits.EID_17_16=0x0; 
	canRegisters->WIN.W_1.RXF[n].IDbits.EXIDE=0x0;
	canRegisters->WIN.W_1.RXF[n].IDbits.EID_00_15=0x0000;

	// habilitar filtro
	canRegisters->CONF.FEN1=canRegisters->CONF.FEN1|(1<<n);

	return  OK;
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


int CAN_DSPIC33_Enable_interrupts_Stack(CAN_MODULE module)
{
	

	IEC0bits.DMA0IE = 1;   // habilitar interrupcion por fin de transferencia TX, no quiere decir que haya sido transmitido
						   // ¿?
  	IEC0bits.DMA1IE = 1;   // habilitar interrupcion por fin de transferencia RX
	IEC2bits.C1IE = 1;     // habilitar interrupcion por eventos en CAN
	IEC2bits.C1RXIE = 0;   // deshabilitar interrupcion por RX, lo dirá el DMA
	IEC4bits.C1TXIE = 0;	// habilitar interrupcion por fin de transferencia TX, , lo dirá el DMA

	return OK;
}


int CAN_Stack_SetBitRate(CAN_MODULE module,int fsysKhz, int modBitRate)
{

 // Configure the CAN Module Clock. The  CAN_BIT_CONFIG data structure is used
 //  * for this purpose. The propagation segment, phase segment 1 and phase segment 2
 //  * are configured to have 3TQ. The CANSetSpeed function sets the baud. The CPU
 //  * core frequency is 80000000 Hz and desired CAN bus speed is 250000 bps.
  

    CAN_BIT_CONFIG canBitConfig;
   // UINT baudPrescalar;
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

	 	canBitConfig.phaseSeg2Tq            = CAN_BIT_4TQ;
	    canBitConfig.phaseSeg1Tq            = CAN_BIT_4TQ;
	    canBitConfig.propagationSegTq       = CAN_BIT_2TQ;
	    canBitConfig.phaseSeg2TimeSelect    = TRUE;
	    canBitConfig.sample3Time            = FALSE;
	    canBitConfig.syncJumpWidth          = CAN_BIT_3TQ;
//		baudPrescalar = CANCalcBitClockPrescalar(&canBitConfig,80000000,1000000);	
		res=OK;	
		break;
		case BR_100kbit:
			 res=ERROR;
			 break;
		default:
			 res=ERROR;
	}

    CAN_DSPIC33_SetSpeed(module,&canBitConfig,80000000,1000000);

	return res;
}
