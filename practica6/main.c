#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include"defs.h"
#include"binario.h"
#include"algoritmo.h"

void imprimirArray(int a[]);
void vaciar_buffer();

int individuos, alelos;

int main()
{   
    register int m,n;
    int ptCruza, bandera = FALSE;
    char opc;
    srand(getpid());

    printf("Ingrese el numero de individuos que desea: ");
    scanf("%d", &individuos);
    if((individuos % 2) != 0)
        bandera = TRUE;
    
    printf("Ingrese el numero de alelos que desea: ");
    scanf("%d", &alelos);
    
    int a[individuos][alelos+1], hijos[individuos][alelos+1];
    crear_poblacionBin(a);
    
    do{
        system("clear");
        printf("\nTecnicas de cruza:\n");
        printf("1. Cruza de un punto\n");
        printf("2. Cruza de dos punto\n");
        printf("3. Cruza uniforme\n");
        printf("4. Cruza acentuada\n");
        printf("5. Salir\n");
        printf("Ingrese la opcion deseada: ");
        vaciar_buffer();
        opc = getchar();
        switch(opc){
            case '1':
                printf("No.\t|cruza       \t|P Cruza \t|Descendencia\n");
                printf("--------+---------------+---------------+-------------\n");
                if(bandera){
                    for(m = 0; m < individuos-1; m++)
                    {
                        printf("%3d\t|  ",m+1);
                        
                        if((m % 2) == 0)            
                            ptCruza = (rand() % (alelos-1))+1;
                        
                        for(n = 0; n < alelos; n++)
                        {
                            if(ptCruza == n)
                                printf("|%d",a[m][n]);
                            else
                                printf("%d",a[m][n]);
                        }
                        printf("\t|%4d\t\t|    ",ptCruza);
                        if((m % 2) == 0)
                            cruzar(a[m],a[m+1],hijos[m],ptCruza);
                        else
                            cruzar(a[m],a[m-1],hijos[m],ptCruza);
                        
                        printf("\n");
                    }
                    printf("%3d\t|  ",m+1);
                    if((m % 2) == 0)            
                        ptCruza = (rand() % (alelos-1))+1;
                    for(n = 0; n < alelos; n++)
                    {
                        if(ptCruza == n)
                            printf("|%d",a[m][n]);
                        else
                            printf("%d",a[m][n]);
                    }
                    printf("\t|%4d\t\t|    ",ptCruza);
                    imprimirArray(a[m]);
                }
                else
                {
                    for(m = 0; m < individuos; m++)
                    {
                        printf("%3d\t|  ",m+1);
                        
                        if((m % 2) == 0)            
                            ptCruza = (rand() % (alelos-1))+1;
                        
                        for(n = 0; n < alelos; n++)
                        {
                            if(ptCruza == n)
                                printf("|%d",a[m][n]);
                                //printf("|");
                            else
                                printf("%d",a[m][n]);
                        }
                        printf("\t|%4d\t\t|    ",ptCruza);
                        if((m % 2) == 0)
                            cruzar(a[m],a[m+1],hijos[m],ptCruza);
                        else
                            cruzar(a[m],a[m-1],hijos[m],ptCruza);
                        
                        printf("\n");
                    }
                }
                
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '2':
                opc = 0;
                break;
                
            case '3':
                opc = 0;
                break;
            
            case '4':
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

void imprimirArray(int a[])
{
    register int i;
    
    for(i = 0; i < alelos; i++)
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
