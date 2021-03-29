#include <iostream>
#include <string>
#include <unistd.h>
#include "archivos.h"

using namespace std;

/*void fun(){	
	escribirArchivo("/home/dntn/Dir1","HOLA \nARCHIVO\n DIR1");
	cout << leerArchivo("/home/dntn/Dir1") << endl;	
}*/

int hijos;
int id;

//COMANDOS

void crearProceso(){
	pid_t nuevo = fork();
	if(nuevo == 0){
		initTronco(getpid(), 5);
	}else if(nuevo < 0){
		cout << "ERROR PTM " << endl;
	}
}

void comandos(){	
	string comando;
	while(true){
		comando = "";
		cout <<"COMANDO: "<< getppid() << " |HIJOS: "<<hijos << "     |Ingrese comando"<<endl;
		cin >> comando;
		if(comando == "p1"){
			crearProceso();
			hijos++;
		}
	}
}

int main(int argc, char *argv[]){
	if(argc >= 2){
		printf("aqui se debe agregar la lectura del archivo %s\n",argv[1]);
	}else{
		printf("aqui inicia el proyecto por medio de comandos\n");		
		comandos();		
	}
}

//FIN COMANDOS

//TRONCO 

void crearRama(int hj){
	int i = 0;
	for(i = 0; i < hj; i++){
		hijos++;
		cout << "cree al hijo" << hijos << endl;		
	}
}

void initTronco(int idTronco, int hj){
	id = idTronco;
	cout << "TRONCO: " << id << "  |HIJOS: " << hijos <<endl << endl;
}

//FIN TRONCO