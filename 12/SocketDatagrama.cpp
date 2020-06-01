#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

SocketDatagrama::SocketDatagrama(int puerto)
{
    bzero((char *)&direccionLocal, sizeof(puerto));
    socketId = socket(AF_INET, SOCK_DGRAM, 0);
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(puerto);
    bind(socketId, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

int SocketDatagrama::envia(PaqueteDatagrama &paquete)
{
    unsigned int clilen = sizeof(direccionForanea);

    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(paquete.obtieneDireccion());
    direccionForanea.sin_port = htons(paquete.obtienePuerto());

    printf("Enviando a Puerto: %d Direccion IP: %s \n",
        ntohs(((struct sockaddr_in)direccionForanea).sin_port),
        inet_ntoa(((struct sockaddr_in)direccionForanea).sin_addr));

    return sendto(socketId, paquete.obtieneDatos(), paquete.obtieneLongitud(), 0, 
          (struct sockaddr *)&direccionForanea, clilen);
}

int SocketDatagrama::recibe(PaqueteDatagrama &paquete)
{
    unsigned int clilen = sizeof(direccionForanea);
    char * aux = new char[paquete.obtieneLongitud()];

    int r = recvfrom(socketId, aux, paquete.obtieneLongitud(), 0, 
            (struct sockaddr *)&direccionForanea, &clilen);
    
    printf("Remitente: Puerto: %d Direccion IP: %s \n",
        ntohs(((struct sockaddr_in)direccionForanea).sin_port),
        inet_ntoa(((struct sockaddr_in)direccionForanea).sin_addr));

    paquete.inicializaIp(inet_ntoa(((struct sockaddr_in)direccionForanea).sin_addr));
    paquete.inicializaPuerto(ntohs(((struct sockaddr_in)direccionForanea).sin_port));
    paquete.inicializaDatos(aux);

    return r;
}

SocketDatagrama::~SocketDatagrama()
{

}