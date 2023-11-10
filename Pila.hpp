#ifndef PILA_H
#define PILA_H
#include<string.h>
#include<stdio.h>
struct nodoPila{
	char* dato;
	nodoPila *siguiente;
};
typedef nodoPila *Pila;

Pila crearNodoPila(char*);
void apilar(Pila &, Pila);
Pila cima(Pila);
void mostrarP(Pila);
Pila desapilar(Pila&);
void invertir(Pila &);
#endif
	
