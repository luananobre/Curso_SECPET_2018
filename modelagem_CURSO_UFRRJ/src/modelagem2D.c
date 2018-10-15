//
//  modelagem.c
//  
//
//  Created by Luana Nobre on 29/09/14.
//
//


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modelagem2D.h"
#include "parametros.h"


// Modelo de Velocidade de camadas plano-paralelas em 2D
void modelagem() {

    
    int Nxx = 2*NA + NX; // dimensoes do modelo de velocidades com borda NA
    int Nzz = 2*NA + NZ;

    Z0_REC += NA;  // adicao da borda (NA) a Profundidade e a posicao inicial da fonte e dos receptores
    Z0_SHOT += NA;
    X0_REC += NA; 
    X0_SHOT+= NA;

    float * vel = (float*) calloc(NX*NZ, sizeof(float)); // matriz com velocidades
    float * vel_borda  = (float*) calloc(Nxx*Nzz, sizeof(float)); // matriz com velocidades + borda NA
    
    float * P0 = (float*) calloc(Nxx*Nzz, sizeof(float)); // campo de pressao t
    float * P1 = (float*) calloc(Nxx*Nzz, sizeof(float)); // campo de pressao t+dt

    float * sis = (float*) calloc(NREC*NTOTAL, sizeof(float));
    
    float * coef_dampz_sup   = (float*) calloc(Nxx*Nzz, sizeof(float)); //variaveis auxiliares: BORDA DE AMORTECIMENTO
    float * coef_dampz_inf   = (float*) calloc(Nxx*Nzz, sizeof(float));
    float * coef_dampz_right = (float*) calloc(Nxx*Nzz, sizeof(float));
    float * coef_dampz_left  = (float*) calloc(Nxx*Nzz, sizeof(float));

    float * amp = (float*) calloc(Nxx*Nzz, sizeof(float)); //variaveis auxiliares - amp: usado na borda de Reynolds - coef: usado na eq da onda
    float * coefic = (float*) calloc(Nxx*Nzz, sizeof(float));

    int * coord_rec   = (int*) calloc(NSHOT*NREC, sizeof(int));
    int xrec, zrec, irec, ishot, time_step, i, countz;
    int xshot, zshot;
    
/*-----------------------Geracao da fonte------------------------------------------------------*/

    int Nf;
    Nf = (4*sqrt(M_PI))/(FCORTE*DT) + 1;// numero de passos de duracao da funcao gaussiana 
    float * fonte = (float*) calloc(Nf, sizeof(float));
    ricker_wavelet(fonte, Nf);
//-------------------------------------------------------------------------------------------------    
    
    FILE *snapFile_inc  = NULL;
    snapFile_inc = fopen ("../output/snapshot_inc.bin","wb");
    
    FILE * fileOut_sis = NULL;
    fileOut_sis = fopen ("../output/sismo.bin","wb");    
    
    // LEITURA DO MODELO DE VELOCIDADE
    readFile (fileNameVel, vel, NX, NZ);

    ad_borda_model_vel(vel, vel_borda, Nxx, Nzz);
    
    char vel_model_file[50];
    sprintf(vel_model_file, "../output/vel_borda_%dx%d.bin", Nxx, Nzz);
    writeToFile(vel_model_file, vel_borda, Nxx, Nzz);
    
    
/*--------------------CALCULO DOS VALORES DE REFERENCIA PARA DIESPERSAO E ESTABILIDADE--------------------*/    
    float vel_min;
    float vel_max;

    vel_min=5000;
    vel_max=0;
    for (i=0; i<NX; i++) {
        for (countz=0; countz<NZ; countz++) {
            if (vel_min > vel[NZ*i + countz]) vel_min = vel[NZ*i + countz];
            if (vel_max <= vel[NZ*i + countz]) vel_max = vel[NZ*i + countz];
        }
    }
    
    float h_limit = vel_min/(5.*FCORTE);
    float dt_limit = H/(5.*vel_max);

    printf("\n");
    printf("DISPERSAO E ESTABILIDADE:  \n");
    printf("VEL_MIN = %lf   VEL_MAX = %lf \n",vel_min, vel_max);    
    printf(" VALORES LIMITES: H <= %lf DT_MAX < %lf \n", h_limit, dt_limit);
    printf(" VALORES USADOS : H  = %d      DT = %lf \n", H, DT);
    printf("\n");
//------------------------------------------------------------------------------------------------------------
    
    // Calculo de variaveis auxiliares - amp: usado na borda de Reynolds - coef: usado na eq da onda
    // Calculados fora do loop do tempo
    for (i=0; i<Nxx; i++) {
        for (countz=0; countz<Nzz; countz++) {
            amp[Nzz*i + countz] = (vel_borda[Nzz*i + countz] * DT)/H;
            coefic[Nzz*i + countz] = -(pow(amp[Nzz*i + countz],2))/12;
        }
    }
    
    // CALCULO DOS COEFICIENTES DA BORDA DE AMORTECIMENTO
    calc_coef_damping_zones(Nxx, Nzz, coef_dampz_left, coef_dampz_right, coef_dampz_inf, coef_dampz_sup);    


    
    printf("-----MODELAGEM ACUSTICA 2D \n");
    for(ishot=0; ishot < NSHOT; ishot++) {

        printf ("_________Tiro numero: %d \n", ishot+1);

        xshot = X0_SHOT + ishot*DX_SHOT ;
        zshot = Z0_SHOT;

        memset(P0, 0., sizeof(float)*Nxx*Nzz);
        memset(P1, 0., sizeof(float)*Nxx*Nzz); 
        
        for (time_step=0; time_step<NTOTAL; time_step++) {
            
            if (time_step%1000==0) printf ("_________Passo de tempo: %d \n", time_step);
            
            modeling_data(time_step, P0, P1, fonte, vel_borda, coefic, amp, coef_dampz_left, coef_dampz_right, coef_dampz_inf, coef_dampz_sup, xshot, zshot, Nf, Nxx, Nzz, snapFile_inc);

            for (irec=0; irec<NREC; irec++){
                
                geometria (xshot, coord_rec, irec, ishot);
                sis[NTOTAL*irec + time_step]   =  P0[Nzz*coord_rec[NSHOT*irec + ishot] + Z0_REC];
            }
        }

        fwrite (sis, sizeof(float), NREC*NTOTAL, fileOut_sis);
    }


    P0=NULL;
    P1=NULL;
    vel=NULL;
    vel_borda=NULL;
    amp=NULL;
    coefic=NULL;
    sis=NULL;
    coef_dampz_left=NULL;
    coef_dampz_right=NULL;
    coef_dampz_inf=NULL;
    coef_dampz_sup=NULL;
    fonte=NULL;
    
    free(P0);
    free(P1);
    free(vel);
    free(vel_borda);
    free(amp);
    free(coefic);
    free(sis);
    free(coef_dampz_left);
    free(coef_dampz_right);
    free(coef_dampz_inf);
    free(coef_dampz_sup);
    free(fonte);
    
    fclose(snapFile_inc);
    fclose(fileOut_sis);
    
}

int main() {

	modelagem();

	return 0;
}
