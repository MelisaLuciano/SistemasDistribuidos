#include "PaqueteDatagrama.hpp"
#include "SocketDatagrama.hpp"
#include "mensaje.h"
#include <inttypes.h>
#include <iostream>
using namespace std;

int puerto = 7300;

int main(void){
    int sum;
    int *datos;
    messageSC mensaje;
    sprintf(mensaje.nombre,"Luciano Espina Melisa");
    PaqueteDatagrama msgclient(100*(sizeof(int)));
    PaqueteDatagrama reply(sizeof(messageSC));
    SocketDatagrama serverAddr(puerto);

    while(1){
        sum = 0;
        serverAddr.recibe(msgclient);
        datos = (int*)msgclient.obtieneDatos();
        for(int x = 0; x < 100; x++){
            cout << datos[x] << endl;
            sum += datos[x];
        }
        mensaje.promedio = sum/100;
        cout << "Nombre: " << mensaje.nombre << "\nEl promedio: " << mensaje.promedio << endl;
        reply.inicializaIp(msgclient.obtieneDireccion());
        reply.inicializaPuerto(msgclient.obtienePuerto());
        reply.inicializaDatos((char*)&mensaje);
        cout << "Enviando mensaje" << endl;
        serverAddr.envia(reply);
    }
}