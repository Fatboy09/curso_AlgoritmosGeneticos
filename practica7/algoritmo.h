#ifndef ALGORITMO_H
#define ALGORITMO_H
void setSubCadena(int padre[], int subcad[]);
void crearPoblacion(int a[]);
int buscar(int a[], int num);
void OrderCrossover(int p1[], int p2[], int h[], int subCad[]);
void PartiallyMappedCrossover(int p1[], int p2[], int h[], int ptP1, int pt2P1, int ptP2, int pt2P2);
#endif
