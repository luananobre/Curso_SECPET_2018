//
//  apply_Cerjan_Boundary.c
//  
//
//  Created by Luana Nobre on 04/05/14.
//
//

#include <stdio.h>
#include <math.h>
#include "parametros.h"


void apply_Cerjan_Boundary(float *P0, float *P1, const int Nxx, const int Nzz, float *coef_dampz_left, float *coef_dampz_right, float *coef_dampz_inf, float *coef_dampz_sup){
    
    int i, j;
    const float fat = 0.0025;

    for (i=2; i<Nxx-2; i++) {
        // Borda superior
        if (NA != 0){
			for (j = 0; j<NA; j++){
				P0[Nzz*i + j] = coef_dampz_sup[Nzz*i + j] * P0[Nzz*i + j];
				P1[Nzz*i + j] = coef_dampz_sup[Nzz*i + j] * P1[Nzz*i + j];
			}
		}

        // Borda inferior
        if (NA != 0){
			for (j =  Nzz-NA; j<Nzz; j++) {
				P0[Nzz*i + j] = coef_dampz_inf[Nzz*i + j] * P0[Nzz*i + j];
				P1[Nzz*i + j] = coef_dampz_inf[Nzz*i + j] * P1[Nzz*i + j];
			}
        }
    }
    
    
	if (NA != 0){
        // Borda lateral esquerda
		for (i = 0; i<NA; i++) {
            for (j = 2; j < Nzz-2; j++) {
				P0[Nzz*i + j] = coef_dampz_left[Nzz*i + j] * P0[Nzz*i + j];
				P1[Nzz*i + j] = coef_dampz_left[Nzz*i + j] * P1[Nzz*i + j];
			}
		}
        // Borda lateral direita
        for (i = Nxx-NA; i<Nxx; i++) {
            for (j = 2; j < Nzz-2; j++) {
                P0[Nzz*i + j] = coef_dampz_right[Nzz*i + j] * P0[Nzz*i + j];
                P1[Nzz*i + j] = coef_dampz_right[Nzz*i + j] * P1[Nzz*i + j];
            }
        }
    }
}
