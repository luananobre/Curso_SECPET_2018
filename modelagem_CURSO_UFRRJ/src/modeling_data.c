//
//  modeling_data.c
//
//
//  Created by Luana Nobre on 27/07/14.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modelagem2D.h"
#include "parametros.h"
#include <math.h>

void modeling_data(int time_step, float *P0, float *P1, float *fonte, float *vel_mod, float *coefic, float *amp, float *coef_dampz_left, float *coef_dampz_right, float *coef_dampz_inf, float *coef_dampz_sup, int xshot, int zshot, int Nf, int Nxx, int Nzz, FILE * snapFile_inc){


    if (time_step < Nf){
        P0[Nzz*xshot + zshot] = P0[Nzz*xshot + zshot] + fonte[time_step]*pow((DT/H),2)*pow(vel_mod[Nzz*xshot + zshot], 2);
    }

    wave_equation(P0, P1, Nxx, Nzz, vel_mod, coefic);

    if (BORDA_CONTORNO_AMORT == 1){
        apply_Cerjan_Boundary (P0, P1, Nxx, Nzz, coef_dampz_left, coef_dampz_right, coef_dampz_inf, coef_dampz_sup);
        apply_Reynolds_Boundary (P0, P1, amp, Nxx, Nzz);
    }

    update_wave_field (P0, P1, Nxx, Nzz);
    

     if (time_step%100==0){
         fwrite (&P0[0], sizeof(float), Nxx*Nzz, snapFile_inc);
     }
     

}
