#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include"defs.h"
#include"binario.h"
#include"algoritmo.h"

void imprimirArray(int a[]);
void escribirArchivo(double h[], int opc);
void graficar(void);

int maxApt = 0, sumApt = 0;

int main()
{    
    register int m,n,k;
    int arr[INDIVIDUOS][ALELO+1], r[INDIVIDUOS], c[INDIVIDUOS][ALELO+1], hijos[INDIVIDUOS][ALELO+1];
    double arr2[INDIVIDUOS], aptMax[GENERACIONES], aptMin[GENERACIONES];
    int x, i, j, ptCruza, nMuta, contador = 0;
    double sumProb = 0.0, maxProb = 0.0, ptr = 0.0, sumAcum = 0.0;
    srand(getpid());

    for(m = 0; m < INDIVIDUOS; m++)
        aptMax[m] = 0.0;

    for(m = 0; m < INDIVIDUOS; m++)
        aptMin[m] = 1.0;

    for(k = 0; k < GENERACIONES; k++)
    {
        sumProb = maxProb = ptr = sumAcum = 0.0;
        contador = maxApt = sumApt = 0;

        for(m = 0; m < INDIVIDUOS; m++)
            r[m] = 0;
        
        printf("\nGeneracion %d\n",k+1);
        printf("\n1.Inicialización, evaluacion y seleccion de padres\n\n");
        crear_poblacionB(arr);
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(arr[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }
        
        printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)=x^2\t|Probabilidad\t|ValEsp\n");
        printf("--------+---------------+---------------+---------------+---------------+---------\n");
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            for(n = 0; n < ALELO; n++)
            {
                printf("%d",arr[m][n]);
            }
            x = To_decimal(arr[m]);
            arr2[m] = calcularEsperanza(obtenerAptitud(x),((double)sumApt/INDIVIDUOS));
            sumProb += calcularProba(obtenerAptitud(x),sumApt);
            if(maxProb < calcularProba(obtenerAptitud(x),sumApt))
                maxProb = calcularProba(obtenerAptitud(x),sumApt);
            printf("\t|%6d\t\t|%5d\t\t|%f\t|%f\n",x,obtenerAptitud(x),calcularProba(obtenerAptitud(x),sumApt),arr2[m]);
        }
        
        printf("\nSuma:      \tAptitud: %5d\t\tProbabilidad: %f\n",sumApt,sumProb);
        printf("Promedio:  \tAptitud: %5d\t\tProbabilidad: %f\n",sumApt/INDIVIDUOS,(1.00*sumProb)/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %5d\t\tProbabilidad: %f\n",maxApt,maxProb);
        
        ptr = (double) (rand() % 11)/10;
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            //printf("m = %d ---------sum = %.1f ------- ptr = %.1f\n",m,sumAcum,ptr);
            for(sumAcum += arr2[m]; sumAcum > ptr; ptr++)
            {
                //printf("m = %d ---------sum = %.1f ------- ptr = %.1f\n",m,sumAcum,ptr);
                if(sumAcum > ptr)
                    r[m] += 1;
            }   
        }
        //printf("\n");
        //imprimirArray(r);
        //printf("\n");
        
        for(m = 0,i = 0; m < INDIVIDUOS; m++)
        {
            if(r[m] > 0)
            {
                for(n = 0; n < r[m]; n++)
                {
                    for(j=0;j<ALELO;j++)
                        c[i][j] = arr[m][j];
                    i++;
                }
            }
        }
        
        //imprimir_poblacionB(arr);
        //printf("-----\n");
        //imprimir_poblacionB(c);
        
        printf("\n2.Cruza y evaluacion de la descendencia\n\n");
        
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       \t|Aptitud\n");
        printf("--------+---------------+---------------+---------------+---------------+---------\n");
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                ptCruza = (rand() % 4)+1;
            
            for(n = 0; n < ALELO; n++)
            {
                if(n == ptCruza)
                    printf("|%d",c[m][n]);
                else
                    printf("%d",c[m][n]);
            }
            printf("\t|%6d\t\t|    ",ptCruza);
            if((m % 2) == 0)
                cruzar(c[m],c[m+1],hijos[m],ptCruza);
            else
                cruzar(c[m],c[m-1],hijos[m],ptCruza);
                
            x = To_decimal(hijos[m]);
            printf("\t|%6d\t\t|%5d\n",x,obtenerAptitud(x));
        }

        sumApt = 0;
        maxApt = 0;
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(hijos[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }
        
        printf("\nSuma:      \tAptitud: %5d\n",sumApt);
        printf("Promedio:  \tAptitud: %5d\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %5d\n",maxApt);

        printf("\n3.Mutacion y evaluacion de la descendencia\n\n");
        nMuta = INDIVIDUOS * PMUTA;
        printf("No.\t|Descendencia  \t|Mutacion \t|Val X\t\t|Aptitud\n");
        printf("--------+---------------+---------------+---------------+-----------\n");

        for (m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|   ", m+1);
            for (int n = 0; n < ALELO; n++)
                printf("%d", hijos[m][n]);

            printf("\t|    ");
            if ((rand() % 2) && (contador < nMuta))
            {
                mutar(hijos[m]);
                contador++;
                printf("#");
            }
            for (n = 0; n < ALELO; n++)
                printf("%d", hijos[m][n]);

            x = To_decimal(hijos[m]);
            printf("\t|%6d\t\t|%7d\n",x,obtenerAptitud(x));
        }

        sumApt = 0;
        maxApt = 0;
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(hijos[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }

        printf("\nSuma:      \tAptitud: %5d\n",sumApt);
        printf("Promedio:  \tAptitud: %5d\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %5d\n",maxApt);

        for (m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(hijos[m]);

            if (aptMax[k] < calcularProba(obtenerAptitud(x),sumApt))
                aptMax[k] = calcularProba(obtenerAptitud(x),sumApt);

            if (aptMin[k] > calcularProba(obtenerAptitud(x),sumApt))
                aptMin[k] = calcularProba(obtenerAptitud(x),sumApt);
        }
    }

    escribirArchivo(aptMax,1);
    escribirArchivo(aptMin,0);
    graficar();
    
    return 0;
}

void imprimirArray(int a[])
{
    register int i;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}

void escribirArchivo(double h[], int opc)
{
    FILE* arch = NULL;
    register int k;

    if(opc)
        arch = fopen("aptMax.txt","w+");
    else
        arch = fopen("aptMin.txt","w+");

    if (arch == NULL)
    {
        perror("Error al crear el archivo de texto\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (k = 0; k < GENERACIONES; k++)
        {
            fprintf(arch, "%d %f\n", k, h[k]);
        }
    }

    fclose(arch);
}

void graficar(void)
{
    register int t;

    char* configGnuplot[] = {"set title \" Resultados. \"",
                                "set ylabel \"Aptitud\"",
                                "set xlabel \"Generaciones\"",
                                "plot \"aptMax.txt\" using 1:2 with lines, \"aptMin.txt\" using 1:2 with lines"
                            };

    FILE* ventanaGnuplot = popen("gnuplot -persist", "w");

    for (t = 0; t < NUM_COMANDOS; t++)
    {
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[t]);
    }
}
