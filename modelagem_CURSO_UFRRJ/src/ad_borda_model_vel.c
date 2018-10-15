//
//  vel_model.c
//  
//
//  Created by Luana Nobre on 05/05/14.
//
//

#include <stdio.h>
#include <string.h>
#include "parametros.h"
#include <math.h>

void ad_borda_model_vel(float *vel_ini, float *vel, int Nxx, int Nzz) {
    
    int ix, iz, j, i;
    
    for (j=NA; j<(NZ+NA); j++) {
        for (i=NA; i<(NX+NA); i++) {
            vel[Nzz*i + j] = vel_ini[NZ*(i-NA) + (j-NA)];
        }
    }
 
    // Borda superior
    for (ix = NA; ix < (NX+NA); ix++) {
        for (iz = 0; iz < NA; iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*ix + (NA+1)];
        }
    }
    
    // Borda inferior
    for (ix = NA; ix < (NX+NA); ix++) {
        for (iz = (NZ+NA); iz < Nzz; iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*ix + NA+NZ-1];
        }
    }
    
    // Borda lateral esquerda
    for (ix = 0; ix < NA; ix++) {
        for (iz = NA; iz < (NZ+NA); iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*(NA+1) + iz];
        }
    }
    
   // Borda lateral direita
    for (ix = (NA+NX); ix < Nxx; ix++) {
        for (iz = (NA); iz < (NZ+NA); iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*(NX+NA-1) + iz];
        }
    }
    
    // Borda quina superior esquerda
    for (ix = 0; ix < NA; ix++) {
        for (iz = 0; iz < NA; iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*(NA+1) + (NA+1)];
        }
    }
    
    // Borda quina superior direita
    for (ix = (NA+NX); ix < Nxx; ix++) {
        for (iz = 0; iz < NA; iz++) {
           vel[Nzz*ix + iz] = vel[Nzz*(NX+NA-1) + NA];
        }
    }
    
    // Borda quina inferior esquerda
    for (ix = 0; ix < NA; ix++) {
        for (iz = (NZ+NA); iz < Nzz; iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*(NA+1) + (NZ+NA-1)];
        }
    }
    
    // Borda quina inferior direita
    for (ix = (NX+NA); ix < Nxx; ix++) {
        for (iz = (NZ+NA); iz < Nzz; iz++) {
            vel[Nzz*ix + iz] = vel[Nzz*(NX+NA) + (NZ+NA-1)];
        }
    }
   
    
}
