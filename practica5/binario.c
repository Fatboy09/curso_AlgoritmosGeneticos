#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

void imprimir_poblacionB(int b[][ALELOS+1])
{
    register int i,j;
    for(j = 0; j < INDIVIDUOS; j++)
    {
        for(i = 0; i < ALELOS; i++)
           printf("%d ",b[j][i]);

		printf("\n");
    }
}

void crear_poblacionB(int a[][ALELOS+1])
{
    register int i,j;
    int alelo;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELOS; j++)
        {
            alelo = rand() % 2;
            a[i][j] = alelo;
        }
        a[i][j] = -1;
    }
    //imprimir_poblacionB(a);
}
