#include "Sistema.hpp"
#include <iostream>
using namespace std;
bool listaVacia(Archivo lista)
{
	return (lista == NULL);
}
bool SistemaVacia(Sistema sis)
{
	return (sis == NULL);
}
Archivo crearNodoArchivo(Cadena nomb, Cadena txt, bool lect)
{
	Archivo n = new archivo;
	n->nombre = strdup(nomb);
	n->contenido = strdup(txt);
	n->soloLectura = lect;
	n->siguiente = NULL;
	n->anterior = NULL;
	return n;
}
Sistema crearNodo(Cadena nom)
{
	Sistema n = new sistema;
	n->nombre = strdup(nom);
	n->pH = NULL;
	n->sH = NULL;
	n->pPadre = NULL;
	n->Parchivo = NULL;
	return n;
}

void insertarOrdenado(Sistema &s, Archivo nuevo) // insertar nodo ordenado
{
	Archivo aux = NULL;
	
	aux = s->Parchivo;
	if (listaVacia(s->Parchivo))
	{
		nuevo->siguiente = s->Parchivo;
		nuevo->anterior = NULL;
		s->Parchivo = nuevo;
		return;
	}
	while (aux->siguiente && strcmp(aux->siguiente->nombre, nuevo->nombre) < 0)
	{
		aux = aux->siguiente;
	}
	if (aux->siguiente == NULL)
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

void insertarSistema(Sistema &s, Sistema nuevo)
{
	Sistema aux = NULL;
	aux = s;
	if (SistemaVacia(s))
	{
		s = nuevo;
	}
	else if(aux->pH == NULL)
	{
		aux->pH = nuevo;
		nuevo->pPadre = aux; // actualiza el puntero al padre
	}
	else
	{
		if (strcmp(aux->pH->nombre, nuevo->nombre) < 0)
		{
			nuevo->sH = aux->pH;
			aux->pH = nuevo;
			nuevo->pPadre = aux;
		}
		else
		{
			while (aux->sH != NULL && strcmp(aux->sH->nombre, nuevo->nombre) < 0)
			{
				aux = aux->sH;
			}
			if (aux->sH == NULL)
			{
				aux->sH = nuevo;
				nuevo->pPadre = aux;
			}
			else
			{
				nuevo->sH = aux->sH;
				aux->sH = nuevo;
				nuevo->pPadre = aux->pPadre;
			}
		}
	}
}
TipoRet CREATEFILE(Sistema &s, Cadena nombreArchivo)
{
	Archivo aux = s->Parchivo;
	Cadena auxCF = new char, auxCF2 = new char;
	strcpy(auxCF, nombreArchivo);
	strcpy(auxCF2, "");
	while (aux != NULL)
	{
		if (strcmp(aux->nombre, nombreArchivo) == 0)
		{
			return ERROR;
		}
		aux = aux->siguiente;
	}
	if (strlen(nombreArchivo) <= MAX_NOMBREARCHIVO)
	{
		insertarOrdenado(s, crearNodoArchivo(auxCF, auxCF2, false));
		return OK;
	}
	else
	{
		cout << "Error:El Nombre del Archivo solo puede contener 15 caracteres" << endl;
	}
	return NO_IMPLEMENTADA;
}
TipoRet DIR(Sistema &s, Cadena parametro)
{
	
	Archivo aux = s->Parchivo;
	Sistema auxsis = s, auxher=s;
	if (strcmp(parametro, "/s") == 0)
	{
		while(auxsis->sH)
		{
			cout<<auxsis->nombre;
			if(aux!=NULL)	
			{
				cout<<"/"<<aux->nombre;
				aux=aux->siguiente;
			}
			else
			{
				while (auxsis->sH!=NULL && auxher->sH!=NULL)
				{
					cout<<"/"<<auxher->sH;
					auxher=auxher->sH;
				}
				
			}	
		}		
	}
	else
	{
		if(strcmp(parametro, "0")==0)
		{
			while (aux)
			{
				if (aux->soloLectura == 0)
				{
					cout << endl
						<< aux->nombre << "     Lectura/Escritura";
					aux = aux->siguiente;
				}
				else if (aux->soloLectura == 1)
				{
					cout << endl
						<< aux->nombre << "     Lectura";
					aux = aux->siguiente;
				}
			}
			if(auxsis->pH != NULL)
			{	   
				auxsis = auxsis->pH;
				while(auxsis !=NULL)
				{
					cout << endl
						<< auxsis->nombre;
					auxsis = auxsis->sH;
				}
			}		
		}
		cout << endl;
		return OK;
	}
	return NO_IMPLEMENTADA;
}

TipoRet DELETE(Sistema &s, Cadena nombreArchivo)
{
	Archivo aux = NULL;
	Archivo aux2 = NULL;
	aux = s->Parchivo;
	while (aux->siguiente && strcmp(aux->siguiente->nombre, nombreArchivo) != 0)
	{
		aux = aux->siguiente;
	}
	if (aux->siguiente != NULL && aux->siguiente->soloLectura == (false))
	{
		aux2 = aux->siguiente;
		aux->siguiente = aux2->siguiente;
		delete aux2;
		return OK;
	}
	else
																  return ERROR;
}
TipoRet IFF(Sistema &s, Cadena nombreArchivo, Cadena texto)
{
	Archivo aux = NULL;
	aux = s->Parchivo;
	while (aux->siguiente && strcmp(aux->siguiente->nombre, nombreArchivo) != 0)
	{
		aux = aux->siguiente;
	}
	
	if (aux->siguiente != NULL && aux->siguiente->soloLectura == false)
	{
		int nuevoLargo = strlen(aux->siguiente->contenido) + strlen(texto);
		if (nuevoLargo <= TEXTO_MAX)
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

TipoRet TYPE(Sistema &s, Cadena nombreArchivo)
{
	Archivo aux = NULL;
	aux = s->Parchivo;
	while (aux->siguiente && strcmp(aux->siguiente->nombre, nombreArchivo) != 0)
	{
		aux = aux->siguiente;
	}
	
	if (aux->siguiente != NULL)
	{
		if (strcmp(aux->siguiente->contenido, "") != 0)
			cout << aux->siguiente->contenido << endl;
		else
			cout << "El archivo no tiene contenido" << endl;
		return OK;
	}
	else
	{
		return ERROR;
	}
}
TipoRet ATTRIB(Sistema &s, Cadena nombreArchivo, Cadena parametro)
{
	Archivo aux = NULL;
	aux = s->Parchivo;
	while (aux->siguiente && strcmp(aux->siguiente->nombre, nombreArchivo) != 0)
	{
		aux = aux->siguiente;
	}
	
	if (aux->siguiente != NULL)
	{
		if (strcmp(parametro, "-w") == 0)
		{
			aux->siguiente->soloLectura = (true);
			return OK;
		}
		else if (strcmp(parametro, "+w") == 0)
		{
			aux->siguiente->soloLectura = (false);
			return OK;
		}
		else
		{
			cout << "Los parametros validos son +w para lectura y escritura, -w solo para lectursa" << endl;
		}
	}
	else
	{
		return ERROR;
	}
	return NO_IMPLEMENTADA;
}
TipoRet CD(Sistema &s, Cadena nombreDirectorio)
{
	
	if (strcmp(nombreDirectorio, "..") == 0)
	{
		// Ir al directorio padre
		if (s->pPadre != NULL)
		{
			s = s->pPadre;  // Mueve al directorio padre
			return OK;
		}
		else
		{
			cout<< "ERROR: Ya estas en el directorio raiz." << endl;
			return ERROR;
		}
	}
	else
	{
		// Ir al directorio hijo
		if (s->pH != NULL)
		{
			Sistema aux = s->pH;
			while (aux != NULL && strcmp(aux->nombre, nombreDirectorio) != 0)
			{
				aux = aux->sH;
			}
			
			if (aux != NULL)
			{
				s = aux;
				return OK;
			}
			else
			{
				cout << "ERROR: No existe el subdirectorio destino." << endl;
				return ERROR;
			}
		}
		else
		{
			cout << "Error: No hay subdirectorios en el directorio actual." << endl;
		}
	}
	
	
	return NO_IMPLEMENTADA;
}
TipoRet MKDIR (Sistema &s, Cadena nombreDirectorio)
{
	Sistema aux = s;
	Cadena CF = new char;
	strcpy(CF, "Raiz");
	if (nombreDirectorio != CF)
	{ 
		if(aux->pH !=NULL)
		{	
			aux = aux->pH;
			while (aux != NULL)
			{
				if (strcmp(aux->nombre, nombreDirectorio) == 0)
				{
					return ERROR;
				}
				aux = aux->sH;
			}
			insertarSistema(s, crearNodo(nombreDirectorio));
			return OK;
		}
		else
		{
			insertarSistema(s, crearNodo(nombreDirectorio));
			return OK;
		}
	}
	else
	{
		return ERROR;
	}
	return NO_IMPLEMENTADA;
}
TipoRet RMDIR (Sistema &s, Cadena nombreDirectorio)
{
	return NO_IMPLEMENTADA;
}
TipoRet MOVE (Sistema &s, Cadena nombre, Cadena directorioDestino)
{
	return NO_IMPLEMENTADA;
}
TipoRet DESTRUIRSISTEMA(Sistema &s)
{
	return NO_IMPLEMENTADA;
}
