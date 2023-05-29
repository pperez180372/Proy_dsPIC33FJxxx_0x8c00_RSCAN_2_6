#include <codigos.h>
#include <mes_int.h>
#include "mct_io.h"

void Tratar_peticion(void)
{
	byte comand;
	byte prog;
        byte count;

	prog=mensaje_act.t_mess.m_gen.aux1;

	switch (mensaje_act.t_mess.m_gen.aux)
       {
        case LOAD_PROG:
			if (!Programa_correcto(prog))
			{
                                MCT_st=INVPROGRAM;
                		return;
			}

		        MES_send_information(BEGIN_PROGRAM,mensaje_act.t_mess.m_gen.aux1,0);

			for (count=0;count<N_PASOS;count++)
			{
                                comand=Prop_paso[count].comandos[prog];
				if (comand!=NULL_COMMAND)
				   MES_send_information(PROG_COMMAND,count,comand);
			}
	
			MES_send_information(END_PROGRAM,mensaje_act.t_mess.m_gen.aux1,0);

                        MCT_st=OK;
        		break;

        case STATUS:    
                        MES_send_error(MCT,MCT_st);
                        break;
        default:        MCT_st=COMNOTVALID;
                        break;
       };
    
}

