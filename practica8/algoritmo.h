#ifndef ALGORITMO_H
#define ALGORITMO_H
void crearPoblacion(int a[]);
int Aptitud(int individ[], int new[], int apt);
void Permutar(int x, int y, int z, int individ[], int lambda[], int aux[],int k);
void Insercion(int indiv[]);
void Desplazamiento(int indiv[]);
void InterReciproco(int indiv[]);
void Heuristico(int indiv[]);
#endif
