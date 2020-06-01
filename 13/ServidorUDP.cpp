#include "Respuesta.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

int nbd=0;

int consultar(){
    return nbd;
}

int escribir(int aumento){
    nbd=nbd+1;
    return nbd;
}

int main(int argc, char const *argv[])
{
    Respuesta servidor(7200);
    while(1){
        int solucion,aux;
        mensaje *enviado=servidor.getRequets();
        if(enviado->operationId==1)
        {
            solucion=consultar();
        }
        else if(enviado->operationId==2){
            memcpy(&aux,enviado->arguments,sizeof(int));
            solucion=escribir(aux);
            
        }
        servidor.sendReply((char*)&solucion,enviado->IP,enviado->puerto);
    }
}
