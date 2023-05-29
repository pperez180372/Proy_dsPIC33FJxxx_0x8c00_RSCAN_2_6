#include <com_ty.h>
#include <mes_int.h>
#include <mg_int.h>
#include <sbor_int.h>
#include <math.h>
#include <codigos.h>
#include "mct_io.h"



static word velocidad_sonido;    /* velocidad en milimetros/decima de sg */

word ROOTS[200];
struct P_SO RAICES;
static byte V_ECO[N_CANTSAMPLES*2];

void Conf_Tabla_ROOTS(void)
{
   data word count;
   data word count1;
   data word dir,dirbase;

   for (count=0;count<200;count++)
     ROOTS[count]=(word)count*(word)count;

   /*MG_Estado_mem();*/
   RAICES=Needstring(16500);     /* reserva espacio para */
/*   MG_Estado_mem();*/
   
   Change_bank(RAICES.bank);
   dirbase=(word)RAICES.dir;

   for (count=1;count<=128;count++)
     for (count1=1;count1<=128;count1++)
      {
           dir=dirbase+(count-1)*(word)128+(count1-1);
           DATAPTR[dir]=Raiz(count*count+count1*count1);
/*           printf("dir: %x , p1: %d  ",dir,count);
           printf("p2: %d , r: %d  \n",count1,(int)(DATAPTR[dir]));*/
      };
}

void Conf_vel_sonido(float temperatura)
{
        velocidad_sonido=(dword)((167.2+0.6*(temperatura+263.0)*1000.0/10.0));
}

word Calculo_distancia(void)
{
    data byte der1,der0;
    data byte count;
    data byte salir;
    data byte pr,finpr;
    data byte maximos,min,posmin,valmax;
    data float valmaxreal;
    data float posfinal1;
    data float vuelo;
    word distancia;

    salir=FALSE;
    der1=V_ECO[20]>V_ECO[21];
    count=21;
    maximos=0;

    do
    {
      /* modulo y suavizado del vector aqui solo hasta el punto del primer eco */
   
       der0=der1;
       der1=V_ECO[count]>V_ECO[count+1];
       if ((der0==0) && (der1==1))
       { 
           if (V_ECO[count+1]>15)  /* maximo v lido */
           {
              salir=TRUE;
              maximos=count+1;
           }   
       }
       if (count==255) salir=TRUE;
       count++;
   }
   while(!salir);
   
   if (maximos!=0)
   {
/*      printf("He encontrado un máximo en %d \n",(word)maximos);*/
      pr=maximos-7;      /* [pr,finpr] intervalo para obtener el valor mínimo antes del eco */
      finpr=maximos-3; 
      

/*      printf("[%d,%d]\n",(word)pr,finpr);*/
      
      posmin=pr;
      min=V_ECO[pr];
           
      do
      {
        if (V_ECO[pr]<min)
           {
              min=V_ECO[pr];
              posmin=pr;
           }
        pr++;
        /*printf("pr:%d\n",(word)pr);*/
      }
      while (pr<=finpr);

      /*printf("He encontrado minimo relativo %d \n",(word)posmin);*/
            
      valmax=V_ECO[maximos]/2;
      
/*      printf("valor medio %d \n",(word)valmax);           */
      valmaxreal=((float)V_ECO[maximos])/2.0;
      
      pr=maximos;
      min=maximos-7;
      do
      {
          pr--;
      }
      while ((V_ECO[pr]>=valmax) && (min<=pr));
      
/*    printf("Valor medio\n");       */
      posfinal1=(float)pr+(valmaxreal-(float)V_ECO[pr])/(float)(V_ECO[pr+1]-V_ECO[pr]);
      /* parche total */

      if (posfinal1>(float)(pr+1))
        posfinal1=maximos-2;
      else
        if (posfinal1<(float)(pr))
          posfinal1=maximos-2;
      

   }
   else
   {
      posfinal1=(float)255.0;
   }
       
   vuelo=(((float)posfinal1)+6.8)*95.625; /* en microsegundos */
   vuelo=(vuelo-441.0-25.0-13.0)/1000000.0;

   distancia=((float)346000.0*vuelo/2.0);
   /*printf("Distancia: %x\n",distancia);*/
   return distancia;
   
}

void Devuelve_DISTANCIA(byte count)
{
        struct t_cab_signal cabecera;
        word distancia;

        cabecera.tipo_senal=DISTANCE;
        cabecera.tiempo=Prop_paso[count].tiempo;
        cabecera.paso=count;
        cabecera.ganancia=0; /* no aplicable */
        cabecera.longitud=sizeof(word); /* 1 dato */

        Calcula_modulovector(V_ECO,Prop_paso[count].dir);      
        distancia=Calculo_distancia();

        cabecera.dir.dir=(byte *)&distancia;
        cabecera.dir.bank=0;

        MES_send_signal(&cabecera);
        
}

void Muestra_vector(void)
{
        data word dirbase,count,count1,dir;

        Change_bank(RAICES.bank);
        dirbase=(word)RAICES.dir;
       
       for (count=1;count<=1;count++)
       for (count1=1;count1<=20;count1++)
       {
            dir=dirbase+(count-1)*(word)128+(count1-1);
            printf("dir: %x , p1: %d  ",dir,count);
            printf("p2: %d , r: %d  \n",count1,(int)(DATAPTR[dir]));
       };
}


void Devuelve_ECO(byte count)
{
        
        struct t_cab_signal cabecera;

        cabecera.tipo_senal=ECHO;
        cabecera.tiempo=Prop_paso[count].tiempo;
        cabecera.paso=count;
        cabecera.ganancia=Prop_paso[count].ganancia; 
        cabecera.longitud=N_CANTSAMPLES;
        cabecera.dir.dir=(byte *)V_ECO;
        cabecera.dir.bank=0;

        Calcula_modulovector(V_ECO,Prop_paso[count].dir);
        MES_send_signal(&cabecera);       
}

void Devuelve_CANAL(byte count,byte canal)
{
        struct t_cab_signal cabecera;

        cabecera.tipo_senal=canal;
        cabecera.tiempo=Prop_paso[count].tiempo;
        cabecera.paso=count;
        cabecera.ganancia=Prop_paso[count].ganancia; 
        cabecera.longitud=N_CANTSAMPLES;        

        Change_bank(Prop_paso[count].dir.bank);

        switch (canal)
        {

            case PHASE:
                              cabecera.dir=Prop_paso[count].dir;
                              MES_send_signal(&cabecera);
                              break;
            case QUADRATURE:
 
                              cabecera.dir=Prop_paso[count].dir;
                              cabecera.dir.dir=((byte *)Prop_paso[count].dir.dir)+N_CANTSAMPLES;
                              MES_send_signal(&cabecera);
                              break;
        }
}

void Devuelve_TEST(byte count)
{
            
        struct t_cab_signal cabecera;

        
        cabecera.tipo_senal=TEST;
        cabecera.tiempo=Prop_paso[count].tiempo;
        cabecera.paso=count;
        cabecera.ganancia=Prop_paso[count].ganancia; 
        cabecera.longitud=N_CANTSAMPLES*2;
        cabecera.dir=Prop_paso[count].dir;

        Change_bank(Prop_paso[count].dir.bank);

        MES_send_signal(&cabecera);      

}

