#ifndef __CAN_CONFIGURACION_H__
#define __CAN_CONFIGURACION_H__

#include "can_scocan.h"
#include "CANTypes.h"


void CAN_DSPIC33_Init_Stack(void);
void CAN_DSPIC33_SetSpeed(CAN_MODULE module, int BPR,int PS,int PS1,int PS2,int SJW,int PHTS,int SAM );
void CAN_DSPIC33_SetOperatingMode(CAN_MODULE module, CAN_OP_MODE opmode);
CAN_OP_MODE CAN_DSPIC33_GetOperatingMode (CAN_MODULE module);
void CAN_DSPIC33_EnableModule(CAN_MODULE module, BOOL enable);
int CAN_DSPIC33_First_Free_Filter_from (CAN_MODULE module,int n);
int CAN_DSPIC33_Filter (CAN_MODULE module,int nbuff,long int id,int n,int num_mask);
int CAN_DSPIC33_Association_FIFO_ID_to_Handle(CAN_MODULE  module,unsigned long int id,PT_HD handle);
int CAN_DSPIC33_Association_Filter_to_Handle(CAN_MODULE module,int nbuff,PT_HD handle);
int CAN_DSPIC33_SetDMA (CAN_MODULE module);
int CAN_DSPIC33_Enable_interrupts_Stack(CAN_MODULE module);
int CAN_DSPIC33_Enable_interrupts_Devices(CAN_MODULE module);
int CAN_DSPIC33_Stack_SetBitRate(CAN_MODULE module, int modBitRate);
int CAN_DSPIC33_Set_TX_BUFFERS (CAN_MODULE module);
#endif
