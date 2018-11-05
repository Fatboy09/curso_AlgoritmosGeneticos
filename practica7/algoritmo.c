#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

extern int alelos, individuos;

void randomNumbers(int a[], int tam, int num)
{
    int elegidos[num];                                   // ¿ya salio ese numero? (del 0 a alelos-1)
    int posibles = num, contador, posicion, i, j;

    
    for( i = 0; i < num; i++)
        elegidos[i] = FALSE;                                // Empieza que no se ha elegido ningun numero
    
    
    for( i = 0; i < tam; i++)
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
        a[i] = j;                       // La posicion dentro la lista de elegidos es el numero a guardar
    } 
}

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

void setSubCadena(int padre[], int subCad[])
{
    register int i;
    int tamSubCad, inicio;

    if(alelos > 2)
        tamSubCad = (rand() % (alelos-2))+1;
    else
        tamSubCad = 1;
    
    for(i = 0; i < alelos; i++)                   //Inicializamos subCad con valor de -1
        subCad[i] = -1;

    int lista[tamSubCad];
    //printf("tamSubCad = %d\n", tamSubCad);

    inicio = (rand() % ((alelos - tamSubCad) + 1));
    //printf("inicio = %d\n", inicio);

    for(i = 0; i < tamSubCad; i++){               //Guardamos en un arreglo los indices de la Subcadena
        lista[i] = inicio;
        inicio++;
    }

    for(i = 0; i < tamSubCad; i++){
        subCad[lista[i]] = lista[i];                //Almacenamos los indices en el arreglo SubCad
    }
}

int buscar(int a[], int num)
{
    int i = 0;
    int indice = -1;

    while(i < alelos){
        if(a[i] == num){
            indice = i;
            i = alelos+1;
        }
        i++;
    }
    return indice;
}

void OrderCrossover(int p1[], int p2[], int h[], int subCad[])
{
    register int m,n;
    int aux[alelos];
    int i;

    for(m = 0; m < alelos; m++){                    //Inicializamos aux con los valores del padre 2
        aux[m] = p2[m];
    }
    
    for(m = 0; m < alelos; m++){
        i = buscar(p2,p1[subCad[m]]);               //Buscamos los elementos de subCad en el padre 2 
        if(i != -1)                                 //y los eliminamos de aux (se ponen con valor de -1)
            aux[i] = -1;
    }

    for(m = 0, n = 0; m < alelos; m++)
    {
        if(subCad[m] != -1)
            h[m] = p1[subCad[m]];
        else{
            if(aux[n] != -1){
                h[m] = aux[n];
                n++;
            }else{
                while(aux[n] == -1)
                    n++;
                h[m] = aux[n];
                n++;
            }
        }
        printf("%d",h[m]);
    }
}

void PartiallyMappedCrossover(int p1[], int p2[], int h[], int ptP2, int pt2P2)
{
    register int i;
    int indice, j;

    for(i = 0; i < alelos; i++)
        h[i] = -1;

    for(i = ptP2; i <= pt2P2; i++)
    {
        h[i] = p2[i];
    }

    for(i = 0, j = 0; i < alelos; i++)
    {
        indice = buscar(h,p1[i]);
        if(indice == -1)
        {
            while(h[j] != -1)
                j++;

            h[j]=p1[i];
            j++;
        }
    }

    for(i = 0, j = 0; i < alelos; i++)
    {
        indice = buscar(h,p2[i]);
        if(indice == -1)
        {
            while(h[j] != -1)
                j++;

            h[j]=p2[i];
            j++;
        }
    }

    for(i = 0; i < alelos; i++)
        printf("%d",h[i]);
}

void PositionBasedCrossover(int p1[], int p2[], int h[])
{
    int numAlelos = 1;
    int i, indice, j;

    if(alelos > 2) 
        numAlelos = (rand() % (alelos-2)+1)+1;

    int posiciones[numAlelos], auxP2[alelos-numAlelos];

    for(i = 0; i < alelos; i++)
        h[i] = -1;

    randomNumbers(posiciones,numAlelos,alelos);

    printf("\t\t|   ");
    for(i = 0; i < numAlelos; i++)
    {
        h[posiciones[i]] = p1[posiciones[i]];
    }
    for(i = 0; i < alelos; i++){
        if(h[i] != -1)
            printf("%d",h[i]);
        else
            printf("x");
    }

    for(i = 0, j = 0; i < alelos; i++){
        indice = buscar(h,p2[i]);
        if(indice == -1){
            auxP2[j] = p2[i];
            j++;
        }
    }
    
    for(i = 0, j = 0; i < alelos; i++){
        if(h[i] == -1){
            h[i] = auxP2[j];
            j++;
        }
    }
    printf(" => ");

    for(i = 0; i < alelos; i++)
        printf("%d",h[i]);
}
