#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include"defs.h"
#include"binario.h"
#include"algoritmo.h"

int cmpfunc (const void * a, const void * b);
void imprimirArray(int a[],int tam);
void vaciar_buffer();

int individuos, alelos;

int main()
{   
    register int m,n;
    int ptCruza, ptCruza2, aux, bandera = FALSE;
    char opc;
    srand(getpid());

    printf("Ingrese el numero de individuos que desea: ");
    scanf("%d", &individuos);
    if((individuos % 2) != 0)
        bandera = TRUE;
    
    printf("Ingrese el numero de alelos que desea: ");
    scanf("%d", &alelos);
    
    int a[individuos][alelos+1], hijos[individuos][alelos+1], pattern[alelos], marcas[individuos][alelos+1];
    crear_poblacionBin(a);
    
    do{
        system("clear");
        printf("\nTecnicas de cruza:\n\n");
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
                printf("\nNo.\t|cruza       \t|P Cruza \t|Descendencia\n");
                printf("--------+---------------+---------------+-------------\n");
                if(bandera)
                {
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
                        printf("\t|%4d\t\t|  ",ptCruza);
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
                    printf("\t|%4d\t\t|  ",ptCruza);
                    imprimirArray(a[m],alelos);
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

                            else
                                printf("%d",a[m][n]);
                        }
                        printf("\t|%4d\t\t|   ",ptCruza);
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
                printf("\nNo.\t|cruza       \t|P Cruza \t|Descendencia\n");
                printf("--------+---------------+---------------+-------------\n");
                if(bandera)
                {
                    for(m = 0; m < individuos-1; m++)
                    {
                        printf("%3d\t|  ",m+1);
                        
                        if((m % 2) == 0)
                        {            
                            ptCruza = (rand() % (alelos-1))+1;
                            ptCruza2 = (rand() % (alelos-1))+1;
                            while(ptCruza2 == ptCruza)
                                ptCruza2 = (rand() % (alelos-1))+1;
                            
                            if(ptCruza > ptCruza2){
                                aux = ptCruza;
                                ptCruza = ptCruza2;
                                ptCruza2 = aux;
                            }
                        }
                        
                        for(n = 0; n < alelos; n++)
                        {
                            if(ptCruza == n)
                                printf("|%d",a[m][n]);
                            else if(ptCruza2 == n)
                                printf("%d|",a[m][n]);
                            else
                                printf("%d",a[m][n]);
                        }
                        printf("\t|%4d,%d\t\t|  ",ptCruza, ptCruza2);
                        if((m % 2) == 0)
                            cruzar2(a[m],a[m+1],hijos[m],ptCruza,ptCruza2);
                        else
                            cruzar2(a[m],a[m-1],hijos[m],ptCruza,ptCruza2);
                        
                        printf("\n");
                    }
                    printf("%3d\t|  ",m+1);
           
                    ptCruza = (rand() % (alelos-1))+1;
                    ptCruza2 = (rand() % (alelos-1))+1;
                    while(ptCruza2 == ptCruza)
                        ptCruza2 = (rand() % (alelos-1))+1;
                    
                    if(ptCruza > ptCruza2){
                        aux = ptCruza;
                        ptCruza = ptCruza2;
                        ptCruza2 = aux;
                    }

                    for(n = 0; n < alelos; n++)
                    {
                        if(ptCruza == n)
                            printf("|%d",a[m][n]);
                        else if(ptCruza2 == n)
                            printf("%d|",a[m][n]);
                        else
                            printf("%d",a[m][n]);
                    }
                    printf("\t|%4d,%d\t\t|  ",ptCruza, ptCruza2);
                    imprimirArray(a[m],alelos);
                }
                else{
                    for(m = 0; m < individuos; m++)
                    {
                        printf("%3d\t|  ",m+1);
                        
                        if((m % 2) == 0)
                        {            
                            ptCruza = (rand() % (alelos-1))+1;
                            ptCruza2 = (rand() % (alelos-1))+1;
                            while(ptCruza2 == ptCruza)
                                ptCruza2 = (rand() % (alelos-1))+1;
                            
                            if(ptCruza > ptCruza2){
                                aux = ptCruza;
                                ptCruza = ptCruza2;
                                ptCruza2 = aux;
                            }
                        }
                        
                        for(n = 0; n < alelos; n++)
                        {
                            if(ptCruza == n)
                                printf("|%d",a[m][n]);
                            else if(ptCruza2 == n)
                                printf("%d|",a[m][n]);
                            else
                                printf("%d",a[m][n]);
                        }
                        printf("\t|%4d,%d\t\t|   ",ptCruza, ptCruza2);
                        if((m % 2) == 0)
                            cruzar2(a[m],a[m+1],hijos[m],ptCruza,ptCruza2);
                        else
                            cruzar2(a[m],a[m-1],hijos[m],ptCruza,ptCruza2);
                        
                        printf("\n");
                    }
                }
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
                
            case '3':
                printf("\nNo.\t|P.Ini       \t|Pattern \t|Descendencia\n");
                printf("--------+---------------+---------------+-------------\n");
                
                if(bandera)
                {
                    for(m = 0; m < individuos-1; m++)
                    {
                        printf("%3d\t|  ",m+1);
                        
                        if(m % 2 == 0)
                            getPattern(pattern);
                        
                        for(n = 0; n < alelos; n++)
                            printf("%d",a[m][n]);
                        
                        printf("\t|   ");
                        
                        for(n = 0; n < alelos; n++)
                            printf("%d",pattern[n]);
                        
                        printf("\t|  ");
                        
                        if((m % 2) == 0)
                            cruzaUniforme(a[m],a[m+1],hijos[m],pattern);
                        else
                            cruzaUniforme(a[m],a[m-1],hijos[m],pattern);
                        
                        printf("\n");
                    }
                    printf("%3d\t|  ",m+1);
                    getPattern(pattern);
                    for(n = 0; n < alelos; n++)
                        printf("%d",a[m][n]);	
                    
                    printf("\t|   ");
                        
                    for(n = 0; n < alelos; n++)
                        printf("%d",pattern[n]);
                    
                    printf("\t|  ");
                    imprimirArray(a[m],alelos);
                }else{
                    for(m = 0; m < individuos; m++)
                    {
                        printf("%3d\t|  ",m+1);
                        
                        if(m % 2 == 0)
                            getPattern(pattern);
                        
                        for(n = 0; n < alelos; n++)
                            printf("%d",a[m][n]);
                        
                        printf("\t|   ");
                        
                        for(n = 0; n < alelos; n++)
                            printf("%d",pattern[n]);
                        
                        printf("\t|   ");
                        
                        if((m % 2) == 0)
                            cruzaUniforme(a[m],a[m+1],hijos[m],pattern);
                        else
                            cruzaUniforme(a[m],a[m-1],hijos[m],pattern);
                        
                        printf("\n");
                    } 
                }
                printf("\n\nPresione la tecla enter para continuar...");
                vaciar_buffer();
                getchar();
                opc = 0;
                break;
            
            case '4':
            	printf("\nNota: En la seccion de \"Marcas\" los \'1\' representan los alelos del individuo que estan marcados\n");
            	printf("\nNo.\t|P.Ini       \t|Marcas  \t|Descendencia\n");
                printf("--------+---------------+---------------+-------------\n");
            	
            	getMarcas(marcas);
            	
            	if(bandera){
            		for(m = 0; m < individuos-1; m++){
            			printf("%3d\t|  ",m+1);
            			for(n = 0; n < alelos; n++)
                            printf("%d",a[m][n]);
                        
                        printf("\t|  ");
                        for(n = 0; n < alelos; n++)
                            printf("%d",marcas[m][n]);
                        
                        printf("\t|  ");
                        
                        if((m % 2) == 0)
                        	cruzaAcentuada(a[m],a[m+1],hijos[m],marcas[m],marcas[m+1]);
                        else
                        	cruzaAcentuada(a[m],a[m-1],hijos[m],marcas[m],marcas[m-1]);
                        
                        printf("\n");
            		}
            		printf("%3d\t|  ",m+1);
            		for(n = 0; n < alelos; n++)
                        printf("%d",a[m][n]);
                    
                    printf("\t|  ");
                    for(n = 0; n < alelos; n++)
                            printf("%d",marcas[m][n]);
                    
                    printf("\t|  ");
                    imprimirArray(a[m],alelos);
            	}else{
            		for(m = 0; m < individuos; m++){
            			printf("%3d\t|  ",m+1);
            			for(n = 0; n < alelos; n++)
                            printf("%d",a[m][n]);
                        
                        printf("\t|  ");
                        for(n = 0; n < alelos; n++)
                            printf("%d",marcas[m][n]);
                        
                        printf("\t|   ");
                        
                        if((m % 2) == 0)
                        	cruzaAcentuada(a[m],a[m+1],hijos[m],marcas[m],marcas[m+1]);
                        else
                        	cruzaAcentuada(a[m],a[m-1],hijos[m],marcas[m],marcas[m-1]);
                        
                        printf("\n");
            		}
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
