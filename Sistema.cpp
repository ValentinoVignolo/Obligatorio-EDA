#include "Sistema.hpp"
#include "Pila.hpp"
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
	else if (aux->pH == NULL)
	{
		aux->pH = nuevo;
		nuevo->pPadre = aux; // actualiza el puntero al padre
	}
	else
	{
		aux = aux->pH;
		while (aux->sH != NULL && strcmp(aux->sH->nombre, nuevo->nombre) < 0)
		{
			aux = aux->sH;
		}
		if (aux->sH == NULL)
		{
			aux->sH = nuevo;
			nuevo->pPadre = aux->pPadre;
		}
		else
		{
			nuevo->sH = aux->sH;
			aux->sH = nuevo;
			nuevo->pPadre = aux->pPadre;
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

Sistema sisactaul;
TipoRet DIR(Sistema &s, Cadena parametro)
{
	Pila p = NULL , p2 = NULL;
	Archivo aux = s->Parchivo;
	Sistema auxsis = s;
	Sistema auxpadre = s;
	Cadena parametroS = new char;
	strcpy (parametroS, "/s");
	if (strcmp(parametro, "/s") == 0)
	{
		if (s != NULL)
		{
			if(auxpadre->pPadre != NULL)
			{
				
				while (auxpadre->pPadre != NULL)
				{
					apilar(p, crearNodoPila(auxpadre->pPadre->nombre));
					apilar(p2, crearNodoPila(auxpadre->pPadre->nombre));
					auxpadre = auxpadre->pPadre;
				}
			}
			while (p)
			{
				cout << desapilar(p)->dato << "/";
			}
			cout << auxsis->nombre << "/" << endl;
			if(aux != NULL)
			{
				while (aux != NULL)
				{
						mostrarP(p2);
						cout << auxsis->nombre << "/";
					cout << aux->nombre <<endl;
					aux = aux->siguiente;
				}
			}
			// Llama recursivamente el primer hijos de este sistema
			if (auxsis->pH != NULL)
				DIR(auxsis->pH,parametroS);
			// Llama recursivamente los siguientes hijos de este sistema
			if (auxsis->pH != NULL)
			{
				if (auxsis->pH->sH != NULL)
					DIR(s->pH->sH, parametroS);
			}
		}
		return OK;
	}
	else
	{
		if (strcmp(parametro, "0") == 0)
		{
			while (auxpadre->pPadre != NULL)
			{
				apilar(p, crearNodoPila(auxpadre->pPadre->nombre));
				auxpadre = auxpadre->pPadre;
			}
			while (p)
			{
				cout << desapilar(p)->dato << "/";
			}
			cout << s->nombre << "/" << endl;
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
			if (auxsis->pH != NULL)
			{
				auxsis = auxsis->pH;
				while (auxsis != NULL)
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

TipoRet DELETE(Sistema & s, Cadena nombreArchivo)
{
	Archivo aux = NULL;
	Archivo aux2 = NULL;
	aux = s->Parchivo;
	if(listaVacia(s->Parchivo))
	{
		cout<<"No hay archivos en este directorio"<<endl;
		return NO_IMPLEMENTADA;
	}
	if(strcmp(aux->nombre, nombreArchivo) == 0 && aux->soloLectura == (false))
	{
		s->Parchivo = aux->siguiente;
		delete(aux);
		return OK;
	}
	while (aux->siguiente && strcmp(aux->siguiente->nombre, nombreArchivo) != 0)
	{
		aux = aux->siguiente;
	}
	if (aux->siguiente != NULL && aux->siguiente->soloLectura == (false))
	{
		aux2 = aux->siguiente;
		aux->siguiente = aux2->siguiente;
		if(aux2->siguiente != NULL)
			aux2->siguiente->anterior = aux;
		delete aux2;
		return OK;
	}
	else
																  return ERROR;
}
TipoRet IFF(Sistema & s, Cadena nombreArchivo, Cadena texto)
{
	Archivo aux = NULL;
	aux = s->Parchivo;
	if(listaVacia(s->Parchivo))
	{
		cout<<"No hay archivos en este directorio"<<endl;
		return NO_IMPLEMENTADA;
	}
	if(strcmp(aux->nombre, nombreArchivo) == 0)
	{
		int nuevoLargo = strlen(aux->contenido) + strlen(texto);
		if (nuevoLargo <= TEXTO_MAX)
		{
			Cadena nuevoContenido = new char[nuevoLargo + 1];
			strcpy(nuevoContenido, texto);
			strcat(nuevoContenido, aux->contenido);
			delete[] aux->contenido;
			aux->contenido = nuevoContenido;
			
			return OK;
		}
		else
		{
			return ERROR;
		}
	}
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

TipoRet TYPE(Sistema & s, Cadena nombreArchivo)
{
	Archivo aux = NULL;
	aux = s->Parchivo;
	if(listaVacia(s->Parchivo))
	{
		cout<<"No hay archivos en este directorio"<<endl;
		return NO_IMPLEMENTADA;
	}
	if(strcmp(aux->nombre, nombreArchivo) == 0)
	{
		if (strcmp(aux->contenido, "") != 0)
			cout << aux->contenido << endl;
		else
			cout << "El archivo no tiene contenido" << endl;
		return OK;
	}
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
TipoRet ATTRIB(Sistema & s, Cadena nombreArchivo, Cadena parametro)
{
	Archivo aux = NULL;
	aux = s->Parchivo;
	if(listaVacia(s->Parchivo))
	{
		cout<<"No hay archivos en este directorio"<<endl;
		return NO_IMPLEMENTADA;
	}
	if(strcmp(aux->nombre, nombreArchivo) == 0)
	{
		if (strcmp(parametro, "-w") == 0)
		{
			aux->soloLectura = (true);
			return OK;
		}
		else if (strcmp(parametro, "+w") == 0)
		{
			aux->soloLectura = (false);
			return OK;
		}
		else
		{
			cout << "Los parametros validos son +w para lectura y escritura, -w solo para lectursa" << endl;
		}
	}
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
TipoRet CD(Sistema & s, Cadena nombreDirectorio)
{
	if(strcmp(nombreDirectorio, "raiz") == 0)
	{
		if (s->pPadre != NULL)
		{
			while(s->pPadre != NULL)
			{
				s = s->pPadre;
			}
			return OK;
			
		}
		cout << "ERROR: Ya estas en el directorio raiz." << endl;
		return ERROR;
	}
	else if (strcmp(nombreDirectorio, "..") == 0)
	{
		// Ir al directorio padre
		if (s->pPadre != NULL)
		{
			s = s->pPadre; // Mueve al directorio padre
			return OK;
		}
		else
		{
			cout << "ERROR: Ya estas en el directorio raiz." << endl;
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
				cout << "ERROR: No existe el directorio destino." << endl;
				return ERROR;
			}
		}
		else
		{
			cout << "No hay subdirectorios en el directorio actual." << endl;
		}
	}
	
	return NO_IMPLEMENTADA;
}
TipoRet MKDIR(Sistema & s, Cadena nombreDirectorio)
{
	Sistema aux = s;
	Cadena CF = new char;
	strcpy(CF, "Raiz");
	if (nombreDirectorio != CF)
	{
		if (aux->pH != NULL)
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
TipoRet RMDIR(Sistema & s, Cadena nombreDirectorio)
{
	Sistema auxActual = s;
	Sistema auxSub = s->pH;
	// Si el directorio es el primer hijo
	if (strcmp(auxActual->pH->nombre, nombreDirectorio) == 0)
	{
		s->pH = auxActual->pH->sH;
		DESTRUIRSISTEMA(auxSub);
		return OK;
	}
	// Busca el directorio a eliminar
	while (auxSub->sH != NULL && strcmp(auxSub->sH->nombre, nombreDirectorio) != 0)
	{
		auxSub = auxSub->sH;
	}
	// Elimina todos los archivos y subdirectorios del directorio a eliminar
	if (auxSub->sH != NULL)
	{
		Sistema AuxElim = auxSub->sH;
		auxSub->sH = AuxElim->sH;
		DESTRUIRSISTEMA(AuxElim);
		return OK;
	}
	else
	{
		// No se encontrï¿½ el directorio a eliminar
		return ERROR;
	}
	return NO_IMPLEMENTADA;
}
TipoRet MOVE(Sistema & s, Cadena nombre, Cadena directorioDestino)
{
	Sistema auxcpy = NULL, auxsis = s, auxraiz = s;
	Archivo auxArchivo = s->Parchivo, auxArchivocpy = NULL;
	Cadena raiz = new char;
	strcpy(raiz, "raiz");
	Cadena pal = new char[100];
	const char divisor[2] = "/";
	pal = strtok(directorioDestino,divisor);
	Cadena palabras[20];
	int contador = 0;
	while (pal != NULL)
	{
		palabras[contador++] = pal;
		pal = strtok (NULL, divisor);
	}
	
	if (auxsis->pH != NULL )
	{
		if (strcmp(auxsis->pH->nombre, nombre) == 0)
		{
			if(strcmp(auxraiz->nombre, raiz)!=0)
				CD(auxraiz, raiz);
			for(int i = 1; i < contador; i++)
			{
				if(strcmp(palabras[i-1],auxsis->nombre) == 0 && strcmp(palabras[i],auxsis->pH->nombre) == 0 )
				{
					cout<<"ERROR:No se puede mover a un subdirectorio del origen"<<endl;
					return ERROR;
				}
				TipoRet ret = CD(auxraiz, palabras[i]);
				if (ret == ERROR)
				{
					delete[] raiz;
					delete[] pal;
					return ERROR;
				}
			}	
			auxsis = auxsis->pH;
			s->pH = auxsis->sH;
			auxsis->sH = NULL;
			insertarSistema(auxraiz,auxsis) ;
			delete[] raiz;
			delete[] pal;
			return OK;
		}
		else
		{
			auxsis = auxsis->pH;
			// Busca el directorio a Mover
			while (auxsis->sH != NULL && strcmp(auxsis->sH->nombre, nombre) != 0)
			{
				auxsis = auxsis->sH;
			}
			if (auxsis->sH != NULL)
			{
				auxcpy = auxsis->sH;
				if(strcmp(auxraiz->nombre, raiz)!=0)
					CD(auxraiz, raiz);
				for(int i = 1; i < contador; i++)
				{
					if( strcmp(palabras[i-1],auxcpy->pPadre->nombre) == 0 && strcmp(palabras[i],auxcpy->nombre) == 0 )
					{
						cout<<"ERROR:No se puede mover a un subdirectorio del origen"<<endl;
						return ERROR;
					}
					TipoRet ret = CD(auxraiz, palabras[i]);
					if (ret == ERROR)
					{
						delete[] raiz;
						delete[] pal;
						return ERROR;
					}
				}	
				auxsis->sH = auxcpy->sH;
				auxcpy->sH = NULL;
				insertarSistema(auxraiz,auxcpy) ;
				return OK;
			}
			else if (auxArchivo!=NULL)
			{
				if(strcmp(auxArchivo->nombre,nombre) == 0)
				{
					if(strcmp(auxraiz->nombre, raiz)!=0)
						CD(auxraiz, raiz);
					
					for(int i = 1; i < contador; i++)
					{
						TipoRet ret = CD(auxraiz, palabras[i]);
						if (ret == ERROR)
						{
							delete[] raiz;
							delete[] pal;
							return ERROR;
						}
					}	
					s->Parchivo = auxArchivo->siguiente;
					if (auxArchivo->siguiente != NULL)
						auxArchivo->siguiente->anterior = NULL;
					auxArchivo->siguiente = NULL;
					auxArchivo->anterior = NULL;
					insertarOrdenado(auxraiz,auxArchivo);
					delete[] raiz;
					delete[] pal;
					return OK;
				}
				while(auxArchivo->siguiente !=NULL && strcmp(auxArchivo->siguiente->nombre,nombre) != 0)
				{
					auxArchivo = auxArchivo->siguiente;
				}
				if(auxArchivo->siguiente !=NULL)
				{
					if(strcmp(auxraiz->nombre, raiz)!=0)
						CD(auxraiz, raiz);
					
					for(int i = 1; i < contador; i++)
					{
						TipoRet ret = CD(auxraiz, palabras[i]);
						if (ret == ERROR)
						{
							delete[] raiz;
							delete[] pal;
							return ERROR;
						}
					}	
					auxArchivocpy = auxArchivo->siguiente;
					auxArchivo->siguiente = auxArchivocpy->siguiente;
					if(auxArchivocpy->siguiente != NULL)
						auxArchivocpy->siguiente->anterior = auxArchivo;
					auxArchivocpy->siguiente = NULL;
					auxArchivocpy->anterior = NULL;
					insertarOrdenado(auxraiz,auxArchivocpy);
					delete[] raiz;
					delete[] pal;
					return OK;
				}
				else
				{
					cout<<"ERROR: No existe un subdirectorios o archivos con ese nombre"<<endl;
					delete[] raiz;
					delete[] pal;
					return ERROR;
				}
			}
		}
		
	}
	else if(auxArchivo !=NULL)
	{
		if(strcmp(auxArchivo->nombre,nombre) == 0)
		{
			if(strcmp(auxraiz->nombre, raiz)!=0)
				CD(auxraiz, raiz);
			
			for(int i = 1; i < contador; i++)
			{
				TipoRet ret = CD(auxraiz, palabras[i]);
				if (ret == ERROR)
				{
					delete[] raiz;
					delete[] pal;
					return ERROR;
				}
			}		
			s->Parchivo = auxArchivo->siguiente;
			if (auxArchivo->siguiente != NULL)
				auxArchivo->siguiente->anterior = NULL;
			auxArchivo->siguiente = NULL;
			auxArchivo->anterior = NULL;
			insertarOrdenado(auxraiz,auxArchivo);
			delete[] raiz;
			delete[] pal;
			return OK;
		}
		while(auxArchivo->siguiente !=NULL && strcmp(auxArchivo->siguiente->nombre,nombre) != 0)
		{
			auxArchivo = auxArchivo->siguiente;
		}
		if(auxArchivo->siguiente !=NULL)
		{
			if(strcmp(auxraiz->nombre, raiz)!=0)
				CD(auxraiz, raiz);
			
			for(int i = 1; i < contador; i++)
			{
				TipoRet ret = CD(auxraiz, palabras[i]);
				if (ret == ERROR)
				{
					delete[] raiz;
					delete[] pal;
					return ERROR;
				}
			}	
			auxArchivocpy = auxArchivo->siguiente;
			auxArchivo->siguiente = auxArchivocpy->siguiente;
			if(auxArchivocpy->siguiente != NULL)
				auxArchivocpy->siguiente->anterior =auxArchivo;
			auxArchivocpy->siguiente = NULL;
			auxArchivocpy->anterior = NULL;
			insertarOrdenado(auxraiz,auxArchivocpy);
			delete[] raiz;
			delete[] pal;
			return OK;
		}
		else
		{
			cout<<"ERROR: No existe un subdirectorios o archivos con ese nombre"<<endl;
			delete[] raiz;
			delete[] pal;
			return ERROR;
		}
	}
	else
	{
		cout << "No hay subdirectorios o archivos en este directorio" << endl;
	}
	return NO_IMPLEMENTADA;
}
TipoRet DESTRUIRSISTEMA(Sistema & s)
{
	if (s != NULL)
	{
		// Llama a la funcion para destruir la lista de archivos apuntada por este sistema
		while (s->Parchivo != NULL)
		{
			Archivo auxElim = s->Parchivo;
			s->Parchivo = s->Parchivo->siguiente;
			delete auxElim->nombre;
			delete auxElim->contenido;
			delete auxElim;
		}
		
		// Llama a la funcion para destruir recursivamente los siguientes hijos de este sistema
		if (s->pH != NULL)
		{
			if (s->pH->sH != NULL)
				DESTRUIRSISTEMA(s->pH->sH);
		}
		
		// Llama a la funcion para destruir recursivamente el primer hijos de este sistema
		if (s->pH != NULL)
			DESTRUIRSISTEMA(s->pH);
		
		// Libera la memoria del nodo actual
		delete s;
	}
	// Asigna NULL al puntero del sistema para decirle que ya no hay estructuras validas
	s = NULL;
	return OK;
}
void SistemaActual(Sistema s)
{
	sisactaul = s;
}
