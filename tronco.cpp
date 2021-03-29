#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

using namespace std;


void crearRama(int hj){
	int i = 0;
	for(i = 0; i < hj; i++){
		hijos++;
		cout << "cree al hijo" << hijos << endl;		
	}
}

void initTronco(pid_t nom, int hj){
	nombre = nom;
	cout << "Soy el tronco con nombre: " << nom << endl;
	crearRama(hj);
	sleep(30);
}

void comandoTronco(){

}