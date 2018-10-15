//
//  coef_damping_zones.c
//
//
//  Created by Luana Nobre on 11/05/14.
//
//

#include <math.h>
#include <stdio.h>
#include "parametros.h"


void calc_coef_damping_zones(int Nxx, int Nzz, float *coef_dampz_left, float *coef_dampz_right, float *coef_dampz_inf, float *coef_dampz_sup) {

    int i, j;
    const float fat = 0.0010;

    for (i=0; i<Nxx; i++) 
    {
        // Borda superior
        if (NA != 0)
        {
                for (j = 0; j<NA; j++) 
                {
                    coef_dampz_sup[Nzz*i + j] = exp(-pow(fat*(NA - j), 2));
                }
        }

        // Borda inferior
        if (NA != 0)
        {
                for (j = Nzz-NA; j<Nzz; j++)
                {
                        coef_dampz_inf[Nzz*i + j] = exp(-pow(fat*(Nzz-NA - j), 2));
                }
        }
    }

    if (NA != 0)
    {
        // Borda lateral esquerda
        for (i = 0; i<NA+1; i++)
        {
            for (j = 0; j < Nzz; j++) 
            {
                coef_dampz_left[Nzz*i + j] = exp(-pow(fat*(NA - i), 2));
            }
        }
        // Borda lateral direita
        for (i = Nxx-NA; i<Nxx; i++)
        {
            for (j = 0; j < Nzz; j++) 
            {
                coef_dampz_right[Nzz*i + j] = exp(-pow(fat*(Nxx-NA - i), 2));
            }
        }
    }

}
