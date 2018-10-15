//
//  writeToFile.c
//
//
//  Created by Luana Nobre on 01/05/14.
//
//

#include <stdio.h>
void writeToFile(char fileName[100], float* var, int Nx, int Nz)
{
	FILE * fileIn;
	fileIn = fopen (fileName,"wb");

    if (Nz!=0) fwrite (var, sizeof(float), Nx*Nz, fileIn);
    if (Nz == 0) fwrite (var, sizeof(float), Nx, fileIn);

	fclose(fileIn);
}
