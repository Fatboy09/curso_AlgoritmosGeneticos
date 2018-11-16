#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

extern int alelos, individuos;

void crearPoblacion(int a[])
{
    int elegidos[alelos];                                   // ¿ya salio ese numero? (del 0 a alelos-1)
    int posibles = alelos, contador, posicion, i, j;

    
    for( i = 0; i < alelos; i++)
        elegidos[i] = FALSE;                                // Empieza que no se ha elegido ningun numero
    
    
    for( i = 0; i < alelos; i++)
    {
        posicion = rand() % posibles+1;     // elige al azar una posicion entre los no elegidos (de 1 a INDIVIDUOS)
        j = 0;
        contador = 0;                       // cuenta los numeros no elegidos que encuenta.
        
        while(contador < posicion)      // Cuenta las posiciones no elegidas
        {
            if(!elegidos[j++])
                contador++;             // Si el numero ya fue elegido se ignora 
        }
        j--;                            // Cuando encuentra la posicion hace un j++ de mas.
        elegidos[j] = TRUE;             // se marca la posicion como elegida
        posibles--;                     // hay una posicion "no elegida" menos
        a[i] = j+1;                     // La posicion dentro la lista de elegidos es el numero a guardar
    }
}

int Aptitud(int individ[], int new[], int apt)
{
	int i,j,aptitud=0;
	for(i=0,j=alelos;i<alelos;i++,j--){
		aptitud=aptitud+(individ[i]*j);
	}
	if(apt<aptitud){
		for(i=0;i<alelos;i++){
			new[i]=individ[i];
		}
		return aptitud;
	}else{
		return apt;
	}
}

void Permutar(int x, int y, int z, int individ[], int lambda[], int aux[],int k)
{
	int i,j;
	printf("\t\t%d) %d %d %d => ",k,lambda[x],lambda[y],lambda[z]);
		j=0;
		for(i=0;i<alelos;i++){
			if(aux[i]==1){
				switch(j){
					case 0:
						individ[i]=lambda[x];
					break;
					case 1:
						individ[i]=lambda[y];
					break;
					case 2:
						individ[i]=lambda[z];
					break;
				}
				j++;
			}
			printf("%d ",individ[i]);
		}
		printf("\n");
}

void Insercion(int indiv[])
{
    int i = rand() % alelos;
    int j = rand() % alelos;
    int k,aux,aux2;
    //i el menor
    while((j < i) || (j==i)){
        if(i == j)
            i = rand() % alelos;
        j=rand()%(alelos);
    }

    printf("(%d->%d) => ",j+1,i+1);
    
    aux = indiv[i];
	indiv[i] = indiv[j];

	for(k = i+1; k <= j; k++){
		aux2 = indiv[k];
		indiv[k] = aux;
		aux = aux2;
	}

	for(k=0;k<alelos;k++)
		printf("%d",indiv[k]);
}

void Desplazamiento(int indiv[])
{
    int i=rand() % alelos;
	int j=rand() % alelos;
	int k,aux,aux2;
	//i el menor
	while((j < i) || (j==i)){
		if(i == j)
			i = rand() % alelos;
		j=rand() % alelos;
	}
	printf("(%d->%d) => ",j+1,i+1);
	
	aux = indiv[i];
	indiv[i] = indiv[j];

	for(k = i+1; k <= j; k++){
		aux2 = indiv[k];
		indiv[k] = aux;
		aux = aux2;
	}
}

void InterReciproco(int indiv[])
{
    int i = rand() % alelos;
	int j = rand() % alelos;
	int k,aux;
	//i el menor
	//seleccionamos dos puntos al azar
	while((j < i)||(j == i)){
		if(i == j)
			i = rand() % alelos;
		j=rand() % alelos;
	}
	printf("(%d->%d) => ",j+1,i+1);
	
	aux = indiv[i];
	indiv[i] = indiv[j];
	indiv[j] = aux;
	
	for( k = 0; k < alelos; k++){
		printf("%d",indiv[k]);
	}
}

void Heuristico(int indiv[])
{
    /* seleccionamos genes al azar	*/
	//asociando una cadena binaria que tenga 3 unos
	int i,j=0,k=0,n,apt=0; 
	int aux[alelos+1],lambda[alelos+1],new[alelos+1];
	while(k<3){
		k=0;
		for(i=0;i<alelos;i++){
			if(k>2){
				n=0;
			}else{
				n=rand() % 2;
			}
			aux[i]=n;
			if(n==1){
				k++;
			}
		}
	}
	//seleccionamos los genes a permutar
		for(i=0;i<alelos;i++){
			if(aux[i]==1){
				lambda[j]=indiv[i];
				j++;
			}
		}
	//imprimimos lambda
		printf("\n\t Generando permutaciones de: ");
		for(i=0;i<j;i++){
			printf("%d ",lambda[i]);
		}
		printf("\n");
	/* Creamos permutaciones */
		Permutar(0,2,1,indiv,lambda,aux,1);
		apt=Aptitud(indiv,new,apt);
		Permutar(1,0,2,indiv,lambda,aux,2);
		apt=Aptitud(indiv,new,apt);
		Permutar(1,2,0,indiv,lambda,aux,3);
		apt=Aptitud(indiv,new,apt);
		Permutar(2,1,0,indiv,lambda,aux,4);
		apt=Aptitud(indiv,new,apt);
		Permutar(2,0,1,indiv,lambda,aux,5);
		apt=Aptitud(indiv,new,apt);
	//imprimimos el más apto
		printf("\tSeleccionamos el mejor: ");
		for(i=0;i<alelos;i++){
			printf("%d ",new[i]);
		}
		printf("\n");
}
