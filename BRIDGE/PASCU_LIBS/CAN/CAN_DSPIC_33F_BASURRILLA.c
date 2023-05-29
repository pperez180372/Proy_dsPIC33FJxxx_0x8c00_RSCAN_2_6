/*
int ct;

CANTxMessageBuffer * buffer;
buffer=CANGetTxMessageBuffer(module,0);

// borra buffer
buffer->messageWord[0] = 0;
buffer->messageWord[1] = 0;
buffer->messageWord[2] = 0;
buffer->messageWord[3] = 0;

// rellena buffer

//rellenar el buffer con la información enviada 

buffer->msgEID.DLC=length;
buffer->msgEID.RTR=rtr;
buffer->msgSID.SID = (id>>18)&0x7FF;      	// 11 bits Message SID 
if (can2b) // extended
{
buffer->msgEID.IDE = 1;
buffer->msgEID.EID = (id&0x3FFFF);			//18  Message SID 
}

for (ct=0;ct<length;ct++)
	buffer->data[ct] = *(buffer_or+ct); // Byte 0 Data 

CANUpdateChannel(module, 0);
CANFlushTxChannel(module,0);

return OK;

}



*/

/*



int CAN_Stack_SetBuffer_Monitor(CAN_MODULE module)
{


// 32 bufferes en total 
// 0-7 primeros pueden ser TX/RX --> serán definidos para transmisión 
// 8-15 para RX no puede hacerse una cola con ellos -> serán definidos como HP
// 16-31 sólo para uso como cola de recepción -> serán definidos como LP
//unsigned int TX_HPCANMSG[8][CAN_TX_RX_MESSAGE_SIZE_BYTES];
//unsigned int RX_HPCANMSG[8][CAN_TX_RX_MESSAGE_SIZE_BYTES];
//unsigned int RX_LPCANMSG_QUEUE[16][CAN_TX_RX_MESSAGE_SIZE_BYTES];




/////////////////////////////////// MASK
// programación de las mascaras 
// los mensajes de HP utilizan el mascara exacta 
// los de LP aceptan conforme se va programando por defecto todo 
// dos mascaras HP y LP

// mascara 0 HP todos los bits importan acepta standard y extended
// MIDE 0;

C1RXM0SID=0xFFE3; // SID=0x7FF MIDE=0 EID(17-16)=0x3;
C1RXM0SEID=0xFFFF; 

// mascara 1 LP no importa ningun bit
C1RXM1SID=0x0000;
C1RXM1SEID=0x0000;


////////////////////////////////////////////// FILTER 
// No se pograma los filtros de HP y las mascaras de LP tampoco
C1RXF0SID
C1RXF0EID

para LP solo se trabaja con la mascara


////////////////////////////////////////////// FILTER ADDRESS
// programación de los filtros por defecto
// direcciones de los bufferes para cada filtros 
C1BUFPNT1 = 0x3210; // cada filtro a su buffer 
C1BUFPNT2 = 0x7654;  // cada filtro a su buffer 
C1BUFPNT3 = 0xFFFF;  // filter 8-11  a cola
C1BUFPNT4 = 0xFFFF;  // filter 12-16 a cola



// dirección base de los bufferes 




// habilitados todos los filtros LP




// mascara empleada para cada filtro
// del 0-7 todo id exacto
// del 7-15 no importa el id, se acepta todo por defecto.


//1. Allocate memory for the CAN message buffer FIFOs.
//2. Place the module into Configuration mode (OPMOD<2:0> = 100).                                                                                       34
//3. Update the CAN FIFO Base Address (CiFIFOBA) register with the base address of the
//   FIFO. This should be the physical start address of Message Buffer 0 of FIFO0.
//4. Update the FIFO control register with the FIFO size (FSIZE<4:0> in CiFIFOCONn).
//5. Select whether the FIFO is to be a transmit or receive FIFO (TXEN bit in CiFIFOCONn).
//6. Place the module into Normal Operation mode (OPMOD<2:0> = 000).


  
if (CAN_DSPIC33_GetOperatingMode(module) != CAN_CONFIGURATION)
	return ERROR;





CANResetChannel(module, 0); // resetea la fifo_0	
xTimeOutCAN_0 = xTaskGetTickCount();	
while (!CANIsChannelReset(module,0))
	{
		if (CAN_Stack_TimeFinished( xTimeOutCAN_0,xTaskGetTickCount(),2))
		return ERROR;
	}

CANAssignMemoryBuffer(module, (void *)CAN_Stack_FifoMessageBuffers,sizeof(CAN_Stack_FifoMessageBuffers));
CANConfigureFilterMask(module, 0, 0x1FFFFFFF, CAN_EID,CAN_FILTER_MASK_ANY_TYPE);
 CANConfigureFilter(module, 1 , 0x00, CAN_EID);
//??CANLinkFilterToChannel(CAN_MODULE module, CAN_FILTER filter, CAN_FILTER_MASK mask, CAN_CHANNEL channel)
CANEnableFilter(module, 1, TRUE);

// Configure FIFO0 
CANConfigureChannelForTx(module,0,(32-1),CAN_TX_RTR_DISABLED,0x03); // 0x03 la prioridad más alta
// Configure FIFO1 
CANConfigureChannelForRx(module, 1, (32-1),FALSE);

return OK;

}




int CAN_Stack_TimeFinished(portTickType prev, portTickType act, int seg)
{
	int aux1,aux2,aux3;

	aux1=(act-prev);
	aux2=configTICK_RATE_HZ;
	aux3=aux1/aux2;
	return (aux3>=seg);
}

int CAN_Stack_Config_Init(CAN_MODULE module)
{

    xTimeOutCAN_0 = xTaskGetTickCount();
    // Place the CAN module in configuration mode. 

    CAN_DSPIC33_SetOperatingMode(module, CAN_CONFIGURATION);

    while(CAN_DSPIC33_GetOperatingMode(module) != CAN_CONFIGURATION)
	{
		if (CAN_Stack_TimeFinished( xTimeOutCAN_0,xTaskGetTickCount(),2))
			return ERROR;
	};
	return OK;
}


int CAN_Stack_Config_Run(CAN_MODULE module,int mode)
{

    xTimeOutCAN_0 = xTaskGetTickCount();	
	// Switch the CAN module off. 
    CAN_DSPIC33_EnableModule(module,TRUE);  
    CAN_DSPIC33_SetOperatingMode(module, 	mode);
    while(CAN_DSPIC33_GetOperatingMode(module) != 	mode)
	{
		if (CAN_Stack_TimeFinished( xTimeOutCAN_0,xTaskGetTickCount(),2))
		return ERROR;
	}



	return OK;
}
*/



/*



int ReceiveMessage(CAN_MODULE module,int cola, int* id,int* length,int *rtr, int *can2b, char * buffer_dst)
{
CANRxMessageBuffer * buffer;

if (CANGetChannelEvent(module, cola)&CAN_RX_CHANNEL_NOT_EMPTY)
// hay mensajes 
{
	int ct;
	buffer =CANGetRxMessage(module,cola);
	
	*length=buffer->msgEID.DLC;
	*rtr=buffer->msgEID.RTR;
	*can2b=buffer->msgEID.IDE;

	for (ct=0;ct<(*length);ct++)
		buffer_dst[ct] = buffer->data[ct]; // Byte 0 Data /


	if (*can2b == 1)
	{	 // extended
		*id=((buffer->msgSID.SID)<<18)|(buffer->msgEID.EID);	
	}
	else
	{
		*id=buffer->msgSID.SID;
	}
	
	CANUpdateChannel(module, cola);
	return OK;
}
else
	return ERROR;

}

//extern void  __attribute__  ((interrupt(ipl7), vector(45))) CAN_FreeRTOS_ISR(void);

void _CANInterrupt(void)
{

   vParTestToggleLED( 0 ); 
//   CANClearUSBInterrupt();

}//end of CANDeviceTasks()




*/
