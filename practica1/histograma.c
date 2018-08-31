#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM 50

int numAl();
void llenarArray(int*);
void dibujarHistograma(int []);
void imprimirArray(int []);

int main()
{
    int array[10];
    srand(getpid());
    
    llenarArray(array);
    printf("Array: ");
    imprimirArray(array);
    printf("\n");
    dibujarHistograma(array);

    return 0;
}

int numAl()
{
    return rand() % NUM + 1;
}

void llenarArray(int* a)
{
    register int i;
    
    for(i = 0; i < 10; i++)
    {
        a[i] = numAl();
    }
}

void imprimirArray(int a[])
{
    register int i;
    
    for(i = 0; i < 10; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

void dibujarHistograma(int a[])
{
    printf("\t\t--Histograma--\n\n");
    register int i,j;
    for(i = 0; i < 10; i++)
    {
        printf("%d",i+1);
        for(j = 0; j < a[i]; j++)
            printf("*");
        printf("%d\n", a[i]);    
    }
}   
