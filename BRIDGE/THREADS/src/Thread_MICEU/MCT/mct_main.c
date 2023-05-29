#include <com_ty.h>
#include <mg_int.h>
#include <mes_int.h>
#include <codigos.h>
#include <assert.h>
#include "mct_io.h"

struct PROP Prop_paso[N_PASOS];        /* almacena los datos sobre cada captura */

float temperatura;              /* Mantiene la tempetatura */
word prog_act;                  /* programa actual */
byte MCT_st;                    /* resultado del ultimo comando */

byte ret_status;                /* true si devuelve el estado por
                                   cada comando */
unsigned int MCT_n_muestras;    /* numero de muestras que envia de regreso */

idata struct t_mess_in mensaje_act; /* mensaje en curso */

void MCT_Init(void)
{ 
  
     /*MG_Estado_mem();*/
     Conf_Tabla_ROOTS();                      /* realiza precalculos de modulos de señal */
     /*MG_Estado_mem();*/
     
     /*printf("roots\n");*/
     Inicializar_programas();                   /* borra programas */
/*     printf("ini_prog\n");      */
     
     
     Asignar_buffers();                         /* asigna los buffers para captura */
     Estable_n_muestras(8);                     /* 256 muestras */
     MCT_st=OK;
     prog_act=0;

     Inicializa_sistema_captura();          /* aqui no haria falta controlar los errores de calibrado */

     Conf_ganancia(GANANCIA_DINAMICA,0);  /* Por defecto, funciona con variable dinamica */
     temperatura=27.0;                          /* grados centigrados */
     Conf_vel_sonido(temperatura);           /* para una temperatura fija calcula la velocidad 
                                                del ultrasonido */
     MES_request(MCT,SET_TEMPERATURE);
}

void Inicializar_programas(void)
{
        byte cont;    

        for(cont=0;cont<MAX_PROGRAMAS;cont++)
        {
           mensaje_act.t_mess.m_conf.t_inf.aux=cont;
           Borrar_prog();
        }
}

void Asignar_buffers(void)
{
        int count;
        struct P_SO pdir;

        for(count=0;count<N_PASOS;count++)
        {
                pdir=(Needstring(sizeof(struct ESP_TEMP)));     /* reserva espacio para */
                
                /*printf("%x tamaño: %x  dir: %p Banco: %x\n",count,(word)(sizeof(struct ESP_TEMP)),pdir.dir,pdir.bank);*/
                Prop_paso[count].dir=pdir;
                
        }
}

void MCT_execute(struct t_mess_in m)
{
  byte aux;
  byte * dir;
  mensaje_act=m;

  /*TEST_sistema_captura();                               */

  /*printf("Mn: ");
  dir=(byte *)&m;

  for (aux=0;aux<8;aux++)
  {
     printf("%d:",(int)dir[aux]);
  }
  printf("\n");*/
  
  switch (mensaje_act.tipo)
  {
        case CONFIGURE:   Configurar();
                          break;
        case INSTRUCTION: Programar_orden();
                          break;
        case EXECUTE:     Ejecutar_programa();
                          break;
        case EXECUTEEX:   Ejecutarex_programa();
                          break;                        
        case REQUEST:     Tratar_peticion();
                          break;
        default:          MES_send_error(MCT,MESSNOTVALID);
  }
}
byte MCT_status(void)
{
        return MCT_st;
}

