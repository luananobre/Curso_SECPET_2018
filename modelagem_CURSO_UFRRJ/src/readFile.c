//
//  openFile.c
//  
//
//  Created by Luana Nobre on 01/05/14.
//  Le arquivos com uma coluna
//

#include <stdio.h>

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int readFile(const char *fileName, float* var, int Nx, int Nz)
{
    struct stat buf;
    
    errno = 0;
    if ( stat ( fileName, &buf ) != 0 && errno == ENOENT ) {
        fprintf ( stderr, "File:%s does not exist\n", fileName);
        exit ( EXIT_FAILURE );
    }

    FILE * file;
    file = fopen (fileName,"rb");
    fread (var, sizeof(float), Nx*Nz, file);
    fclose(file);
    
    
    return EXIT_SUCCESS;
    

}