#include "Sistema.hpp"
#include<iostream>
using namespace std;
bool listaVacia(Archivo lista)
{
	return (lista == NULL);
}

Archivo crearNodoArchivo(Cadena nomb, Cadena txt, bool lect) 
{
	Archivo n=new archivo;
	n->nombre = strdup(nomb);
	n->contenido=strdup(txt);
	n->soloLectura=lect;
	n->siguiente=NULL;
	n->anterior=NULL;
	return n;
}
Sistema crearNodo(Cadena nom)
{
	Sistema n=new sistema;
	n->nombre = strdup(nom);
	n->pH=NULL;
	n->sH=NULL;
	n->Parchivo=NULL;
	return n;
}
void insertarInicio(Sistema &s, Sistema nuevo) //inserta nodo al inicio
{
	if(listaVacia(s))
	{
		nuevo->siguiente = s->Parchivo;
		nuevo->anterior = NULL;
		s->Parchivo = nuevo;	
	}
	else
	{
		nuevo->siguiente = s->Parchivo;
		s->Parchivo->anterior = nuevo;
		nuevo->anterior = NULL;
		s->Parchivo = nuevo;
	} 
}

void insertarOrdenado(Sistema &s, Sistema nuevo) //insertar nodo ordenado
{
	Sistema aux = NULL;
	
	aux = s->Parchivo;
	if(listaVacia(s))
	{
		nuevo->siguiente = s->Parchivo;
		nuevo->anterior = NULL;
		s->Parchivo = nuevo;	
		return;
	}
	while(aux->siguiente && strcmp(aux->siguiente->nombre, nuevo->nombre)< 0)
	{
		aux = aux->siguiente;
	}
	if(aux->siguiente == NULL)
	{
		nuevo->siguiente = aux->siguiente;
		aux->siguiente = nuevo;
		nuevo->anterior = aux;
	}
	else
	{
		nuevo->siguiente = aux->siguiente;
		aux->siguiente->anterior = nuevo;
		aux->siguiente = nuevo;
		nuevo->anterior = aux;
	}
	
} 

Cadena strdup(const Cadena cade) 
{
	if (cade == NULL)
	{
		return NULL;
	}
	int largo = strlen(cade) + 1;
	Cadena nuevo_cade = new char[largo];
	
	if (nuevo_cade != NULL)
	{
		strcpy(nuevo_cade, cade);
	}
	return nuevo_cade;
}

//void insertar ( Directorio&arbol, Directorio Anuevo)
//{
// if (arbol==NULL) // si no hay nada inserta
//	 arbol=Anuevo;
// else
// 	if()
// 	else
// 		if(strcmp(arbol->nombre, Anuevo->nombre)=0);
 }
 TipoRet MKDIR(Sistema &s, Cadena nombreDirectorio)
 {
    Sistema aux=s, Anuevo;
    Anuevo=crearNodo(nombreDirectorio);
    if(aux->pH=NULL)
        aux->pH=Anuevo;
    else 
        if(strcmp(aux->pH->nombre,Anuevo->nombre)<0)
        {
            Anuevo->sH=aux->pH;
            aux->pH=Anuevo;
        }
        else
        {
            while(aux->sH!=NULL && strcmp(aux->sH->nombre,Anuevo->nombre))
                aux=aux->sH;
            if(aux->sH=NULL)
                aux->sH=Anuevo;
            else
            {
                Anuevo->sH=aux->sH;
                aux->sH=Anuevo;
            }
        }
        return NO_IMPLEMENTADA;
 }
TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo)
{
	Sistema aux = s->Parchivo;
	Cadena auxCF=new char, auxCF2=new char;
	strcpy(auxCF, nombreArchivo);
	strcpy(auxCF2,"");
	while (aux != NULL) {
		if (strcmp(aux->nombre, nombreArchivo) == 0 )
		{
			return ERROR;
		}
		aux = aux->siguiente;
	}
	if(strlen(nombreArchivo) <= MAX_NOMBREARCHIVO)
	{
		insertarOrdenado(s,crearNodoArchivo(auxCF,auxCF2,false));
		return OK;
	}
	else
	{
		cout<<"Error:El Nombre del Archivo solo puede contener 15 caracteres"<<endl;
	}
	return NO_IMPLEMENTADA;	
}
TipoRet DIR (Sistema &s, Cadena parametro)
{
	
	Sistema aux=s->Parchivo;
	while(aux)
	{	
//		if(aux->esDirectorio ==(true))
//		{
//			cout<< aux->nombre <<"/";
//			aux = aux->siguiente;
//		}
//		else
//		{ 
			if(aux->soloLectura == 0)
			{
				cout<<endl<< aux->nombre<<"     Lectura/Escritura";
				aux = aux->siguiente;
			}
			else if(aux->soloLectura == 1)
			{
				cout<<endl<< aux->nombre<<"     Lectura";
				aux = aux->siguiente;
			}
//		}
	}
	cout<<endl;
	return OK;
}

TipoRet DELETE (Sistema &s, Cadena nombreArchivo)
{
	Sistema aux=NULL;
	Sistema aux2=NULL;
	aux = s->Parchivo;
	while(aux->siguiente && strcmp(aux->siguiente->nombre,nombreArchivo)!=0)
	{
		aux=aux->siguiente;
	}
	if(aux->siguiente!=NULL && aux->siguiente->soloLectura == (false))
	{
		aux2 = aux->siguiente;
		aux->siguiente = aux2->siguiente;
		delete aux2;
		return OK;
	}
	else
	   return ERROR;	
}
TipoRet IFF (Sistema &s, Cadena nombreArchivo, Cadena texto)
{
	Sistema aux=NULL;
	aux = s->Parchivo;
	while(aux->siguiente && strcmp(aux->siguiente->nombre,nombreArchivo)!=0)
	{
		aux=aux->siguiente;
	}
	
	if (aux->siguiente != NULL && aux->siguiente->soloLectura == false )
	{
		int nuevoLargo = strlen(aux->siguiente->contenido) + strlen(texto);
		if(nuevoLargo <= TEXTO_MAX)	
		{
			Cadena nuevoContenido = new char[nuevoLargo + 1];
			strcpy(nuevoContenido, texto);
			strcat(nuevoContenido, aux->siguiente->contenido);
			delete[] aux->siguiente->contenido;
			aux->siguiente->contenido = nuevoContenido;
			
			return OK;
		}
		else
		{
		   return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

TipoRet TYPE (Sistema &s, Cadena nombreArchivo)
{
	Sistema aux=NULL;
	aux = s->Parchivo;
	while(aux->siguiente && strcmp(aux->siguiente->nombre,nombreArchivo)!=0)
	{
		aux=aux->siguiente;
	}
	
	if (aux->siguiente != NULL )
	{
		if(strcmp(aux->siguiente->contenido, "") !=0)
			cout<<aux->siguiente->contenido<<endl;
		else
			cout<<"El archivo no tiene contenido"<<endl;
		return OK;
	}
	else
	{
		return ERROR;
	}
}
TipoRet ATTRIB (Sistema &s, Cadena nombreArchivo, Cadena parametro)
{
	Sistema aux=NULL;
	aux = s->Parchivo;
	while(aux->siguiente && strcmp(aux->siguiente->nombre,nombreArchivo)!=0)
	{
		aux=aux->siguiente;
	}
	
	if (aux->siguiente != NULL )
	{
		if(strcmp(parametro, "-w")==0)
		{
			aux->siguiente->soloLectura = (true);
			return OK;
		}		
		else if(strcmp(parametro, "+w")==0)
		{
			aux->siguiente->soloLectura = (false);
			return OK;
		}
		else
		{
			cout<<"Los parametros validos son +w para lectura y escritura, -w solo para lectursa"<<endl;
		}
	}
	else
	{
		return ERROR;
	}
	return NO_IMPLEMENTADA;
}
TipoRet CD (Sistema &s, Cadena nombreDirectorio)
{

}
