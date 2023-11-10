#include<iostream>
#include<stdio.h>
#include "Colas.hpp"
#include "Pila.hpp"
using namespace std;

pNodo crearNodoC(char* val)
{
	pNodo aux=new tipoNodo;
	if (aux)
	{
		aux->dato=val;
		aux->siguiente=NULL;
		return aux;
	}
}

pNodo primero(cola cab)
{
	return cab.frente;
}

void encolar(cola &cab, pNodo q)
{  
	if (!cab.frente) 
	{
		cab.frente=q;
		cab.fondo=q;
	}
	else 
	{
		cab.fondo->siguiente=q; 
		cab.fondo=q;
	}
}

pNodo desencolar(cola &cab)
{
	if(!cab.frente)
		return NULL;
	pNodo adev=new tipoNodo, aux;
	aux=cab.frente;
	adev->dato=cab.frente->dato;
	adev->siguiente=NULL;
	cab.frente=cab.frente->siguiente;
	delete aux;
	return adev;
}

void mostrarC(cola c)
{
	if(!c.frente)
	{
		cout<<"Cola vacia"<<endl;
	}
	pNodo aux;
	aux = c.frente;
	while(aux)
	{
		cout<<"\t|"<<aux->dato;
		aux = aux->siguiente;
	}
	cout<<endl;
	system("pause");
}
void apilarColaEnPila(cola &c, Pila &p){
	if(!c.frente)
	{
		cout<<"Cola vacia"<<endl;
		system("pause");
	}
	else
	{
		while(c.frente!=NULL)
		{
			apilar(p,crearNodoPila(desencolar(c)->dato));
		}
		mostrarC(c);
		mostrarP(p);
	}
}
	void encolarPilaEnCola(Pila &p, cola &c){
		if(!p)
		{
			cout<<"Pila vacia"<<endl;
			system("pause");
		}
		else
		{
			while(p!=NULL)
			{
				encolar(c, crearNodoC(desapilar(p)->dato));
			}
			mostrarC(c);
			mostrarP(p);
		}
	}
