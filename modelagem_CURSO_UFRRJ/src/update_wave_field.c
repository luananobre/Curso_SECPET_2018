//
//  update_wave_field.c
//  
//
//  Created by Luana Nobre on 03/05/14.
//
//

#include <stdio.h>

void update_wave_field(float *P0, float *P1, int Nxx, int Nzz)
{
    int i, j;
    float p_temp;
    
    for (i=0; i<Nxx; i++)
    {
        for (j=0; j<Nzz; j++)
        {
            p_temp = P0[Nzz*i + j];
            P0[Nzz*i + j] = P1[Nzz*i + j];
            P1[Nzz*i + j] = p_temp;
        }
    }
  
}
