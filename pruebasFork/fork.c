#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int d = 0;

void padre(int a, int b, int c){
	a = 1;
	b = 2;
	int f[] ={1,2,3};
	printf("padre: Los valores de abc son: %d, %d,%d, %d\n",f[1],f[0],c,d);
	printf("getpid: %d, getpid: %d\n", getppid(), getpid());
}

void main(){
	int a;

	pid_t pr = fork();

	int b;
	int c = 5;

	int e[] = {10,11,12};

	if(pr == 0){
		a = 8;
		b = 9;
		printf("hijo: Los valores de abc son: %d, %d,%d, %d\n",e[1],e[0],e[2],d);
		printf("getpid: %d, getpid: %d\n", getppid(), getpid());
	}else{
		padre(a,b,c);
	}
}