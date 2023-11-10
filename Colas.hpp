#ifndef COLAS_H
#define COLAS_H
#include "Pila.hpp"
typedef struct nodo
{
	char* dato;
	nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;

struct cola{
	pNodo frente;
	pNodo fondo;
};

void encolar(cola &, pNodo);
pNodo desencolar(cola &);
void mostrarC(cola);
pNodo primero(cola);
pNodo crearNodoC(char*);
void apilarColaEnPila(cola &, Pila &);
void encolarPilaEnCola(Pila &, cola &);
#endif
