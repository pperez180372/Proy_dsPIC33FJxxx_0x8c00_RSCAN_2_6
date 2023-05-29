#include <COM_TY.H>
#include "mct_io.h"

byte Raiz(data word N)
{
   data byte A1,A2;
   data word D1,D2,D3;
   data word R1,R2,R3;

   if (!N) return 1;

   A2=(N/200)+2;
   do
   {        A1=A2;
            A2=(N/A1+A1)>>1;
   } while (!((A1==A2) || ((byte)(A1-A2)==(byte)1) || ((byte)(A2-A1)==(byte)1)));

   R1=ROOTS[A1-1];
   R2=ROOTS[A1];

   if (N>R1)
      D1=N-R1;
   else
      D1=R1-N;

   if (N>R2)
      D2=N-R2;
   else
      D2=R2-N;

   if (D1>D2)
   {     
      R3=ROOTS[A1+1];
      if (N>R3)
         D3=N-R3;
      else
         D3=R3-N;
      if (D2>D3)
         return A1+1;
      else
         return A1;
   }
   else
     return A1-1;
}
