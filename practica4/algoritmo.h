#ifndef ALGORITMO_H
#define ALGORITMO_H
int To_decimal(int a[]);
double obtenerAptitud(int x);
double calcularProba(double x, int total);
double calcularEsperanza(int fi, double f);
void cruzar(int p1[], int p2[], int h[], int n);
void mutar(int h[]);
void ruleta(int indiv[][ALELO+1], int hijo[][ALELO+1], int mayPadre[], int max);
int flip();
void barajear(int a[]);
int torneo(int ganadores[], int indiv1[], int indiv2[], int i1, int i2);
#endif
