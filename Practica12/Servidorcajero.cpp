#include "Respuesta.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

int nbd=4;

char *consultar(){
    char *retorno,aux[10];
    sprintf(aux,"%d",nbd);
    retorno=aux;
    return retorno;
}

char *escribir(char *cadena){
    char aux[1]={},aux2[10]={};
    strcpy(aux,cadena);
    int u=atoi(aux);
    nbd=nbd+u;
    sprintf(aux2,"%d",nbd);
    char *retorno=aux2;
    return retorno;
}

int main(int argc, char const *argv[])
{
    Respuesta servidor(7200);
    while(1){
        char cadena[4000];
        mensaje *enviado=servidor.getRequets();
        if(enviado->operationId==1)
        {
            strcpy(cadena,consultar());
        }
        else if(enviado->operationId==2){
            strcpy(cadena,escribir(enviado->arguments));
        }
        servidor.sendReply(cadena,enviado->IP,enviado->puerto);
    }
}
