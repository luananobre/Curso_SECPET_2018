//
//  apply_Reynolds_Boundary.c
//  
//
//  Created by Luana Nobre on 04/05/14.
//
//

#include <stdio.h>
#include "parametros.h"


void apply_Reynolds_Boundary(float *P0, float *P1, float *amp, int Nxx, int Nzz) {
    
    int i;
    int j;
    
    
    for (i=2; i<Nxx-2; i++){
        // Interface superior
        for (j=0; j<2; j++) {
            P1[Nzz*i + j] = P0[Nzz*i + j] + amp[Nzz*i + j]*( P0[Nzz*i + (j+1)] - P0[Nzz*i + j] );
        }
        
        // Interface inferior
        for (j=Nzz-2; j<Nzz; j++) {
            P1[Nzz*i + j] = P0[Nzz*i + j] - amp[Nzz*i + j]*( P0[Nzz*i + j] - P0[Nzz*i + (j-1)] );
        }
    }
    
    for (j=2; j<Nzz-2; j++) {
        // Interface esquerda
        for (i=0; i<2; i++) {
            P1[Nzz*i + j] = P0[Nzz*i + j] + amp[Nzz*i + j]*( P0[Nzz*(i+1) + j] - P0[Nzz*i + j] );
        }
        
        // Interface direita
        for (i=Nxx-2; i<Nxx; i++) {
            P1[Nzz*i + j] = P0[Nzz*i + j] - amp[Nzz*i + j]*( P0[Nzz*i + j] - P0[Nzz*(i-1) + j] );
        }
    }    
}
