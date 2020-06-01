#include "Respuesta.h"
#include "Archivo.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>  

using namespace std; 
int enviado,recibido;
int main(int argc, char const *argv[])
{   
    int puertoServer;

    cout << "Puerto: " << endl;
    cin >> puertoServer;
    Respuesta respuesta(puertoServer);


    while(1)
    { 
        mensaje *m = respuesta.getRequest();
        int aux;
        printf("%d %d\n",m->operationId,m->requestId);
        if(m->operationId==OBTENER)
        {
            
        }
        else if(m->operationId==ENVIAR){
            switch(m->requestId){
            case OPEN: recibido=open(m->arguments,O_WRONLY|O_TRUNC|O_CREAT,0666);
            aux=READ;
            break;
            case WRITE: write(recibido,m->data,m->tam);
            aux=WRITE;
            break;
            case CLOSE: close(recibido);
            aux=CLOSE;
            }
        }
        respuesta.sendReply((char*)&aux,m->IP,m->puerto,aux,m->arguments);
    }
    return 0;
}