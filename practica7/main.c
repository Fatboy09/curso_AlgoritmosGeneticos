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
    int bandera = FALSE;
    int ptCP1, ptC2P1, aux, ptCP2, ptC2P2;
    char opc;
    srand(getpid());

    printf("Ingrese el numero de individuos que desea: ");
    scanf("%d", &individuos);
    if((individuos % 2) != 0)
        bandera = TRUE;
    
    printf("Ingrese el numero de alelos que desea: ");
    scanf("%d", &alelos);
    
    int a[individuos][alelos+1], hijos[individuos][alelos+1], subCad[alelos];
    for(m = 0; m < individuos; m++)
    {
        crearPoblacion(a[m]);
    }
    
    do{
        system("clear");
        printf("\nTecnicas de cruza:\n\n");
        printf("1. Order Crossover (OX)\n");
        printf("2. Partially Mapped Crossover (PMX)\n");
        printf("3. Position Based Crossover\n");
        printf("4. Orded Based Crossover\n");
        printf("5. Cycle Crossover (CX)\n");
        printf("6. Salir\n");
        printf("Ingrese la opcion deseada: ");
        vaciar_buffer();
        opc = getchar();
        switch(opc){
            case '1':
                printf("\n----------------+-----------------------+-----------------------+------------------------\n");
                printf("      No.\t|\tPobla Ini\t|\tSubcadena\t|\tDescendencia\n");
                printf("----------------+-----------------------+-----------------------+------------------------\n");
                if(bandera)
                {
                    for(m = 0; m < individuos-1; m++)
                    {
                        setSubCadena(a[m],subCad);
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        //imprime subCadena
                        if(subCad[0] != -1)
                            printf("\t\t|%4d",a[m][0]);
                        else
                            printf("\t\t|   x");
                        for(n = 1; n < alelos; n++){
                            if(subCad[n] != -1)
                                printf("%d",a[m][n]);
                            else
                                printf("x");
                        }
                        printf("\t\t|   ");
                        if((m % 2) == 0)
                            OrderCrossover(a[m],a[m+1],hijos[m],subCad);
                        else
                            OrderCrossover(a[m],a[m-1],hijos[m],subCad);
                        printf("\n");
                    }
                    setSubCadena(a[m],subCad);
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                        printf("%d",a[m][n]);
                    }
                    //imprime subCadena
                    if(subCad[0] != -1)
                        printf("\t\t|%4d",a[m][0]);
                    else
                        printf("\t\t|   x");
                    for(n = 1; n < alelos; n++){
                        if(subCad[n] != -1)
                            printf("%d",a[m][n]);
                        else
                            printf("x");
                    }
                    printf("\t\t|   ");
                    imprimirArray(a[m],alelos);
                }else{
                    for(m = 0; m < individuos; m++)
                    {
                        setSubCadena(a[m],subCad);
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        //imprime subCadena
                        if(subCad[0] != -1)
                            printf("\t\t|%4d",a[m][0]);
                        else
                            printf("\t\t|   x");
                        for(n = 1; n < alelos; n++){
                            if(subCad[n] != -1)
                                printf("%d",a[m][n]);
                            else
                                printf("x");
                        }
                        printf("\t\t|   ");
                        if((m % 2) == 0)
                            OrderCrossover(a[m],a[m+1],hijos[m],subCad);
                        else
                            OrderCrossover(a[m],a[m-1],hijos[m],subCad);
                        printf("\n");
                    }
                }
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '2':
                printf("\n----------------+-----------------------+-----------------------+------------------------\n");
                printf("      No.\t|\tPobla Ini\t|    Puntos de Cruza\t|\tDescendencia\n");
                printf("----------------+-----------------------+-----------------------+------------------------\n");
                if(bandera)
                {
                    for(m = 0; m < individuos-1; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }

                        if((m%2) == 0){
                            ptCP1 = (rand() % (alelos-1))+1;
                            ptC2P1 = (rand() % (alelos-1))+1;

                            while(ptC2P1 == ptCP1)
                                ptC2P1 = (rand() % (alelos-1))+1;
                            
                            if(ptCP1 > ptC2P1){
                                aux = ptCP1;
                                ptCP1 = ptC2P1;
                                ptC2P1 = aux;
                            }

                            ptCP2 = (rand() % (alelos-1))+1;
                            ptC2P2 = (rand() % (alelos-1))+1;
    
                            while(ptC2P2 == ptCP2)
                            ptC2P2 = (rand() % (alelos-1))+1;
                            
                            if(ptCP2 > ptC2P2){
                                aux = ptCP2;
                                ptCP2 = ptC2P2;
                                ptC2P2 = aux;
                            }
                        }
                        printf("\t\t|    P1(%d,%d):P2(%d,%d)\t|   ",ptCP1,ptC2P1,ptCP2,ptC2P2);
                        
                        if((m % 2) == 0)
                            PartiallyMappedCrossover(a[m],a[m+1],hijos[m],ptCP2,ptC2P2);
                        else{
                            aux = ptCP2;
                            ptCP2 = ptCP1;
                            ptCP1 = aux;

                            aux = ptC2P2;
                            ptC2P2 = ptC2P1;
                            ptC2P1 = aux;

                            PartiallyMappedCrossover(a[m],a[m-1],hijos[m],ptCP2,ptC2P2);
                        }
                        printf("\n");
                    }
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                        printf("%d",a[m][n]);
                    }
                    ptCP1 = (rand() % (alelos-1))+1;
                    ptC2P1 = (rand() % (alelos-1))+1;

                    while(ptC2P1 == ptCP1)
                        ptC2P1 = (rand() % (alelos-1))+1;
                            
                    if(ptCP1 > ptC2P1){
                        aux = ptCP1;
                        ptCP1 = ptC2P1;
                        ptC2P1 = aux;
                    }
                    printf("\t\t|    P1(%d,%d):-------\t|   ",ptCP1,ptC2P1);
                    imprimirArray(a[m],alelos);
                }else{
                    for(m = 0; m < individuos; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }

                        if((m%2) == 0){
                            ptCP1 = (rand() % (alelos-1))+1;
                            ptC2P1 = (rand() % (alelos-1))+1;

                            while(ptC2P1 == ptCP1)
                                ptC2P1 = (rand() % (alelos-1))+1;
                            
                            if(ptCP1 > ptC2P1){
                                aux = ptCP1;
                                ptCP1 = ptC2P1;
                                ptC2P1 = aux;
                            }

                            ptCP2 = (rand() % (alelos-1))+1;
                            ptC2P2 = (rand() % (alelos-1))+1;
    
                            while(ptC2P2 == ptCP2)
                            ptC2P2 = (rand() % (alelos-1))+1;
                            
                            if(ptCP2 > ptC2P2){
                                aux = ptCP2;
                                ptCP2 = ptC2P2;
                                ptC2P2 = aux;
                            }
                        }
                        printf("\t\t|    P1(%d,%d):P2(%d,%d)\t|   ",ptCP1,ptC2P1,ptCP2,ptC2P2);
                        
                        if((m % 2) == 0)
                            PartiallyMappedCrossover(a[m],a[m+1],hijos[m],ptCP2,ptC2P2);
                        else{
                            aux = ptCP2;
                            ptCP2 = ptCP1;
                            ptCP1 = aux;

                            aux = ptC2P2;
                            ptC2P2 = ptC2P1;
                            ptC2P1 = aux;

                            PartiallyMappedCrossover(a[m],a[m-1],hijos[m],ptCP2,ptC2P2);
                        }
                        printf("\n");
                    }
                }
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '3':
                printf("\n----------------+-----------------------+------------------------\n");
                printf("      No.\t|\tPobla Ini\t|\tDescendencia\n");
                printf("----------------+-----------------------+------------------------\n");
                if(bandera)
                {
                    for(m = 0; m < individuos-1; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        if((m%2) == 0)
                            PositionBasedCrossover(a[m],a[m+1],hijos[m]);
                        else
                            PositionBasedCrossover(a[m],a[m-1],hijos[m]);
                        printf("\n");
                    }
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                        printf("%d",a[m][n]);
                    } 
                    printf("\t\t|   ");
                    imprimirArray(a[m],alelos);
                }else{
                    for(m = 0; m < individuos; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        if((m%2) == 0)
                            PositionBasedCrossover(a[m],a[m+1],hijos[m]);
                        else
                            PositionBasedCrossover(a[m],a[m-1],hijos[m]);
                        printf("\n");
                    }
                }
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '4':
                printf("\n----------------+-----------------------+------------------------\n");
                printf("      No.\t|\tPobla Ini\t|\tDescendencia\n");
                printf("----------------+-----------------------+------------------------\n");
            	if(bandera){
                    for(m = 0; m < individuos-1; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        if((m%2) == 0)
                            OrderBasedCrossover(a[m],a[m+1],hijos[m]);
                        else
                            OrderBasedCrossover(a[m],a[m-1],hijos[m]);
                        printf("\n");
                    }
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                        printf("%d",a[m][n]);
                    } 
                    printf("\t\t|   ");
                    imprimirArray(a[m],alelos);
            		
            	}else{
                    for(m = 0; m < individuos; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        if((m%2) == 0)
                            OrderBasedCrossover(a[m],a[m+1],hijos[m]);
                        else
                            OrderBasedCrossover(a[m],a[m-1],hijos[m]);
                        printf("\n");
                    }
            	}
            	printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '5':
            	printf("\n----------------+-----------------------+------------------------\n");
                printf("      No.\t|\tPobla Ini\t|\tDescendencia\n");
                printf("----------------+-----------------------+------------------------\n");
            	if(bandera){
                    for(m = 0; m < individuos-1; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        if((m%2) == 0)
                            CycleCrossover(a[m],a[m+1],hijos[m]);
                        else
                            CycleCrossover(a[m],a[m-1],hijos[m]);
                        printf("\n");
                    }
                    printf("%8d\t|%4d",m+1,a[m][0]);
                    for(n = 1; n < alelos; n++){
                        printf("%d",a[m][n]);
                    }
                    printf("\t\t|   ");
                    imprimirArray(a[m],alelos);
            	}else{
            		for(m = 0; m < individuos; m++){
                        printf("%8d\t|%4d",m+1,a[m][0]);
                        for(n = 1; n < alelos; n++){
                            printf("%d",a[m][n]);
                        }
                        if((m%2) == 0)
                            CycleCrossover(a[m],a[m+1],hijos[m]);
                        else
                            CycleCrossover(a[m],a[m-1],hijos[m]);
                        printf("\n");
                    }
            	}
            	printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '6':
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
