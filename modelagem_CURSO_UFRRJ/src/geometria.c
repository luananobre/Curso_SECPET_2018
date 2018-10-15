//
//  geometria.c
//  
//
//  Created by Luana Nobre on 29/09/14.
//
//

#include <stdio.h>
#include "parametros.h"
#include <string.h>

void geometria (int xshot, int *coord_rec, int irec, int ishot){
    
    if (GEOMETRY == 0){
        
        // REGISTRO EM TODO MODELO
        coord_rec[NSHOT*irec + ishot] = X0_REC -1 + irec*DX_REC ;
    }

}
