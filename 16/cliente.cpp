#include "PaqueteDatagrama.h"
#include "SocketMulticast.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <vector>
#include <algorithm>
#include <arpa/inet.h>

using namespace std;

int i = 10; /* Variable compartida */
sem_t mutex1;
sem_t mutex2;
SocketMulticast sckt(8000);
int puerto = 8000;
int suma[2] = {89, 56};
PaqueteDatagrama envia((char *)&suma, sizeof(int) * 2, (char *) "225.1.1.1",
                       puerto);
PaqueteDatagrama recibe(BUFSIZ);
int tam;
std::vector<string> DirIps;

struct menor_magnitud {
  bool operator()(const string &s1, const string &s2) const {
    int num1, num2;
    sscanf(s1.c_str(),"%d.%d.%d.%d", &num1, &num1, &num1, &num1);
    sscanf(s2.c_str(),"%d.%d.%d.%d", &num2, &num2, &num2, &num2);
    return num1 < num2;
  }
};

void *Hilo1(void *);
void *Hilo2(void *);
void *Hilo3(void *);

pthread_t th1; 
pthread_t th2; 
pthread_t th3; 

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    cout << "ingrese" << argv[0] << "puerto" << endl;
    exit(0);
  }

  puerto = atoi(argv[1]);
  envia.inicializaPuerto(puerto);

  sckt.envia(envia);

  // Inicializa los semaforos
  sem_init(&mutex1, 0, 1);
  sem_init(&mutex2, 0, 0);

  // Crea hilos
  pthread_create(&th1, NULL, &Hilo1, NULL);
  pthread_create(&th2, NULL, &Hilo2, NULL);
  pthread_create(&th3, NULL, &Hilo3, NULL);

  // Esperar a que los hilos terminen
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);
}

void *Hilo1(void *) {
  while (true) {
    sem_wait(&mutex1);
    sckt.envia(envia);
    cout << " Enviado " << endl;
    sleep(5);
    sem_post(&mutex2);
  }
  pthread_exit(0);
}

void *Hilo2(void *) {
  while (true) {
    sem_wait(&mutex2);
    sort(DirIps.begin(), DirIps.end(), menor_magnitud());
    std::vector<string>::iterator i;
    for (i = DirIps.begin(); i != DirIps.end(); i++) {
      cout << (*i) << endl;
    }
    DirIps.clear();
    sem_post(&mutex1);
  }
  pthread_exit(0);
}

void *Hilo3(void *) {
  while (true) {
    tam = sckt.recibe(recibe);
    DirIps.push_back(recibe.obtieneDireccion());
  }
  pthread_exit(0);
}