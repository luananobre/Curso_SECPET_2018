//
//  ricker_wavelet.c
//  
//
//  Created by Luana Nobre on 29/04/14.
//
//
#include <stdio.h>
#include <math.h>
#include "parametros.h"

void ricker_wavelet(float *fonte, int Nf)
{
    float fc;
    float td;
    int time_step;
   
            
    fc = FCORTE/(3*sqrt(M_PI));
    
    for (time_step=0; time_step<Nf; time_step++)
    {
        td = (time_step * DT) - (2* sqrt(M_PI)/FCORTE);
        
        fonte[time_step]= exp(-M_PI * pow((M_PI*fc*td),2)) * (1. - (2.* M_PI * pow(M_PI*fc*td, 2)));
        
    }
    
    printf("\n PARAMETROS DA FONTE: Nf = %d   FCorte = %f   dt = %f \n", Nf, FCORTE, DT);
        
   
    FILE * source_File = NULL;
    source_File = fopen ("../output/fonte.bin","wb");     
    fwrite (fonte, sizeof(float), Nf, source_File);
    
}
