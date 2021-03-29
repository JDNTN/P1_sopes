#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string>
#include <fstream>

using namespace std;

fstream archivo;
FILE *archivoLog;


void crearArchivo(char* direccion){
	archivoLog = fopen(direccion, "wt");
	fclose(archivoLog);
}

void abrirArchivo(char* direccion){
	archivo.open(direccion, ios::in | ios::out);
  	if(archivo.fail()){
	    cout<<"Texto entrada Estructura.txt no existe"<<endl;	    
	    crearArchivo(direccion);
  	}
}

char* leerArchivo(char* direccion){
	char* data;
	char ch;
	abrirArchivo(direccion);
	while(!archivo.eof()){
		archivo >> ch;		
	}
	archivo.close();
	return data;
}

void escribirArchivo(char* direccion, char* mensaje){
	//crearArchivo(direccion);
	abrirArchivo(direccion);
	archivo << mensaje;
    archivo.close();
}
