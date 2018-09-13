#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void imprimir_poblacionB(int b[][ALELO+1])
{
    register int i,j;
    for(j = 0; j < INDIVIDUOS; j++)
    {
        for(i = 0; i < ALELO; i++)
           printf("%d ",b[j][i]);

		printf("\n");
    }
}

void crear_poblacionB(int a[][ALELO+1])
{
    register int i,j;
    int alelo;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELO; j++)
        {
            alelo = rand() % 2;
            a[i][j] = alelo;
        }
    }
    imprimir_poblacionB(a);
}
