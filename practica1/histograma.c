#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM 50
#define NUM_COMANDOS 4

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
    FILE* arch = NULL;
    register int i,j;
    
    arch = fopen("datos.txt","w+");
    if(arch == NULL)
    {
        perror("Error al crear el archivo de texto\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for( i = 0; i < 10; i++)
        {
            fprintf(arch,"%d\t%d\n",i+1,a[i]);
        }
    }
    fclose(arch);
    
    printf("\t\t--Histograma--\n\n");

    for(i = 0; i < 10; i++)
    {
        printf("%d",i+1);
        for(j = 0; j < a[i]; j++)
            printf("*");
        printf("%d\n", a[i]);    
    }
    
    char * configGnuplot[] = {"set title \"Histograma\"", 
                                "set ylabel \"----Power--->\"",
                                "set xlabel \"----Frecuencia--->\"",
                                "plot \"datos.txt\" using 1:2 with linespoints pt 2, \"datos.txt\" using 1:2 with impulses"
                             };
    FILE * ventanaGnuplot = popen ("gnuplot -persist", "w");
    // Executing gnuplot commands one by one
    for (i = 0; i < NUM_COMANDOS; i++)
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[i]);
}   
