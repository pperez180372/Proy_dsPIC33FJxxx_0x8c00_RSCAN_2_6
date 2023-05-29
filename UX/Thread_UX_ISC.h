/* 
 * File:   Thread_UX_ISC.h
 * Author: Disca
 *
 * Created on 14 de septiembre de 2015, 10:45
 */

#ifndef THREAD_UX_ISC_H
#define	THREAD_UX_ISC_H

#ifdef	__cplusplus
extern "C" {
#endif
int putPosition(unsigned int num_servo,unsigned int pos /* centesimas de grado */ );
unsigned long int getDistance(void);
unsigned int getPosition(unsigned int num_servo); //centesimas de grado 
void vHeadTask( void *pvParameters );

void UX_HEAD_procesa_CAN_BUFF(char * nbuff);
void UX_HEAD_procesa_CAN(int nbuff);

#ifdef	__cplusplus
}
#endif

#endif	/* THREAD_UX_ISC_H */

