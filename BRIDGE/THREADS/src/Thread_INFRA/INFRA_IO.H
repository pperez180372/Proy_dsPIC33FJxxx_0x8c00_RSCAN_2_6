#ifndef __MINF_IO_H__
#define __MINF_IO_H__
#include <tipos.h>

extern unsigned char INFRA_CANAL_ACTUAL;             /* canal que actualmente esta seleccionado */

void INFRA_Activacion(byte estado);
void INFRA_Seleccion_canal(int cont,int hab);
int INFRA_Get_buffer(void);
inline int INFRA_Get_Senyal(byte b,byte canal);
inline int INFRA_Get_Enviroment(byte b,byte canal);
int INFRA_Set_mode(int);

#define INFRA_SENYAL        2
#define INFRA_PROMEDIANDO   1
#define INFRA_OFF           0
    

#endif

