#include <COM_TY.H>
#include <mg_int.h>
#include <math.h>
#include <stdio.h>
#include "mct_io.h"

void Calcula_modulovector(byte * Buffer,struct P_SO dir)
{
        data byte datoaux1;
        data byte datoaux2;
        data byte count;
        data byte dato1;
        data byte dato2;
        data byte dato3;
        data word pos;
        data byte * ptr;
        data byte * ptr1;
        data word dirl;

        ptr=Buffer;

        Change_bank(dir.bank);
        pos=(word)(dir.dir);

        count=0;
        do
        {
            datoaux1=DATAPTR[pos+(word)count];

            if (datoaux1>127)
               datoaux1=datoaux1-128;
            else
               datoaux1=128-datoaux1;
            
            *(ptr++)=datoaux1;
                        
            datoaux2=DATAPTR[pos+(word)count+N_CANTSAMPLES];
            if (datoaux2>127)
               datoaux2=datoaux2-128;
            else
               datoaux2=128-datoaux2;
            *(ptr++)=datoaux2;

        count++;
        }while(count);

        /* calcula el m¢dulo */

        ptr=Buffer;
        ptr1=Buffer;  

        Change_bank(RAICES.bank);
        pos=(word)RAICES.dir;
        count=0;
        do {

         dato1=*(ptr++);
         dato2=*(ptr++);

         if (dato1==0)
            dato3=dato2;
         else
            if (dato2==0)
               dato3=dato1;
            else
               {
               dirl=pos+(word)(dato1-1)*(word)128+(word)(dato2-1);
               dato3=DATAPTR[dirl];
               }

         *(ptr1++)=dato3;
        count++;
/*        printf("dir: %x, d1: %d, d2: %d , r: %d \n", dirl, (int)dato1,(int)dato2,(int)dato3);*/
        }while(count);
   
}

