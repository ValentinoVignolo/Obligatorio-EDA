#include "Pila.hpp"
#include<iostream>
#include<string.h>
using namespace std;

Pila crearNodoPila(char* dat)
{
	Pila aux = new nodoPila;
	if (aux)
	{
		aux->dato=dat;
		aux->siguiente=NULL;
		return aux;
	}
	return 0;
}
void apilar(Pila &pila, Pila aux) //insertar al ppio.
{
	aux->siguiente = pila;
	pila = aux;
}
Pila cima(Pila pil)
{
	return (pil);
}

void mostrarP(Pila p)
{
	Pila aux;
	aux = p;
	while(aux)
	{
		cout<<aux->dato<<"/";
		aux = aux->siguiente;
	}
}

Pila desapilar(Pila &p)
{
	Pila aux=NULL, dev=new nodoPila;
	aux=p;
	if(!p) return NULL;
	dev->dato=p->dato;
	dev->siguiente=NULL;
	p=p->siguiente;
	delete(aux);
	return dev;
}

void invertir(Pila &pil)
{
	Pila aux=NULL;
	while(pil)
		apilar(aux, desapilar(pil));
	pil=aux;
}
