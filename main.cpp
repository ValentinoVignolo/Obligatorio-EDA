#include<iostream>
#include<cstring>
#include "Sistema.hpp"
using namespace std;

int main(int argc, char *argv[]) {
	Sistema sis = NULL;
	Cadena aux1 = new char;
	strcpy(aux1,"raiz");
	insertarSistema(sis, crearNodo(aux1));
	
	Cadena palabras = new char[100]; // cadena a leer
	Cadena pal = new char[100];      // donde guardo palabra obtenida actual
	Cadena pal2 = new char[100];
	const char divisor[2] = " ";    // defino lo que divide cada palabra
	
	do {
		gets(palabras); // leer cadena completa
//		cout<<strlwr("HOLA");
		pal = strtok(palabras, divisor); // obtengo la primera palabra
		if (pal != NULL) {
			// verificar comando ingresado y realizar acciï¿½n correspondiente
			if (strcmp(pal, "createfile") == 0) 
			{
				pal = strtok(NULL, divisor);
				// obtener nombre del archivo
				if (pal != NULL) 
				{
					TipoRet ret = CREATEFILE(sis, pal);
					if (ret == OK)
						cout << "El archivo se creo correctamente"<<endl;
					else if (ret == ERROR)
						cout<<"Error:Ya existe un archivo con ese nombre"<<endl;
				}
				else 
				{
					cout << "Error: Falta el nombre del archivo para crear el archivo." << endl;
				}
			} 
			else if (strcmp(pal, "dir") == 0) 
			{
				pal = strtok(NULL, divisor);
				if(pal !=NULL && strcmp(pal,"/s")==0)
				{
						Cadena parametro;
						parametro = pal;
						TipoRet ret = DIR (sis, parametro);
						if(ret==OK)
							cout<<"";
				}
				else
				{
					Cadena parametro = new char;
					strcpy(parametro, "0");
					TipoRet ret = DIR (sis,parametro);
					if(ret==OK)
						cout<<"";
				}
			}
			else if (strcmp(pal, "delete") == 0) 
			{
				pal = strtok(NULL, divisor);
				if (pal != NULL) 
				{
					TipoRet ret = DELETE (sis, pal);
					if(ret == OK)
						cout<<"El Archivo fue Eliminado"<<endl;
					else if(ret == ERROR)
						cout<<"Error: No existe un archivo con ese nombre"<<"\n"<<"      o El archivo es solo de Lectura"<<endl;
				}
				else 
				{
					cout << "Error: Falta el nombre del archivo a eliminar ." << endl;
				}
			}
			else if (strcmp(pal, "iff") == 0) 
			{
				pal = strtok(NULL, divisor);
				pal2 = strtok(NULL, """");
				if (pal != NULL) 
				{
					if(pal2 != NULL)
					{
						if(pal2[0] == '"' && pal2[strlen(pal2) - 1] == '"')
						{
							// Quitar las comillas dobles del principio y del final
							pal2 = pal2 + 1; 
							pal2[strlen(pal2) - 1] = '\0'; 
							
							TipoRet ret = IFF (sis, pal, pal2);
							if(ret == OK)
								cout<<"El texto del archivo fue modificado"<<endl;
							else if(ret == ERROR)
								cout<<"Error:No existe un archivo con ese nombre "<<"\n"<<"    o El archivo es solo de Lectura "<<"\n"<<"    o El texto excede los 55 caracteres"<<endl;
						}
						else
						{
							cout <<"Error: El contenido del archivo debe estar entre comillas dobles."<< endl;
						}
					}
					else
					{
						cout << "Error: Falta el contenido del archivo entre comillas dobles."<< endl;
					}
				}
				else 
				{
					cout << "Error: Falta el nombre del archivo para editarlo." << endl;
				}
				
			}
			else if (strcmp(pal, "type") == 0) 
			{
				pal = strtok(NULL, divisor);
				if (pal != NULL) 
				{
					TipoRet ret = TYPE (sis, pal);
					if(ret == OK)
					{
						cout<<endl;
					}
					else if(ret == ERROR)
						cout<<"Error: No existe un archivo con ese nombre"<<endl;
				}
				else 
				{
					cout << "Error: Falta el nombre del archivo." << endl;
				}
			}
			else if (strcmp(pal, "attrib") == 0) 
			{
				pal = strtok(NULL, divisor);
				pal2 = strtok(NULL, divisor);
				if (pal != NULL) 
				{
					if(pal2 != NULL)
					{
						TipoRet ret = ATTRIB (sis, pal, pal2);
						if(ret == OK)
							cout<<"El archivo se a modificado"<<endl;
						else if(ret == ERROR)
							cout<<"Error: No existe un archivo con ese nombre"<<endl;
					}
					else
					{
						cout << "Error: Falta el parametro +w o -w."<< endl;
					}
				}
				else
				{
					cout<<"Error: falta el nombre del archivo"<<endl;
				}
			}
			else if (strcmp(pal, "mkdir") == 0) 
			{
				pal = strtok(NULL, divisor);
				// obtener nombre del directorio
				if (pal != NULL)
				{
					TipoRet ret = MKDIR(sis, pal);
					if (ret == OK)
						cout << "El Directorio se creo correctamente"<<endl;
					else if (ret == ERROR)
					{
						cout<<"ERROR:Ya existe un Directorio con ese nombre o"<<endl;
						cout<<"		 El nombre del Directorio no puede ser Raiz"<<endl;
					}
				}
				else 
				{
					cout << "Error: Falta el nombre para crear el Directorio." << endl;
				}
			} 
			else if (strcmp(pal, "cd") == 0) 
			{
				pal = strtok(NULL, divisor);
				if(pal != NULL)
				{
					TipoRet ret = CD(sis, pal);
					if(ret == OK)
					{
						Cadena cero = new char;
						strcpy(cero, "0");
						DIR(sis, cero);
					}
					if (ret == ERROR)
						cout << "ERROR DETECTADO, ANALIZAR LA SENTENCIA ANTERIOR" << endl;
				}
				else 
				{
						cout<<"Falta el Nombre del Subdirectorio al que quiere ingresar o el parametro .."<<endl;
				}
			}
			else if (strcmp(pal, "rmdir") == 0) 
			{
				pal = strtok(NULL, divisor);
				if(pal != NULL)
				{
					TipoRet ret = RMDIR(sis, pal);
					if(ret == OK)
						cout<<"El subdirectorio se a eliminado exitosamente"<<endl;
					else if(ret == ERROR)
						cout<<"No existe el subdirectorio a eliminar"<<endl;
					else if (ret == NO_IMPLEMENTADA)
						cout << "NO IMPLEMENTADO"<<endl;
				}
				else 
				{
					cout<<"Error: falta el nombre del subdirectorio a eliminar"<<endl;
				}
			}
			else if (strcmp(pal, "move") == 0) 
			{
				pal = strtok(NULL, divisor);
				pal2 = strtok(NULL, divisor);
				if (pal != NULL) 
				{
					if(pal2 != NULL)
					{
						TipoRet ret = MOVE(sis, pal, pal2);
						if(ret == OK)
							cout<<"Se a movido Correctamente"<<endl;
						if(ret == ERROR)
							cout<<"ERROR: LEER LA SENTENCIA ANTERIOR"<<endl;
					}
					else
					{
						cout << "Error: Falta el directorio destino"<< endl;
					}
				}
				else
				{
					cout<<"Error: falta el nombre del archivo"<<endl;
				}
			}
			else if (strcmp(pal, "destruirsistema") == 0) 
			{
				TipoRet ret = DESTRUIRSISTEMA(sis);
				strcpy(palabras,"exit");
				if (ret == NO_IMPLEMENTADA)
					cout << "NO IMPLEMENTADO"<<endl;
			}
			else if (strcmp(pal, "cls") == 0) 
			{
				system("cls");
			}
			else if (strcmp(pal, "exit") == 0) 
			{
				cout<<"Programa Terminado"<<endl;
			}
			else 
			{
				cout << "Comando no reconocido." << endl;
			}
		}
		
	} while (strcmp(palabras, "exit") != 0);
	
	return 0;
}
