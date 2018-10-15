//
//  wave_equation.c
//  
//
//  Created by Luana Nobre on 29/04/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void wave_equation(float *P0, float *P1, int Nxx, int Nzz, float *vel, float *coefic)
{
    int i, j;
    
    for (i=2; i<(Nxx-2); i++){
         for (j=2; j<(Nzz-2); j++){
             
              P1[Nzz*i+j] = coefic[Nzz*i+j]*( P0[Nzz*(i-2)+j] + P0[Nzz*(i+2)+j]+P0[Nzz*i+(j+2)]+P0[Nzz*i+(j-2)]-16*(P0[Nzz*(i-1)+j]+P0[Nzz*(i+1)+j]+P0[Nzz*i+(j-1)]+P0[Nzz*i+(j+1)])+60*P0[Nzz*i+j])+ 2*P0[Nzz*i+j]-P1[Nzz*i+j];            
        }
    }
}
