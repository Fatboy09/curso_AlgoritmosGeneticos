#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include"defs.h"
#include"algoritmo.h"

int cmpfunc (const void * a, const void * b);
void imprimirArray(int a[],int tam);
void vaciar_buffer();

int individuos, alelos;

int main()
{   
    register int m,n;
    char opc;
    int NoDesp;
    srand(getpid());

    printf("Ingrese el numero de individuos que desea: ");
    scanf("%d", &individuos);
    
    printf("Ingrese el numero de alelos que desea: ");
    scanf("%d", &alelos);
    
    int a[individuos][alelos+1];
    for(m = 0; m < individuos; m++)
    {
        crearPoblacion(a[m]);
    }
    
    do{
        system("clear");
        printf("\nTecnicas de Mutacion:\n\n");
        printf("1. Insercion\n");
        printf("2. Desplazamiento\n");
        printf("3. Intercambio reciproco\n");
        printf("4. Heuristico\n");
        printf("5. Salir\n");
        printf("Ingrese la opcion deseada: ");
        vaciar_buffer();
        opc = getchar();
        switch(opc){
            case '1':
                printf("\n----------------+-----------------------+-----------------------+\n");
                printf("      No.\t|\tIndividuo\t|\tDescendencia\n");
                printf("----------------+-----------------------+-----------------------+\n");
                for(m = 0; m < individuos; m++)
                {
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                    	printf("%d",a[m][n]);
                    }

                    printf("\t\t|   ");
                    Insercion(a[m]);
                    
                    printf("\n");
				}    
                
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '2':
                printf("\n----------------+-----------------------+-----------------------+\n");
                printf("      No.\t|\tIndividuo\t|\tDescendencia\n");
                printf("----------------+-----------------------+-----------------------+\n");
                
                for(m = 0; m < individuos; m++)
                {
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                    	printf("%d",a[m][n]);
                    }

                    printf("\t\t|   ");
                    NoDesp = rand() % (alelos-1) + 1;
                    Desplazamiento(a[m]);
                    for(n = 0; n < NoDesp; n++)
						Desplazamiento(a[m]);

                    //imprimimos individuo
                    for(n = 0; n < alelos; n++)
                        printf("%d",a[m][n]);
                    
                    printf("\n");
				}  

                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '3':
                printf("\n----------------+-----------------------+-----------------------+\n");
                printf("      No.\t|\tIndividuo\t|\tDescendencia\n");
                printf("----------------+-----------------------+-----------------------+\n");

                for(m = 0; m < individuos; m++)
                {
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                    	printf("%d",a[m][n]);
                    }

                    printf("\t\t|   ");
                    InterReciproco(a[m]);          
                    printf("\n");
				}
                
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '4':
                printf("\n----------------+---------------------------------------+\n");
                printf("      No.\t|\tIndividuo\n");
                printf("----------------+---------------------------------------+\n");

                for(m = 0; m < individuos; m++)
                {
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                    	printf("%d",a[m][n]);
                    }

                    printf("\t\t|   ");
                    Heuristico(a[m]);          
                    printf("\n");
                    printf("-----------------------------------------------------------------\n");
				}
            	
            	printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '5':
                printf("Bye!!! :3\n");
                exit(1);
                break;
            
            default:
                printf("Error. Opcion no valida, intentelo de nuevo. ");
                printf("Presione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
        }
    
    }while(opc == 0);
    
    return 0;
}

void imprimirArray(int a[], int tam)
{
    register int i;
    
    for(i = 0; i < tam; i++)
    {
        printf("%d",a[i]);
    }
    printf("\n");
}

void vaciar_buffer()
{
    int fdflags;
    fdflags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, fdflags | O_NONBLOCK);
    while (getchar()!=EOF);
    fcntl(STDIN_FILENO, F_SETFL, fdflags);
}
