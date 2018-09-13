#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include"defs.h"
#include"binario.h"
#include"gray.h"
#include"numR.h"
#include"numE.h"

int main()
{
    int arr[INDIVIDUOS][ALELO+1];
    float arr2[INDIVIDUOS][ALELO+1];
    int opc2;
    srand(getpid());
    
    do
    {
        system("clear");
		int opc;
		printf("\n\t\tMenu\n");
		printf("1. Representacion binaria\n");
        printf("2. Codigo Gray\n");
        printf("3. Codificacion en numeros reales\n");
        printf("4. Codificacion en numeros enteros\n");
        printf("5. Salir\n");
		printf("\nTeclee con un numero la operacion que desea hacer: ");
		scanf("%d",&opc);

		switch(opc)
		{
			case 1:
				crear_poblacionB(arr);
				break;

			case 2:
				crear_poblacionG(arr);
				break;

			case 3:
			    crear_poblacionNR(arr2);
				break;

			case 4:
			    crear_poblacionNE(arr);
				break;

			case 5:
				printf("\nAdios!!!\n");
				break;

			default:
				printf("Error... Ingreso una opcion no valida, ejecute el programa de nuevo.\n");
				break;
		}
		opc2 = 0;
	}while(opc2 > 0);

    return 0;
}

