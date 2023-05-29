#include <com_ty.h>
#include <codigos.h>
#include <MES_int.h>
#include <MCT_int.h>
#include <sbor_int.h>

#include "MCT_IO.h"

void Configurar(void)
{
 
   switch (mensaje_act.t_mess.m_conf.comando)
  {
         case RESET_MAQ:        MCT_Init();                          
                                break;
         case RESET_PROG:       Borrar_prog();
                                break;
         case DECLARE_PROG:     Declare_prog();
                                break;
         case VISIBLE_CHECK:    MCT_st=TEST_sistema_captura();                               
                                break;
         case GANANCIA_DIN:     MCT_st=Conf_ganancia(GANANCIA_DINAMICA,0);
                                break;
         case GANANCIA_PAS:     MCT_st=Conf_ganancia(GANANCIA_PASIVA,mensaje_act.t_mess.m_conf.t_inf.aux);
                                break;
         case SET_TEMPERATURE:  Conf_vel_sonido(mensaje_act.t_mess.m_conf.t_inf.temperatura);
                                break;                                     
         case SET_SAMPLES:      Estable_n_muestras(mensaje_act.t_mess.m_conf.t_inf.aux);
                                break;
         case RECALIBRATE:      MCT_st=Ir_a_posicion_absoluta(mensaje_act.t_mess.m_conf.t_inf.aux);
                                break;

         default:               MCT_st=COMNOTVALID;
  }
}


void Estable_n_muestras(byte n_muestras)
{
  if ((n_muestras>0) && (n_muestras<=8)) /* n_muestras en potencias de 2 */
  {
    MCT_n_muestras=((int)1)<<n_muestras; 
    SBOR_Establece_n_muestras((int)MCT_n_muestras);
    MCT_st=OK;
  } 
  else
    MCT_st=INVSAMPLES;
}


byte Programa_correcto(byte num)
{
        if (num<MAX_PROGRAMAS)
                return TRUE;
        else
                return FALSE;
}

byte Programa_vacio(byte num_prog)
{
        byte cont;

        if (!Programa_correcto(num_prog)) /* dara como vacio */
              return TRUE;

        for(cont=0;cont<N_PASOS;cont++)
           if (Prop_paso[cont].comandos[num_prog]!=NULL_COMMAND)
              return (FALSE);

        return(TRUE);
}


void Borrar_prog(void)
{
        byte cont;

        if (!Programa_correcto(mensaje_act.t_mess.m_conf.t_inf.aux))
        {
            MCT_st=INVPROGRAM;
            return;
        }

        for(cont=0;cont<N_PASOS;cont++)
           Prop_paso[cont].comandos[mensaje_act.t_mess.m_conf.t_inf.aux]=NULL_COMMAND;
  
}

void Declare_prog(void)
{
     if (!Programa_vacio(mensaje_act.t_mess.m_conf.t_inf.aux))
         MCT_st=PROGREDEFINED;
     else
     {
         Borrar_prog();
         if (MCT_st==OK)
            prog_act=mensaje_act.t_mess.m_conf.t_inf.aux;
     }
}
