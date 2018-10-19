#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include"defs.h"
#include"binario.h"
#include"algoritmo.h"

//void imprimirArray(int a[]);
void imprimirArray(double a[]);
void escribirArchivo(double h[], int opc);
void graficar(void);

double maxApt = 0.0, sumApt = 0.0, minApt = 1.0;

int main()
{    
    register int m,n,k;
    int arr[INDIVIDUOS][ALELO+1], baraja1[INDIVIDUOS], baraja2[INDIVIDUOS], hijos[INDIVIDUOS][ALELO+1], ganador[INDIVIDUOS][ALELO+1];
    int mayPadre[ALELO];
    double aptMax[GENERACIONES], aptMin[GENERACIONES];
    int x, ptCruza, nMuta, contador = 0;
    double sumProb = 0.0, maxProb = 0.0, ptr = 0.0, sumAcum = 0.0;
    srand(getpid());

    for(m = 0; m < INDIVIDUOS; m++)
        aptMax[m] = 0.0;

    for(m = 0; m < INDIVIDUOS; m++)
        aptMin[m] = 1.0;

    crear_poblacionB(arr);

    for(k = 0; k < GENERACIONES; k++)
    {
        sumProb = maxProb = ptr = sumAcum = 0.0;
        contador = maxApt = sumApt = 0;
        
        printf("\nGeneracion %d\n",k+1);
        printf("\nInicialización, evaluacion y seleccion de padres\n\n");
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(arr[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }

        printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)\t|Probabilidad\n");
        printf("--------+---------------+---------------+---------------+---------------\n");
        for(m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            for(n = 0; n < ALELO; n++)
            {
                printf("%d",arr[m][n]);
            }
            x = To_decimal(arr[m]);
            sumProb += calcularProba(obtenerAptitud(x),sumApt);
            if(maxProb < calcularProba(obtenerAptitud(x),sumApt))
            {
                maxProb = calcularProba(obtenerAptitud(x),sumApt);
                
                for( n = 0; n < ALELO; n++)
                    mayPadre[n] = arr[m][n];
            }
            printf("\t\t|%8d\t|%f\t|%f\n",x,obtenerAptitud(x),calcularProba(obtenerAptitud(x),sumApt));
        }
        printf("\nSuma:      \tAptitud: %f\t\tProbabilidad: %f\n",sumApt,sumProb);
        printf("Promedio:  \tAptitud: %f\t\tProbabilidad: %f\n",sumApt/INDIVIDUOS,(1.00*sumProb)/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %f\t\tProbabilidad: %f\n",maxApt,maxProb);

        if(k == 0)
        {
            aptMax[0] = maxApt;
            aptMin[0] = minApt;
        }

        printf("\n\nTorneo probabilistico 0.7>= p <=1: seleccion de padres. \n");
		printf("\nOrden |  Aptitud  |Barajear |Ganador |Barajear |Ganador\n");
        printf("------+-----------+---------+--------+---------+-------\n");

        barajear(baraja1);
        barajear(baraja2);
        //imprimirArray(baraja1);
        //imprimirArray(baraja2);
        
        for( m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d   |  ",m+1);                //orden
            x = To_decimal(arr[m]);
            printf("%4f | ",obtenerAptitud(x));     //Aptitud
            printf("%4d    |",baraja1[m]);          //Baraja1
            if((m % 2) == 0)
				printf("%6d  |",torneo(ganador[m],arr[baraja1[m]],arr[baraja1[m+1]],baraja1[m],baraja1[m+1]));    //Ganador1
			else
				printf("    --  |");
            printf("%4d     |",baraja2[m]);
            if((m % 2) == 0)
				printf("%4d  ",torneo(ganador[m+1],arr[baraja2[m]],arr[baraja2[m+1]],baraja2[m],baraja2[m+1]));    //Ganador1
			else
				printf("  --  ");
            printf("\n");
        }
        
        for(n = 0; n < INDIVIDUOS; n++)
        {
			for(m = 0; m < ALELO; m++)
				arr[n][m]=ganador[n][m];
		}

        printf("\n\nCruza y evaluación de la descendencia. \n\n");
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       |Aptitud\n");
        printf("--------+---------------+---------------+---------------+------------+---------\n");

        for(m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                ptCruza = (rand() % 3)+1;
            
            for(n = 0; n < ALELO; n++)
            {
                if(n == ptCruza)
                    printf("|%d",arr[m][n]);
                else
                    printf("%d",arr[m][n]);
            }
            printf("\t|%4d\t\t|    ",ptCruza);
            if((m % 2) == 0)
                cruzar(arr[m],arr[m+1],hijos[m],ptCruza);
            else
                cruzar(arr[m],arr[m-1],hijos[m],ptCruza);
                
            x = To_decimal(hijos[m]);
            printf("\t|%6d\t     |%f\n",x,obtenerAptitud(x));
        }

        sumApt = maxApt = 0.0;
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(hijos[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }
        printf("\nSuma:      \tAptitud: %f\n",sumApt);
        printf("Promedio:  \tAptitud: %f\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %f\n",maxApt);

        printf("\n\nMutacion y evaluacion de descendencia. \n\n");
        printf("No.\t|Descendencia  \t|Mutacion \t|Val X\t\t|Aptitud\n");
        printf("--------+---------------+---------------+---------------+-----------\n");

        nMuta = INDIVIDUOS * PMUTA;

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
            printf("\t|%6d\t\t|%f\n",x,obtenerAptitud(x));
        }

        sumApt = maxApt = 0.0;

        for(m = 0; m < INDIVIDUOS; m++)
        {
			x = To_decimal(hijos[m]);
			if(m == 0)
				minApt = obtenerAptitud(x);
			sumApt += obtenerAptitud(x);
			if(maxApt < obtenerAptitud(x))
				maxApt = obtenerAptitud(x);;
			if(minApt > obtenerAptitud(x))
				minApt = obtenerAptitud(x);
		}

        printf("\nSuma:      \tAptitud: %f\n",sumApt);
        printf("Promedio:  \tAptitud: %f\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %f\n",maxApt);
        printf("Minimo:    \tAptitud: %f\n",minApt);

        if(k > 0)
        {
            aptMax[k] = maxApt;
            aptMin[k] = minApt;
        }

        ruleta(arr,hijos,mayPadre,sumApt);

        sumApt = maxApt = 0.0;
        minApt = 1.0;
    }

    //imprimirArray(aptMax);
    //imprimirArray(aptMin);
    escribirArchivo(aptMax,1);
    escribirArchivo(aptMin,0);
    graficar();
    
    return 0;
}

/*void imprimirArray(int a[])
{
    register int i;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}*/
void imprimirArray(double a[])
{
    register int i;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        printf("%f ",a[i]);
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
            fprintf(arch, "%d %f\n", k+1, h[k]);
        }
    }

    fclose(arch);
}

void graficar(void)
{
    register int t;

    char* configGnuplot[] = {"set title \" Resultados. \"",
                                "set ylabel \"%Aptitud\"",
                                "set xlabel \"Generacion\"",
                                "plot \"aptMax.txt\" using 1:2 with lines, \"aptMin.txt\" using 1:2 with lines"
                            };

    FILE* ventanaGnuplot = popen("gnuplot -persist", "w");

    for (t = 0; t < NUM_COMANDOS; t++)
    {
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[t]);
    }
}
