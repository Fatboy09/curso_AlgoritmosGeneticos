#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

extern int alelos;

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

