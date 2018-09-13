#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void imprimir_poblacionNE(int nE[][ALELO+1])
{
    register int i,j;
    for(j = 0; j < INDIVIDUOS; j++)
    {
        for(i = 0; i < ALELO; i++)
           printf("%d ",nE[j][i]);

		printf("\n");
    }
}

void crear_poblacionNE(int nE[][ALELO+1])
{
    register int i,j;
    int alelo;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELO; j++)
        {
            alelo = rand() % 10;
            nE[i][j] = alelo;
        }
    }

	imprimir_poblacionNE(nE);
}

