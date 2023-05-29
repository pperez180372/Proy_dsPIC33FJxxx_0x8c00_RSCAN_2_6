#include "CAN_DSPIC_33F_Stack.h"
#include "can_scocan.h"

/* 4.- definicion de tx,rx,init
*/

//#include "GenericTypeDefs.h"
//#include "Compiler.h"
//#include "HardwareProfile.h"

#include "FreeRTOS.h"

#include "CAN_DSPIC_33F_Stack.h"




// 32 bufferes en total 
// 0-7 primeros pueden ser TX/RX --> serán definidos para transmisión 
// 8-15 para RX no puede hacerse una cola con ellos -> serán definidos como HP
// 16-31 sólo para uso como cola de recepción -> serán definidos como LP

 // como se pone esto en la memoria de DMA

/* sólo se aceptan los mensajes que hay en los filtros */
/* HP 8 filtros */
/* LP 7 filtros exactos */
/* LP 1 filtro con mascara variable, por defecto deshabilitado */ 

// 2's fifo 

portTickType xTimeOutCAN_0;


/* Ojo con las interrupciones y DMA */
/* La linea de interrupción es empleada TAMBIEN para realziar un DMAREQ */
/* cuando se termina la transferencia se genera una interrupcion por fin de transferencia */
/* por lo que se debe inhabilitddar alguna de las mismas 

lo lógico es inhabilitar la del periferico */

int CAN_DSPIC_33F_Init(CAN_MODULE module,int kbits)
{


	CAN_DSPIC33_SetOperatingMode(module,CAN_CONFIGURATION);
	
	while(CAN_DSPIC33_GetOperatingMode(module)!=CAN_CONFIGURATION);
	

	CAN_DSPIC33_Init_Stack();  // no configura ningun bit del controlador

	if (CAN_DSPIC33_Stack_SetBitRate(module, kbits)==ERROR)
		return ERROR;
//  if (CAN_DSPIC33_Stack_Configure_Messages(module)==ERROR)
//		return ERROR;
	if (CAN_DSPIC33_Set_TX_BUFFERS(module)==ERROR)		
		return ERROR;
	if (CAN_DSPIC33_SetDMA (module)==ERROR)
		return ERROR;

	if (CAN_DSPIC33_Enable_interrupts_Stack(module)==ERROR)
		return ERROR;

	CAN_DSPIC33_EnableModule(module, TRUE);
	return OK;
}



int CAN_DSPIC33_Stack_Configure_Messages(CAN_MODULE module )
{
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_CONFIGURATION)
	return ERROR;
	
	// se invoca a las funciones para definir cada mensaje 
	
	return ERROR;
}

unsigned char CAN_DSPIC_33F_Get_char_of_Message_buffer(CAN_MODULE module,int n_buff,int num)
{
	return ECAN_DMA_AREA[n_buff].DATA[num];
}

void CAN_DSPIC_33F_Get_data_of_Message_buffer(CAN_MODULE module,int n_buff,int numini,int numfin,char * pt)
{
	int ct;
	for (ct=numini;ct<=numfin;ct++)
		*(pt+ct-numini)=ECAN_DMA_AREA[n_buff].DATA[ct];
}



int CAN_DSPIC_33F_SetupMessage_sort(CAN_MODULE module,int n_buff,int length, char * buffer_or)
{
	int ct;

	ECAN_DMA_AREA[n_buff].DLC=length;
   
	for (ct=0;ct<length;ct++)
		ECAN_DMA_AREA[n_buff].DATA[ct]= *(buffer_or+ct); // Byte 0 Data 
	return OK;
}


int CAN_DSPIC_33F_SetupMessage(CAN_MODULE module,int n_buff,int id,int length,int rtr, char * buffer_or)
{

	int res;

	if (n_buff>8) 
		return ERROR;
 	
	ECAN_DMA_AREA[n_buff].RTR=rtr;
	ECAN_DMA_AREA[n_buff].IDE=0;
	ECAN_DMA_AREA[n_buff].SID=id;

	res=CAN_DSPIC_33F_SetupMessage_sort(module,n_buff,length, buffer_or);
	
	return OK;
}




int CAN_DSPIC_33F_SendMessage(CAN_MODULE module,int n_buff)
{

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;
	
	// cambiar a window 1
	canRegisters->CONF.CTRL1.WIN = 0;
	canRegisters->WIN.W_0.TRmnCON[n_buff].TXREQ=1;

	return ERROR;	

}

int CAN_DSPIC_33F_TX_BUFF_free(CAN_MODULE module,int ct)
{
//	int mask;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;
	
	// cambiar a window 1
	canRegisters->CONF.CTRL1.WIN = 0;
	
	// 1 si esta libre TXREQ=0
	// 0 si no esta libre TXREQ=1
	// -1 error 

	return (canRegisters->WIN.W_0.TRmnCON[ct].TXREQ==0);	
}


int CAN_DSPIC_33F_SetupMessage_firstfree(CAN_MODULE module,int id,int length,int rtr, char * buffer_or)
{
	// busqueda de un buffer de transmisión libre
	int ct;
	int res;

	for (ct=0;ct<8;ct++)
	{
		res=CAN_DSPIC_33F_TX_BUFF_free(module,ct);
		if (res==1)
		{
			CAN_DSPIC_33F_SetupMessage(module,ct,id,length,rtr,buffer_or);	
			break;
		}	
	}
	
	if (res==1)
		return OK;
	else
		return ERROR;
}

int CAN_DSPIC_33F_Get_Message_ID_in_FIFO_FIRST(CAN_MODULE module)
{
	//lee el puntero del primer buffer ocupado
	int pb;
	pb=CAN_DSPIC_33F_get_first_buffer_busy_in_FIFO(module);
	return CAN_DSPIC_33F_Get_Message_ID_in_FIFO(module,pb);

	
}
int CAN_DSPIC_33F_Get_Message_DLC_in_FIFO_FIRST(CAN_MODULE module)
{
	//lee el puntero del primer buffer ocupado
	int pb;
	pb=CAN_DSPIC_33F_get_first_buffer_busy_in_FIFO(module);
	return CAN_DSPIC_33F_Get_Message_DLC_in_FIFO(module,pb);

}
int CAN_DSPIC_33F_Get_Message_DATA_in_FIFO_FIRST(CAN_MODULE module,int pos)
{
	//lee el puntero del primer buffer ocupado
	int pb;
	pb=CAN_DSPIC_33F_get_first_buffer_busy_in_FIFO(module);
	return CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(module,pb,pos);
}

int CAN_DSPIC_33F_Get_Message_ID_in_FIFO(CAN_MODULE module,int pb)
{


	if (pb<0) 
		return ERROR;
	return ECAN_DMA_AREA[pb].SID;
}

int CAN_DSPIC_33F_Get_Message_DLC_in_FIFO(CAN_MODULE module,int pb)
{

	if (pb<0) 
		return ERROR;
	return ECAN_DMA_AREA[pb].DLC;
}
int CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN_MODULE module,int pb,int pos)
{

	if (pb<0) 
		return ERROR;

	pos=pos%8;
	return ECAN_DMA_AREA[pb].DATA[pos];
}





int CAN_DSPIC_33F_get_first_buffer_busy_in_FIFO(CAN_MODULE module)
{
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	return canRegisters->CONF.FIFO.nextbusy;
}

int CAN_DSPIC_33F_get_first_buffer_free_in_FIFO(CAN_MODULE module)
{
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	return canRegisters->CONF.FIFO.nextfree;
}


int CAN_DSPIC_33F_Release_buffer_in_FIFO(CAN_MODULE module, int n_buff)
{	
	T_SFR * pt_flag;
	int pos;
	unsigned int mask;
	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;
	
	if (n_buff>31)
		return ERROR;

	canRegisters->CONF.CTRL1.WIN=0;
	if (n_buff>15)
	{
		pos=n_buff-16;
		pt_flag=&canRegisters-> WIN.W_0.RXFUL2;
	}
	else
	{
		pos=n_buff;
		pt_flag=&canRegisters-> WIN.W_0.RXFUL1;
	}
	mask=~(1<<pos);
	*pt_flag=(*pt_flag)&mask;
		
	return OK;	

}

int hit_MSG(CAN_MODULE module, int n_buff)
{
	// sólo comprueba los 8 bufferes de recp más prioridad que coinciden 
	// con los bufferes de 8-15

	T_SFR * pt_flag;
	int pos;
	unsigned int mask;
    int res;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;
	
	if (n_buff>31)
		return ERROR;

	canRegisters->CONF.CTRL1.WIN=0;
	
	if (n_buff>15)
	{
		pos=n_buff-16;
		pt_flag=&canRegisters-> WIN.W_0.RXFUL2;
	}
	else
	{
		pos=n_buff;
		pt_flag=&canRegisters-> WIN.W_0.RXFUL1;
	}

	mask=(1<<pos);
	res=(*pt_flag)&mask;
	
	if (res) 
		return TRUE;	
	else
		return FALSE;
}

	  

inline int IN_FAST_hit_MSG(CAN_MODULE module, int mask)
{
	// sólo comprueba los 8 bufferes de recp más prioridad que coinciden 
	// con los bufferes de 8-15

	T_SFR * pt_flag;
    int res;

	CAN_DSPIC_33F_REGISTERS * canRegisters = ( CAN_DSPIC_33F_REGISTERS *)canModules[module];
	
	if (CAN_DSPIC33_GetOperatingMode(module) != CAN_NORMAL_OPERATION)
		return ERROR;

	canRegisters->CONF.CTRL1.WIN=0;
	pt_flag=&canRegisters-> WIN.W_0.RXFUL1;
	

	res=(*pt_flag)&mask;
	
	if (res) 
		return TRUE;	
	else
		return FALSE;
}
