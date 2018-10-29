#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

int To_decimal(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (ALELOS - 1); i < ALELOS; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}

double obtenerAptitud(int x)
{
    int a = x - 5;
    double b = 2.0 + sin(x/(180*PI));
   return ((float) a/b) < 0 ? (-1)*((float) a/b) : ((float) a/b);
}

double calcularProba(double x, int total)
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
    
    for(i = 0; i < ALELOS; i++)
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
    int alelo = rand() % ALELOS;

    for(k = 0; k < ALELOS; k++)
    {
        if(k == alelo)
            h[k] = (h[k]== 0) ? 1 : 0;
    }
}

void ordenar(int indiv[][ALELOS+1]){
    register int i,j,k;
    int x, apt1, apt2;
    int aux[ALELOS+1];

    //Aplicando el metodo de burbuja
    for( i = 1; i < INDIVIDUOS; i++)
    {
        for( j = 0; j < (INDIVIDUOS-1); j++)
        {
            x = To_decimal(indiv[j]);
            apt1 = obtenerAptitud(x);
            x = To_decimal(indiv[j]);
            apt2 = obtenerAptitud(x);
            
            if (apt1 > apt2) {
                for( k = 0; k < ALELOS+1; k++)
                    aux[k] = indiv[j][k];
                for( k = 0; k < ALELOS; k++)
                    indiv[j][k] = indiv[j+1][k];
                for( k = 0; k < ALELOS; k++)
                    indiv[j+1][k] = aux[k];
            }    
        }
    }
}

double rankingLineal(int i){
    double P, base;
    int exp;
    double min = 2 - MAX;
    base = MAX - min;
    exp = (i-1)/(INDIVIDUOS-1);
    i = i+1;
    P = min + (pow(base,exp));
    return P;
}

void ruleta(int indiv[][ALELOS+1], int hijo[][ALELOS+1], int mayPadre[], int max)
{
    register int i,j,k;
    int rul, acum;
    //guardamos al mas apto
    for( i = 0; i < ALELOS; i++)
        indiv[0][i] = mayPadre[i]; 
    //ruleteamos a los demas
    for( i = 1; i < INDIVIDUOS; i++)
    {
        acum = 0;
        rul = rand()%(max+1);
        
        for( j = 0; j < INDIVIDUOS; j++)
        {
            acum += rankingLineal(j);
            if (acum >= rul)
            {
                for( k = 0; k < ALELOS; k++)
                    indiv[i][k] = hijo[i][k];  
                break;
            }
        }
    }
}
