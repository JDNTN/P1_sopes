//
// Created by zofia-px on 3/25/21.
//

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string>
#include <fstream>

using namespace std;

const char *semName = "asdfsd";
const char *second_sem = "jeje";
unsigned int count_readers = 0;
fstream shared_file;
int value;

void open_file(string file_name);
void reader(sem_t *mutex, sem_t *driver);
void write(string command);
void writer(int n, string command, sem_t *driver);
void read();
void print_value(sem_t *semaphore, string name);

void open_file(string file_name) {
    shared_file.open(file_name, ios::in | ios::out);
}

void parent(void){
    sem_t *mutex = sem_open(semName, O_CREAT, 0600, 1);
    sem_t *driver = sem_open(second_sem, O_CREAT, 0600, 1);
    
    if (mutex == SEM_FAILED){
        perror("Parent  : [sem_open] Failed\n"); return;
    }

    writer(1, "testing", driver);
    printf("Parent  : Wait for Child to Print\n");

    /*if (sem_wait(mutex) < 0)
        printf("Parent  : [sem_wait] Failed\n");
    printf("Parent  : Child Printed! \n");

    if (sem_close(mutex) != 0){
        perror("Parent  : [sem_close] Failed\n"); return;
    }

    if (sem_unlink(semName) < 0){
        printf("Parent  : [sem_unlink] Failed\n"); return;
    }*/
}


void child(void) {
    sem_t *mutex = sem_open(semName, O_CREAT, 0600, 1);
    sem_t *driver = sem_open(second_sem, O_CREAT, 0600, 1);
    
    if (mutex == SEM_FAILED || driver == SEM_FAILED ){
        perror("Child   : [sem_open] Failed\n"); return;
    }
    
    reader(mutex, driver);
    
    printf("Child   : I am done! Release Semaphore\n");
    /*if (sem_post(mutex) < 0)
        printf("Child   : [sem_post] Failed \n"); */
}

void print_value(sem_t *semaphore, string name) {
    sem_getvalue(semaphore, &value);
    cout << "valor semaforo " << name << value <<  endl;
}

//Down-wait ; up:signal
void reader(sem_t *mutex, sem_t *driver) {
    cout << "entre al lector" << endl;
    while(true) {
        print_value(mutex, "mutex reader: ");
        sem_wait(mutex); //se convierte en 0
        print_value(mutex, "mutex reader: ");
        count_readers++;
        if(count_readers == 1) {
            print_value(driver, "driver reader: ");
            sem_wait(driver); //se convierte en 0
            print_value(driver, "driver reader: ");
        }
        sem_post(mutex); //se convierte en 1
        print_value(mutex, "mutex reader: ");
        read();
        sem_wait(mutex); //se convierte en 0
        print_value(mutex, "mutex reader: ");
        count_readers--;
        if(count_readers == 0) {
            sem_post(driver); //se convierte en 1
            print_value(driver, "driver reader: ");
        }
        sem_post(mutex); //se convierte en 1
        print_value(mutex, "mutex reader: ");
        sleep(2);
    }
}

void write(string command) {
    open_file("prueba.txt");
    shared_file << command;
    shared_file.close();
    cout << "- Escribi en el archivo, soy el padre" << endl;
    sleep(5);
}

void read() {
    cout << "* Estoy a punto de leer el archivo" << endl;
    open_file("prueba.txt");
    char ch;
    while(!shared_file.eof()) {
        shared_file >> ch;
        cout << "Lei el caracter: " + ch;
    }
    shared_file.close();
    cout << "* Lei el archivo " << endl;
}

void writer(int n, string command, sem_t *driver) {
    while(n != 0) {
        print_value(driver, "driver writer: ");
        sem_wait(driver); //se convierte en 0
        print_value(driver, "driver writer: ");
        write(command);
        sem_post(driver); //se convierte en 1
        print_value(driver, "driver writer: ");
        sleep(2);
        n--;
    }
}

int main(int argc, char *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid < 0){
        perror("fork");
        exit(1);
    }

    if (!pid){
        child();
        printf("Child   : Done with sem_open \n");
    }
    else{
        int status;
        parent();
        wait(&status);
        printf("Parent  : Done with sem_open \n");
    }

    return 0;
}