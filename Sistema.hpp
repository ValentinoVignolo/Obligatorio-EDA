#ifndef SISTEMA_H
#define SISTEMA_H
#include <string.h>
#include <cstring>
#include <stdio.h>
#define MAX_NOMBREARCHIVO 15
#define TEXTO_MAX 55
typedef char* Cadena;
enum retorno{
	OK,
	ERROR,
	NO_IMPLEMENTADA
};
typedef enum retorno TipoRet;

struct archivo
{
	Cadena nombre;
	Cadena contenido;
	bool soloLectura; // si es, sololectura =1, si no soloLectura= 0
	archivo *siguiente;
	archivo *anterior;
};
typedef archivo *Archivo;

struct sistema
{
	Cadena nombre;
	sistema *pH; // apunta al primer hijo
	sistema *sH; //apunta al siguiente hermano
	Archivo Parchivo;//apunta a sus archivos
};
typedef sistema *Sistema;
//
//funciones de listas
Archivo crearNodoArchivo(Cadena,Cadena,bool);
bool listaVacia(Sistema);
void insertarInicio(Sistema &, Sistema);
void insertarOrdenado(Sistema &, Sistema);
Cadena strdup(const Cadena str);
//
// Funciones de arbol
Sistema crearNodo(Cadena);
void insertar (Sistema &, Sistema);
//
//empiezan las funciones del obligatorio
TipoRet CREATEFILE (Sistema &, Cadena);
TipoRet DIR (Sistema &, Cadena);
TipoRet DELETE (Sistema &, Cadena);
TipoRet ATTRIB (Sistema &, Cadena ,Cadena);
TipoRet IFF (Sistema &, Cadena, Cadena);
TipoRet TYPE (Sistema &, Cadena);
TipoRet CD (Sistema &s, Cadena nombreDirectorio);
TipoRet MKDIR (Sistema &s, Cadena nombreDirectorio);
#endif
