#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "binario.h"

void imprimir_poblacionG(int b[][ALELO+1], int g[][ALELO+1])
{
    register int i,j;
    for(j = 0; j < INDIVIDUOS; j++)
    {
	    printf("Binario:\t");
        for(i = 0; i < ALELO; i++)
           printf("%d ",b[j][i]);
           
        printf("\nGray:\t\t");
        
		for(i = 0; i < ALELO; i++)
           printf("%d ",g[j][i]);

		printf("\n\n");
    }
}

void crear_poblacionG(int gray[][ALELO+1])
{
    register int i,j,a,b,c;
    int individuo[INDIVIDUOS][ALELO+1];
    int alelo;
    
    //creamos primero la poblacion en binario
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELO; j++)
        {
            alelo = rand() % 2;
            individuo[i][j] = alelo;
        }
    }
    //Algoritmo para convertir de binario a codigo gray
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = ALELO; j > 0; j--)
        {
			
			gray[i][j] = individuo[i][j] ^ individuo[i][j-1];
		}
		gray[i][0] = individuo[i][0];
	}
	imprimir_poblacionG(individuo,gray);
}

