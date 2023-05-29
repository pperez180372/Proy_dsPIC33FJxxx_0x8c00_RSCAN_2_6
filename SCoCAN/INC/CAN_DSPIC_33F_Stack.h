#ifndef __CAN_STACK_H__
#define __CAN_STACK_H__

#include "can_scocan.h"
#include "CANTypes.h"

#define ERROR 	-1
#define OK		 1


/* bit rates */
#define BR_1Mbit	1
#define BR_100kbits	2
#define BR_500kbits	3
#define BR_10kbits	4
#define BR_125kbits	5
#define BR_20kbits	6
#define BR_250kbits	7


#define MAX_MESSAGES_FUNC 16
#define MAX_MESSAGES_FUNC_FIFO 16    // funciones asociadas a identificadores de baja prioridad

#define FIRST_LP_BUFFER 16
	// TX buffer de 0-7
	// RX buffer de 8-31
	// RX buffer 8-15 HP filter de 0-7 asociados a buffer 8-15 manejados por una thread HP
	// RX buffer 16-31 LP 
	// 8-14 LP con filtro fijo a queue manejados por un thread LP
	// 15 con mascara variable 


typedef int (*PT_HD)(void *);
extern PT_HD id_func_handlers[CAN_NUM_OF_MODULES][MAX_MESSAGES_FUNC];

extern unsigned int id_variables[CAN_NUM_OF_MODULES][MAX_MESSAGES_FUNC_FIFO];
extern PT_HD id_variables_ptfunc[CAN_NUM_OF_MODULES][MAX_MESSAGES_FUNC_FIFO];
extern PT_HD id_default_ptfunc[CAN_NUM_OF_MODULES];



extern CAN_DSPIC_33F_RX_TX_MESSAGE ECAN_DMA_AREA[32] __attribute__((space(dma)));





int CAN_DSPIC_33F_SetupMessage(CAN_MODULE module,int n_buff,int id,int length,int rtr, char * buffer_or);
int CAN_DSPIC_33F_SendMessage(CAN_MODULE module,int n_buff);
int CAN_DSPIC_33F_SetupMessage_sort(CAN_MODULE module,int n_buff,int length, char * buffer_or);
int CAN_DSPIC_33F_Init(CAN_MODULE module,int kbits);

int CAN_DSPIC_33F_TX_BUFF_free(CAN_MODULE module,int ct);

// recogida de datos en fifo
int CAN_DSPIC_33F_Get_Message_ID_in_FIFO(CAN_MODULE module,int pb);
int CAN_DSPIC_33F_Get_Message_DLC_in_FIFO(CAN_MODULE module,int pb);
int CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN_MODULE module,int pb,int pos);


int CAN_DSPIC_33F_get_first_buffer_busy_in_FIFO(CAN_MODULE module);
int CAN_DSPIC_33F_get_first_buffer_free_in_FIFO(CAN_MODULE module);
int CAN_DSPIC_33F_Release_buffer_in_FIFO(CAN_MODULE module, int n_buff);

int hit_MSG(CAN_MODULE module, int n_buff);
inline int IN_FAST_hit_MSG(CAN_MODULE module, int mask);



// CONFIGURATION

void CAN_DSPIC33_Init_Stack(void);

void CAN_DSPIC33_SetSpeed(CAN_MODULE module, int BPR,int PS,int PS1,int PS2,int SJW,int PHTS,int SAM );
void CAN_DSPIC33_SetOperatingMode(CAN_MODULE module, CAN_OP_MODE opmode);
CAN_OP_MODE CAN_DSPIC33_GetOperatingMode (CAN_MODULE module);
void CAN_DSPIC33_EnableModule(CAN_MODULE module, BOOL enable);
int CAN_DSPIC33_First_Free_Filter_from (CAN_MODULE module,int n);
int CAN_DSPIC_33F_SetupMessage_firstfree(CAN_MODULE module,int id,int length,int rtr, char * buffer_or);

int CAN_DSPIC33_Filter (CAN_MODULE module,int nbuff,long int id,int n,int num_mask);
int CAN_DSPIC33_Association_Filter_to_Handle(CAN_MODULE module,int nbuff,PT_HD handle);
int CAN_DSPIC33_Association_FIFO_Default_to_Handle(CAN_MODULE  module,PT_HD handle);

int CAN_DSPIC33_SetDMA (CAN_MODULE module);
int CAN_DSPIC33_Enable_interrupts_Stack(CAN_MODULE module);
int CAN_DSPIC33_Stack_SetBitRate(CAN_MODULE module,int modBitRate);
int CAN_DSPIC33_Set_TX_BUFFERS (CAN_MODULE module);


unsigned char CAN_DSPIC_33F_Get_char_of_Message_buffer(CAN_MODULE module,int n_buff,int num);

void CAN_DSPIC_33F_Get_data_of_Message_buffer(CAN_MODULE module,int n_buff,int numini,int numfin,char * pt);



#endif
