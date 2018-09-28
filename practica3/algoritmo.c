#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

int To_decimal(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (ALELO - 1); i < ALELO; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}

int obtenerAptitud(int a)
{
   return a*a;
}

double calcularProba(int x, int total)
{
    return 1.00*x/total;
}

double calcularEsperanza(int fi, double f)
{
    return 1.00*fi/f;
}

void cruzar(int p1[], int p2[], int h[], int n)
{
    register int i;
    
    for(i = 0; i < ALELO; i++)
    {
        if(i < n)
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf("%d",h[i]);
    }
}

void mutar(int h[])
{
    register int k;
    int alelo = rand() % ALELO;

    for(k = 0; k < ALELO; k++)
    {
        if(k == alelo)
            h[k] = (h[k]== 0) ? 1 : 0;
    }
}

