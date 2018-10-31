#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

extern int alelos, individuos;

int To_decimal(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (alelos - 1); i < alelos; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}

void getPattern(int a[])
{
    int i, j, contador, indice;
    int tam = PC*alelos;
    
    for(i = 0; i < alelos; i++)
        a[i] = FALSE;
    
    contador = 0;
    
    while(contador < tam)
    {
        indice = rand() % alelos;
        j = 0;
        
        while(j < indice)
            j++;
        
        if(!a[j]){
            a[j] = 1;
            contador++;
        }   
    }
}

void getMarcas(int m[][alelos+1])
{
	register int i,j;
	int n;
	
	for(i = 0; i < individuos; i++){
		for(j = 0; j < alelos; j++){
			n = rand() % 2;
			m[i][j] = n;
		}
	}
	
}

void cruzar(int p1[], int p2[], int h[], int n)
{
    register int i;
    
    for(i = 0; i < alelos; i++)
    {
        if(i < n)
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf("%d",h[i]);
    }
}

void cruzar2(int p1[],int p2[], int h[], int pt1, int pt2)
{
    register int i;
    
    for(i = 0; i < alelos; i++)
    {
        if(i < pt1)
            h[i] = p1[i];
        else{
            if(i <= pt2)
                h[i] = p2[i];
            else
                h[i] = p1[i];
        }
        
        printf("%d",h[i]);
    }
}

void cruzaUniforme(int p1[], int p2[],int h[], int patron[])
{
    register int i;
    
    for(i = 0; i < alelos; i++){
        if(patron[i])
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf("%d",h[i]);
    }
}

void cruzaAcentuada(int p1[], int p2[],int h[], int mP1[], int mP2[])
{
	register int i;
	int flagP1 = TRUE;
	
	for(i = 0; i < alelos; i++){
		if(!mP1[i] && !mP2[i]){
			if(flagP1)
				h[i] = p1[i];
			else
				h[i] = p2[i];
		}else{
			if(flagP1)
				h[i] = p1[i];
			else
				h[i] = p2[i];
			if(flagP1)
				flagP1 = FALSE;
			else
				flagP1 = TRUE;
		}
		printf("%d",h[i]);
	}
}
