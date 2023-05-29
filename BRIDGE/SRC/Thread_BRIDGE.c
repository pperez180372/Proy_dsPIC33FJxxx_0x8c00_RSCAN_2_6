// recursos:
// Convertidor A/D 
// timer 3 dispara 

 
#include "Thread_BRIDGE.h"
#include "Thread_UX_ISC.h"



#define _CAN1 //sólo un controlador es necesario para los defines de CAN

#include "FreeRTOS.h"
#include "semphr.h"
#include "can_scocan.h"
#include "CANTypes.h"

#include "CAN_DSPIC_33F_Stack.h"
#include "CAN_DSPIC_33F_Stack_Overflow.h"

#include "CAN_DSPIC_33F_Configuracion.h"
#include "util.h"
#include "handlers_can.h"

#include "message_id.h"

// Comunicaciones 

int INFRA_Buffer[16];
int INFRA_Buffer_sin_emision[16];


unsigned char Serial_MSG_buf[11*2]; // en hex
int SerialMSG_pos=0; // posicion
int SerialMSG_rev=0; // receiving


unsigned char  BRIDGE_CAN_Buffer[8];


void byte2hex(unsigned char d,char * buf);   /*prepara los caracteres del fichero para su envio*/




void BRIDGE_Init_CAN()
{
	// recepción //fijo

	//CAN_DSPIC33_Filter (CAN1,BRIDGE_BUFFER_CAN_IN,0x00,BRIDGE_FILTRO_CAN_IN,0); // filtro 0, mask exacto a buzon
	//CAN_DSPIC33_Association_Filter_to_Handle(CAN1,BRIDGE_BUFFER_CAN_IN,(PT_HD )BRIDGE_procesa_CAN);
    
    // recepción todos los id a fifo 

    CAN_DSPIC33_Filter (CAN1,15,0x00,BRIDGE_FILTRO_CAN_IN,1); // filtro 1, se acepta todo
	CAN_DSPIC33_Association_FIFO_Default_to_Handle(CAN1,(PT_HD )BRIDGE_procesa_CAN);
        
       

    // transmisión
    
	CAN_DSPIC_33F_SetupMessage(CAN1,BRIDGE_BUFFER_CAN,0x00,8,0, (char *)BRIDGE_CAN_Buffer);

}

void BRIDGE_procesa_CAN(int nbuff)
{
    int t;
    char buf[2];
    unsigned long int id;
    int len;
    
    
    id=CAN_DSPIC_33F_Get_Message_ID_in_FIFO(CAN1,nbuff);
	
    // hardcoded bypass to UX
    //if (id==CANID_UX_HEAD) UX_HEAD_procesa_CAN(nbuff);   
    
    
    
	xSerialPutChar(  0, '>' , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, 'R' , BRIDGE_MAIN_TASK);
    
	byte2hex((id&0xff00)>>8,buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , BRIDGE_MAIN_TASK);
    byte2hex((id&0xff),buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , BRIDGE_MAIN_TASK);
    
    len=CAN_DSPIC_33F_Get_Message_DLC_in_FIFO(CAN1,nbuff);
    //printf("Long %x \n",len);
    byte2hex(len,buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , BRIDGE_MAIN_TASK);
    
    for (t=0;t<len;t++)
    {
    byte2hex((unsigned char)CAN_DSPIC_33F_Get_Message_DATA_in_FIFO(CAN1,nbuff,t),buf);   /*prepara los caracteres del fichero para su envio*/
    xSerialPutChar(  0, buf[0] , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, buf[1] , BRIDGE_MAIN_TASK);  
    }
    xSerialPutChar(  0, '<' , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, '\r' , BRIDGE_MAIN_TASK);
    xSerialPutChar(  0, '\n' , BRIDGE_MAIN_TASK);
    
}




void LEDINIT(void)
 {
     
    // para placa ISC
    // prueba placa ISC con el puente serie while(1){
        TRISAbits.TRISA7=0;  //bit 0;
        TRISAbits.TRISA8=0; //bit 1

       // primero programar el pic18f25k50 y despues el pic para poder reprogramar el pic18f25jk50 borrar el dspic
                
        // esta compartida con el iscp del pic18f25k50 ojo
        TRISAbits.TRISA9=0; //bit 2
        TRISAbits.TRISA10=0; //bit 3

        
 }
 void LED1(int st){ PORTAbits.RA7=st;}
 void LED2(int st){ PORTAbits.RA8=st;}
 void LED3(int st){ PORTAbits.RA9=st;}
 void LED4(int st){ PORTAbits.RA10=st;}
 void LEDA(int st){ 
                    PORTAbits.RA7=st&0x01;
                    st=st>>1;
                    PORTAbits.RA8=st&0x01;
                    st=st>>1;
                    PORTAbits.RA9=st&0x01;
                    st=st>>1;
                    PORTAbits.RA10=st&0x01;
                  }




void BRIDGE_vMAIN_Task_TX(void *pvParameters )
{
	//portBASE_TYPE res_sem;
	int c;
	int fase;


    

        char car;
        int res;
       
        int fd=0;
    
    
	// Used to wake the task at the correct frequency. 
	portTickType xLastExecutionTime;
    c=0;
	fase=0;
    
    
    LEDINIT();
    
	
    BRIDGE_Init_CAN();
    
    
	xLastExecutionTime = xTaskGetTickCount();
  	 
	fase=0;

	for( ;; )
	{	
        
		
		switch (fase)
		{

			case 0: // la fase 0 se desperdicia
				
                    SerialMSG_rev=0; // receiving
                    fase=1;
					break;
					
			case 1: 
                
                       res=xSerialGetChar( fd, &car, BRIDGE_MAIN_TASK/30); // 100ms
                       
                       
                       if (res>0){
                       
                           xSerialPutChar(  fd, car   , BRIDGE_MAIN_TASK);	
                           if ((c%2)==0)
                               LED1(0);
                           else
                                LED1(1);
                        }
                        else
                              break;
                       
                       SCoCAN_Reinit_FSM(car);
                       
                       
                       if (car=='>')
                       {                           
                           xSerialPutChar(  fd, 'A'   , BRIDGE_MAIN_TASK);
                           SerialMSG_pos=0; // posicion
                           SerialMSG_rev=1; // receiving                                                    
                           
                       }
                       else
                       {
                           if (SerialMSG_rev==1)
                           {
                               
                               if (car=='<')
                               {
                                   fase=2;
                                   continue;
                               }
                               else
                               if (hex(0,car)>15)
                               {
                                  fase=0;
                                  continue;
                               }
                               else
                               {   // recibido correctamente
                                   if (SerialMSG_pos==Serial_MSG_MAXBUFFER)
                                   {
                                       fase=0;
                                       continue;
                                   }
                                   
                                   else 
                                       Serial_MSG_buf[SerialMSG_pos++]=car; // en hex
                               }
                           }
                           else
                           ;//    xSerialPutChar(  fd, car   , BRIDGE_MAIN_TASK);
                       }
                      
                       break;
                       
            case 2:    // ha recibido todo el mensaje, se analiza y se transmite si es correcto
                        if (SerialMSG_pos<6) // error al menos debe tener id + length (0))                
                        {
                            fase=1;
                            continue;
                        }
                        res=BRIDGE_Analysis_Serial_MSG();
                        if (res==0)
                        {
                            
                            fase=3;
                            continue;
                        }
                        else
                        {
                            fase=0;
                            continue;
                        }
                        break;
                
            case 3: // envio de mensaje
                       	
                        xSerialPutChar(  fd, 'T'   , BRIDGE_MAIN_TASK);                          
                        xSerialPutChar(  fd, '\r'   , BRIDGE_MAIN_TASK);                          
                        xSerialPutChar(  fd, '\n'   , BRIDGE_MAIN_TASK);                          
                        
                        CAN_DSPIC_33F_SendMessage(CAN1,BRIDGE_BUFFER_CAN);
                        LED4(1);
                        fase=0;
                        break;
		}

										
		//vTaskDelayUntil( &xLastExecutionTime, mainCHECK_TASK_PERIOD/30 );
        
		
		c++;	
		
	}
}




int num_canal;
	


volatile int valuedddd;


unsigned char hex(int x,int y)   /*prepara los caracteres del fichero para su envio*/
{          /* cada par de caracteres leidos corresponderan a un dato a enviar */
 int z;

if (x>'9') x=x&0xdf;
if (y>'9') y=y&0xdf;

 switch (x){
 case 48: x=0;break;
 case 49: x=1;break;
 case 50: x=2;break;
 case 51: x=3;break;
 case 52: x=4;break;
 case 53: x=5;break;
 case 54: x=6;break;
 case 55: x=7;break;
 case 56: x=8;break;
 case 57: x=9;break;
 case 65: x=10;break;
 case 66: x=11;break;
 case 67: x=12;break;
 case 68: x=13;break;
 case 69: x=14;break;
 case 70: x=15;break;
 }
 switch (y){
 case 48: y=0;break;
 case 49: y=1;break;
 case 50: y=2;break;
 case 51: y=3;break;
 case 52: y=4;break;
 case 53: y=5;break;
 case 54: y=6;break;
 case 55: y=7;break;
 case 56: y=8;break;
 case 57: y=9;break;
 case 65: y=10;break;
 case 66: y=11;break;
 case 67: y=12;break;
 case 68: y=13;break;
 case 69: y=14;break;
 case 70: y=15;break;
 }
 z=x*16+y;
 return (z);
}

void byte2hex(unsigned char d,char * buf)   /*prepara los caracteres del fichero para su envio*/
{          /* cada par de caracteres leidos corresponderan a un dato a enviar */
    
    int t;
    for (t=0;t<2;t++)
    {
        unsigned int au;
        char a;
        au=(d&0xf0)>>4;
        if (au>9)
            a=65+(au-10);
        else
            a=48+au;
        *buf=a;
        buf++;
        d=d<<4;
    }
        

}



unsigned int getID()
{
    unsigned int hi,lo;
    
    hi=hex(Serial_MSG_buf[0],Serial_MSG_buf[1]);
    lo=hex(Serial_MSG_buf[2],Serial_MSG_buf[3]);
    
    return (hi*256+lo);
    
}

unsigned int getlength()
{
    return (hex(Serial_MSG_buf[4],Serial_MSG_buf[5]))&0x0f;
}


int BRIDGE_Analysis_Serial_MSG(void)
{
	unsigned int lm;
    unsigned int id;
    unsigned char l;
    
    lm=getlength();
    if (lm>8) return -1;
    id=getID();
    // mensaje relleno
    //printf("---> %x %x ",id,lm);
    
    for (l=0;l<lm;l++)
        BRIDGE_CAN_Buffer[l]=hex(Serial_MSG_buf[6+l*2],Serial_MSG_buf[7+l*2]);
    
    // direccion y longitud
    CAN_DSPIC_33F_SetupMessage(CAN1,BRIDGE_BUFFER_CAN,id,lm,0, (char *)BRIDGE_CAN_Buffer);
    
    // hardcoded
    if (id==CANID_UX_HEAD) UX_HEAD_procesa_CAN_BUFF(BRIDGE_CAN_Buffer);   // llega por serie y lo procesa como si fuese por CAN.  
    
    
    return 0;
}