#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <string.h>

#define puertoCliente 7300
#define puertoServer 7100
using namespace std;

int main(int argc, char const *argv[])
{
    SocketDatagrama socketDatagrama(puertoCliente);

    int num[2];
    num[0] = 6;
    num[1] = 5;

    char ip1[50];

    cout<<"IP:"<<endl;
    cin>>ip1;
    PaqueteDatagrama paqueteDatagrama((char *)num, 2*sizeof(int), (char *)ip1, puertoServer);
    socketDatagrama.envia(paqueteDatagrama);

    cout << "Esperando Respuesta" << endl;

    PaqueteDatagrama paqueteRespuesta(2*sizeof(int));
    socketDatagrama.recibe(paqueteRespuesta);

    int respuesta[paqueteDatagrama.obtieneLongitud()];
    memcpy((char *)respuesta, paqueteRespuesta.obtieneDatos(), paqueteRespuesta.obtieneLongitud());
    cout << respuesta[0] << endl;

    return 0;
}
