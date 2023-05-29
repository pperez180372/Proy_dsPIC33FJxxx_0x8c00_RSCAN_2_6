#ifndef __UTIL_H__
#define __UTIL_H__

//definiciones propias

//extern volatile unsigned int  INTCON1 __attribute__((__sfr__));



void escribe_led_lp(int value);
void escribe_led_hp(int value);
void escribe_led_completo(int value);
void escribe_led(int value);

int detecta_bit(int r);
void imprime_pos_led(int res);



/* individualmente no funciona el bit RB14*/
/*#define LED(value) do{\
PORTBbits.RB15=((~value)&0x4)>>2;\
PORTBbits.RB14=((~value)&0x2)>>1;\
PORTBbits.RB13=((~value)&0x1);}\
while(0)
*/
#define LED(value) do{PORTB=(PORTB&0x1FFF)|((~(value))<<13);}while(0);


#define PARPADEO_1(value) {unsigned int c1,c2,res;do{\
res=C1INTF;\
TRISB=TRISB&0x1FFF;PORTB=0x2FFF; for(c1=0;c1<60000;c1++)for(c2=0;c2<20;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0x4FFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<20;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0x8FFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<20;c2++);\
} while(value);\
}

// coche fantastico lento
#define PARPADEO_2(value) {unsigned int c1,c2,c3,res;do{\
res=C1INTF;\
c3=40;\
TRISB=TRISB&0x1FFF;PORTB=0xcFFF; for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*1;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0xAFFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*1;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0x6FFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*1;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0xAFFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*1;c2++);\
} while(value);\
}
// coche fantastico program,able
#define PARPADEO_3(value,vel) {unsigned int c1,c2,c3,res;do{\
res=C1INTF;\
c3=40;\
TRISB=TRISB&0x1FFF;PORTB=0xcFFF; for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*vel;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0xAFFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*vel;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0x6FFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*vel;c2++);\
TRISB=TRISB&0x1FFF;PORTB=0xAFFF;for(c1=0;c1<60000;c1++)for(c2=0;c2<c3*vel;c2++);\
} while(value);\
}

/*parpadeo con valor*/
#define PARPADEO_valor(value,valor) {unsigned int c1,c2,res;do{\
res=C1INTF;\
TRISB=TRISB&0x1FFF;LED(1);for(c1=0;c1<60000;c1++)for(c2=0;c2<10;c2++);\
TRISB=TRISB&0x1FFF;LED(2);for(c1=0;c1<60000;c1++)for(c2=0;c2<10;c2++);\
TRISB=TRISB&0x1FFF;LED(4);for(c1=0;c1<60000;c1++)for(c2=0;c2<10;c2++);\
TRISB=TRISB&0x1FFF;LED((valor));for(c1=0;c1<60000;c1++)for(c2=0;c2<70;c2++);\
} while(value);\
}
#define PARPADEO_valor_ret(value,valor,ret) {unsigned int c1,c2,res;do{\
res=C1INTF;\
TRISB=TRISB&0x1FFF;LED(1);for(c1=0;c1<60000;c1++)for(c2=0;c2<10;c2++);\
TRISB=TRISB&0x1FFF;LED(2);for(c1=0;c1<60000;c1++)for(c2=0;c2<10;c2++);\
TRISB=TRISB&0x1FFF;LED(4);for(c1=0;c1<60000;c1++)for(c2=0;c2<10;c2++);\
TRISB=TRISB&0x1FFF;LED(valor);for(c1=0;c1<60000;c1++)for(c2=0;c2<70*ret;c2++);\
} while(value);\
}




#endif

