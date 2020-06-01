#include "PaqueteDatagrama.h"
#include <string.h>
#include <iostream>

using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char* data, unsigned int longitudData, char* direccionIp, int port)
{
    datos=new char[longitudData];
    longitud = longitudData;
    memcpy(datos, data, sizeof(char)*longitudData);
    memcpy(ip, direccionIp, sizeof(char)*16);
    puerto = port;
}
PaqueteDatagrama::PaqueteDatagrama(unsigned int longitudData)
{
    datos = new char[longitudData];
    longitud = longitudData;
}
PaqueteDatagrama::~PaqueteDatagrama()
{
    delete []datos;
}
char* PaqueteDatagrama::obtieneDireccion()
{
    return ip;
}
char* PaqueteDatagrama::obtieneDatos()
{
    return datos;
}
int PaqueteDatagrama::obtienePuerto()
{
    return puerto;
}
unsigned int PaqueteDatagrama::obtieneLongitud()
{
    return longitud;
}
void PaqueteDatagrama::inicializaPuerto(int port)
{
    puerto = port;
}
void PaqueteDatagrama::inicializaIp(char *direccionIp)
{
    memcpy(ip, direccionIp, sizeof(char)*16);
}
void PaqueteDatagrama::inicializaDatos(char *data)
{
    memcpy(datos, data, longitud);
}