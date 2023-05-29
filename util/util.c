#define _CAN1 //sólo un controlador es necesario para los defines de CAN

#include "FreeRTOS.h"
#include "semphr.h"
#include "can_scocan.h"
#include "CANTypes.h"
#include "Thread_ecan.h"
#include "CAN_DSPIC_33F_Stack.h"

#include "util.h"


int HP_Mesg_Proc_1(void * arg);
int LP_Mesg_Proc(void * arg);

void procesa_pt_WR(int nbuf);
void procesa_pt_RD(int nbuf);

void escribe_led_lp(int value)
{
	// el nivel bajo a cero indica lp
	TRISB=0x2FFF;
	PORTB=((0x4000*(~value))&0xD000);
}


void escribe_led_hp(int value)
{
	
	// el nivel bajo a uno indica HP
	TRISB=0x2FFF;
		PORTB=((0x4000*(~value))&0xD000)+0x1000;
}

void escribe_led(int value)
{
	
	// el nivel bajo a uno indica HP
	TRISB=0x1FFF;
		PORTB=((~value)<<13)&0xE000;
}

int detecta_bit(int r)
{
	int ct;
	int mask;	

	mask=1;
	for (ct=0;ct<16;ct++)
	{
		if (r&mask) return ct;
		mask=mask<<1;
	}
	return -1;
}

void imprime_pos_led(int res)
{
	if (res==-1){PARPADEO_valor_ret(0,7,5);} 
	if ((res<4)&&(res>=0))  {PARPADEO_valor_ret(0,0,4); PARPADEO_valor_ret(0,res&7,4);}  
	if ((res<8)&&(res>=4))  {PARPADEO_valor_ret(0,1,4); PARPADEO_valor_ret(0,res&7,4);}  
	if ((res<12)&&(res>=8)) {PARPADEO_valor_ret(0,2,4); PARPADEO_valor_ret(0,res&7,4);}  
	if ((res<16)&&(res>=12)){PARPADEO_valor_ret(0,3,4); PARPADEO_valor_ret(0,res&7,4);}  		
}


