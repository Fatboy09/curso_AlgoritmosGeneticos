#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

extern int individuos, alelos;

void imprimir_poblacionBin(int b[][alelos+1])
{
    register int i,j;
    for(j = 0; j < individuos; j++)
    {
        for(i = 0; i < alelos; i++)
           printf("%d ",b[j][i]);

		printf("\n");
    }
}

void crear_poblacionBin(int a[][alelos+1])
{
    register int i,j;
    int alelo;
    
    for(i = 0; i < individuos; i++)
    {
        for(j = 0; j < alelos; j++)
        {
            alelo = rand() % 2;
            a[i][j] = alelo;
        }
        a[i][j] = -1;
    }
    //imprimir_poblacionBin(a);
}
