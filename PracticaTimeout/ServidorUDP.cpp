#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <string.h>

#define puertoServer 7100

using namespace std;

int main(int argc, char const *argv[])
{
    SocketDatagrama socketDatagrama(puertoServer);
    
    while(1)
    {
        cout << "Esperando conexión" << endl;
        //Recepción de paquete
        PaqueteDatagrama paqueteDatagrama(2*sizeof(int));
        socketDatagrama.recibe(paqueteDatagrama);

        string ip(paqueteDatagrama.obtieneDireccion());

        cout << "----------" << endl;
        cout << "IP: " << ip << endl;
        cout << "Puerto: " << paqueteDatagrama.obtienePuerto() << endl;
        
        int num[2];
        memcpy((char *)num, paqueteDatagrama.obtieneDatos(),paqueteDatagrama.obtieneLongitud());
        
        int respuesta[1];
        respuesta[0] = num[0] + num[1];
        cout << "res - " << respuesta[0] << endl;

        //Respuesta del paquete
        PaqueteDatagrama paqueteRespuesta(sizeof(int));
        
        paqueteRespuesta.inicializaDatos((char *)&respuesta);
        paqueteRespuesta.inicializaIp(paqueteDatagrama.obtieneDireccion());
        paqueteRespuesta.inicializaPuerto(paqueteDatagrama.obtienePuerto());
        
        socketDatagrama.envia(paqueteRespuesta);
    }
    return 0;
}
