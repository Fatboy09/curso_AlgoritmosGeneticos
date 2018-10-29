#ifndef ALGORITMO_H
#define ALGORITMO_H
int To_decimal(int a[]);
double obtenerAptitud(int x);
double calcularProba(double x, int total);
double calcularEsperanza(int fi, double f);
void cruzar(int p1[], int p2[], int h[], int n);
void mutar(int h[]);
void ruleta(int indiv[][ALELOS+1], int hijo[][ALELOS+1], int mayPadre[], int max);
void ordenar(int indiv[][ALELOS+1]);
float rankingLineal(int i);
#endif
