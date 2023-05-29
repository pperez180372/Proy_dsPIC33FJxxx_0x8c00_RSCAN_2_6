#include <com_ty.h>
#include <mes_int.h>
#include <codigos.h>
#include <sbt_int.h>
#include "mct_io.h"

void Programar_orden(void)
{
  byte comando;
   byte pasoini;
  byte pasofin;
  byte step;
        byte count1;

        comando=mensaje_act.t_mess.m_inst.comando;
        pasoini=mensaje_act.t_mess.m_inst.desde;
        pasofin=mensaje_act.t_mess.m_inst.hasta;
        step=mensaje_act.t_mess.m_inst.enpasos;

/*        printf("ORDEN: %d ,INI: %d, FIN: %d, STEP: %d \n",(int)comando,(int)pasoini,(int)pasofin,(int)step);*/

        if ((comando<COMCAP_LOW) || (comando>COMCAP_HIGH))
        {
            MCT_st=INSTNOTVALID;
            return;
        }

        if (pasoini>199)
        {
            MCT_st=INSTNOTVALID;
            return;
        }
        if (pasofin>199)
        {
            MCT_st=INSTNOTVALID;
            return;
        }
        
        if (pasoini>pasofin)
        {
            MCT_st=INSTNOTVALID;
            return;
        }
        
        for (count1=pasoini;count1<=pasofin;count1=count1+step)
        {
            Prop_paso[count1].comandos[prog_act]=comando;
        };

        MCT_st=OK;
        return;
}

void Ejecutar_programa(void)
{
        byte count,suma;
        byte num_prog;

        printf("Ejecutando programa\n");
        num_prog=mensaje_act.t_mess.m_gen.aux;
        if (!Programa_correcto(num_prog))
        {
                MCT_st=INVPROGRAM;
                return;
        }

        suma=0;
        for (count=0;count<N_PASOS;count++)
         if (Prop_paso[count].comandos[num_prog]!=NULL_COMMAND)
            suma=suma+1;

        MES_send_information(BEGIN_PROGRAM,num_prog,suma);

        for (count=0;count<N_PASOS;count++)
            ExecuteCommand(count,num_prog);

        MES_send_information(END_PROGRAM,num_prog,suma);

        MCT_st=OK;
        return;
}

void Ejecutarex_programa(void)
{
        byte count,suma;
        byte num_prog,linea_inicio,sentido;

        num_prog=mensaje_act.t_mess.m_gen.aux;
        linea_inicio=mensaje_act.t_mess.m_gen.aux1;
        sentido=mensaje_act.t_mess.m_gen.aux2;
        
        if (!Programa_correcto(num_prog))
        {
                MCT_st=INVPROGRAM;
                return;
        }
        
        if (sentido>1)
        {
              MCT_st=INSTNOTVALID;
              return;
        }
        
        if (linea_inicio>199)
        {
              MCT_st=INSTNOTVALID;
              return;       
        }
        
        suma=0;
        for (count=0;count<N_PASOS;count++)
         if (Prop_paso[count].comandos[num_prog]!=NULL_COMMAND)
            suma=suma+1;
        
         
        MES_send_information(BEGIN_PROGRAM,num_prog,suma);

        count=linea_inicio;
        if (sentido)
        {   
        
          do
          {
            ExecuteCommand(count,num_prog);
            count=count-1;
            if (count==255) count=199;        
          }
          while (count!=linea_inicio);
        }
        else
        {
          do
          {
            ExecuteCommand(count,num_prog);
            count=count+1;
            if (count==200) count=0;        
          }
          while (count!=linea_inicio);
        }
        MES_send_information(END_PROGRAM,num_prog,0);

        MCT_st=OK;
        return;
}



void Realizar_captura(byte count,byte num_prog)
{
        byte banco;
        byte * dir;

        
        banco=Prop_paso[count].dir.bank;
        dir=Prop_paso[count].dir.dir;
        Prop_paso[count].tiempo=Current_time();
 
        Capturar(count,banco,dir,&Prop_paso[count].ganancia);
 /*       printf("banco %d dir: %p \n",(word)banco,dir);*/
}



void ExecuteCommand(byte count,byte num_prog)
{
/*    MES_send_information(PROG_COMMAND,count,Prop_paso[count].comandos[num_prog]);*/
    switch (Prop_paso[count].comandos[num_prog])
        {                      
        case STORE:                     Realizar_captura(count,num_prog);
                                        break;
        case LOAD_DISTANCE:             Devuelve_DISTANCIA(count);
                                        break;
        case STORELOAD_DISTANCE:        Realizar_captura(count,num_prog);
                                        Devuelve_DISTANCIA(count);
                                        break;      
        case LOAD_ECHO:                 Devuelve_ECO(count);
                                        break;
        case STORELOAD_ECHO:            
                                        Realizar_captura(count,num_prog);
                                        Devuelve_ECO(count);
                                        break;      
        case LOAD_PHASE:                Devuelve_CANAL(count,PHASE);
                                        break;
        case STORELOAD_PHASE:           Realizar_captura(count,num_prog);
                                        Devuelve_CANAL(count,PHASE);
                                        break;      
        case LOAD_QUAD:                 Devuelve_CANAL(count,QUADRATURE);
                                        break;
        case STORELOAD_QUAD:
                                        Realizar_captura(count,num_prog);
                                        Devuelve_CANAL(count,QUADRATURE);
                                        break;
        case LOAD_TEST:                 Devuelve_TEST(count);
                                        break;
        case STORELOAD_TEST:
                                        Realizar_captura(count,num_prog);
                                        Devuelve_TEST(count);
                                        break;      
        case NULL_COMMAND:
                                        break;
        default:                        break;
        }
}

       
