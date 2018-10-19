#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"defs.h"

int To_decimal(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (ALELO - 1); i < ALELO; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}

double obtenerAptitud(int x)
{
    int a = x - 5;
    double b = 2.0 + sin(x/(180*PI));
   return ((float) a/b) < 0 ? (-1)*((float) a/b) : ((float) a/b);
}

double calcularProba(double x, int total)
{
    return 1.00*x/total;
}

double calcularEsperanza(int fi, double f)
{
    return 1.00*fi/f;
}

void cruzar(int p1[], int p2[], int h[], int n)
{
    register int i;
    
    for(i = 0; i < ALELO; i++)
    {
        if(i < n)
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf("%d",h[i]);
    }
}

void mutar(int h[])
{
    register int k;
    int alelo = rand() % ALELO;

    for(k = 0; k < ALELO; k++)
    {
        if(k == alelo)
            h[k] = (h[k]== 0) ? 1 : 0;
    }
}

int flip()
{
    double n = 0.0;
    n = (float) (rand() % 101) / 100;
    
    if (n >= PFLIP)
        return TRUE;
    else
        return FALSE;
    
}

void barajear(int a[])
{
    int elegidos[INDIVIDUOS];   // ¿ya salio ese numero? (del 0 al 20)
    int posibles = INDIVIDUOS, contador, posicion, i, j;

    
    for( i = 0; i < INDIVIDUOS; i++)
        elegidos[i] = FALSE;    // Empieza que no se ha elegido ningun numero
    
    
    for( i = 0; i < INDIVIDUOS; i++)
    {
        posicion = rand() % posibles+1; // elige al azar una posicion entre los no elegidos (de 1 a INDIVIDUOS)
        j = 0;
        contador = 0;               // cuenta los numeros no elegidos que encuenta.
        
        while(contador < posicion)  // Cuenta las posiciones no elegidas
        {
            if(!elegidos[j++])
                contador++;         // Si el numero ya fue elegido se ignora 
        }
        j--;                        // Cuando encuentra la posicion hace un j++ de mas.
        elegidos[j] = TRUE;         // se marca la posicion como elegida
        posibles--;                 // hay una posicion "no elegida" menos
        a[i] = j+1;                 // La posicion dentro la lista de elegidos es el numero a guardar
    }
}

void ruleta(int indiv[][ALELO+1], int hijo[][ALELO+1], int mayPadre[], int max)
{
    register int i,j,k;
    int rul, acum, dec;
    //guardamos al mas grande
    for( i = 0; i < ALELO; i++)
    {
        indiv[0][i] = mayPadre[i]; 
    }
    //ruleteamos a los demas
    for( i = 1; i < INDIVIDUOS; i++)
    {
        acum = 0;
        rul = rand()%(max+1);
        
        for( j = 0; j < INDIVIDUOS; j++)
        {
            dec = To_decimal(hijo[j]);
            acum += obtenerAptitud(dec);
            if (acum >= rul)
            {
                for( k = 0; k < ALELO; k++)
                    indiv[i][k] = hijo[i][k];  
                break;
            }
        }
    }
}

int torneo(int ganadores[], int indiv1[], int indiv2[], int i1, int i2)
{
    int iflip = flip();
    register int i;

    if(iflip == TRUE)       //si es verdadero entonces gana el de mejor aptitud
    {
        if ( obtenerAptitud(To_decimal(indiv1)) >= obtenerAptitud(To_decimal(indiv2)))
        {
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv1[i];
            
            return i1;
        }else{
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv2[i];

            return i2;
        }
    }else{                  //Si es falso entonces gana el de baja aptitud
        if ( obtenerAptitud(To_decimal(indiv1)) < obtenerAptitud(To_decimal(indiv2)))
        {
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv1[i];
            
            return i1;
        }else{
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv2[i];

            return i2;
        }
    }
}
