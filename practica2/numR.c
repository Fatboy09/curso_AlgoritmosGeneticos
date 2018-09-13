#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void imprimir_poblacionNR(float nR[][ALELO+1])
{
    register int i,j;
    for(j = 0; j < INDIVIDUOS; j++)
    {
        for(i = 0; i < ALELO; i++)
           printf("%.2f ",nR[j][i]);

		printf("\n");
    }
}

void crear_poblacionNR(float nR[][ALELO+1])
{
    register int i,j;
    float alelo;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELO; j++)
        {
            alelo = (float) (rand() % 101)/100;
            nR[i][j] = alelo;
        }
    }

	imprimir_poblacionNR(nR);
}

