#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include"defs.h"
#include"binario.h"
#include"algoritmo.h"

void imprimirArray(double a[]);
void escribirArchivo(double h[], int opc);
void graficar(void);

double maxApt = 0.0, sumApt = 0.0, minApt;
int numGen = 0;

int main()
{    
    register int m,n,k;
    int arr[INDIVIDUOS][ALELOS+1], hijos[INDIVIDUOS][ALELOS+1];
    int mayPadre[ALELOS];
    int x, ptCruza, nMuta, contador = 0;
    double sumProb = 0.0, maxProb = 0.0, sumAcum = 0.0;
    srand(getpid());

    printf("Ingrese el numero de Generaciones que desea: ");
    scanf("%d", &numGen);

    double aptMax[numGen], aptMin[numGen];

    for(m = 0; m < numGen; m++)
        aptMax[m] = 0.0;

    for(m = 0; m < numGen; m++)
        aptMin[m] = 1.0;

    crear_poblacionB(arr);
    
    for( k = 0; k < numGen; k++){
        sumProb = maxProb = sumAcum = 0.0;
        contador = maxApt = sumApt = 0;

        printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		printf("\n\tGENERACION %d", k+1);
		printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
		printf("\n\n1. Inicialización, evaluación, y selección de padres \n");
		printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)\t|Probabilidad\n");
        printf("--------+---------------+---------------+---------------+---------------\n");

        for(m = 0; m < INDIVIDUOS; m++){
            x = To_decimal(arr[m]);
            if(m == 0)
                minApt = obtenerAptitud(x);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
            if(minApt > obtenerAptitud(x))
                minApt = obtenerAptitud(x);
        }

        for(m = 0; m < INDIVIDUOS; m++){
            printf("%3d\t|  ",m+1);
            for(n = 0; n < ALELOS; n++){
                printf("%d",arr[m][n]);
            }
            x = To_decimal(arr[m]);
            sumProb += calcularProba(obtenerAptitud(x),sumApt);
            if(maxProb < calcularProba(obtenerAptitud(x),sumApt)){
                maxProb = calcularProba(obtenerAptitud(x),sumApt);
                
                for( n = 0; n < ALELOS; n++)
                    mayPadre[n] = arr[m][n];
            }
            printf("\t\t|%8d\t|%f\t|%f\n",x,obtenerAptitud(x),calcularProba(obtenerAptitud(x),sumApt));
        }

        printf("\nSuma:      \tAptitud: %f\t\tProbabilidad: %f\n",sumApt,sumProb);
        printf("Promedio:  \tAptitud: %f\t\tProbabilidad: %f\n",sumApt/INDIVIDUOS,(1.00*sumProb)/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %f\t\tProbabilidad: %f\n",maxApt,maxProb);

        //Guardamos los valores de la Generación 0
        if(k == 0){
            aptMax[0] = maxApt;
            aptMin[0] = minApt;
        }

        //Ordenamos por Aptitud, donde 1 representa al menos apto.
        ordenar(arr);

        printf("\n\n2. Cruza y evaluación de la descendencia. \n\n");
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       |Aptitud\n");
        printf("--------+---------------+---------------+---------------+------------+---------\n");

        for(m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                ptCruza = (rand() % 3)+1;
            
            for(n = 0; n < ALELOS; n++)
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
            for (int n = 0; n < ALELOS; n++)
                printf("%d", hijos[m][n]);

            printf("\t|    ");
            if ((rand() % 2) && (contador < nMuta))
            {
                mutar(hijos[m]);
                contador++;
                printf("#");
            }
            for (n = 0; n < ALELOS; n++)
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

        if(k > 0){
            aptMax[k] = maxApt;
            aptMin[k] = minApt;
        }

        ruleta(arr,hijos,mayPadre,sumApt);
        sumApt = maxApt = 0.0;
        minApt = 1.0;
    }
    
    escribirArchivo(aptMax,1);
    escribirArchivo(aptMin,0);
    graficar();
    
    return 0;
}

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
        for (k = 0; k < numGen; k++)
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
