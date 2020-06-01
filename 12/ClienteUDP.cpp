#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <string.h>

#define puertoCliente 7300
#define puertoServer 7100
using namespace std;

int main(int argc, char *argv[]){
    if(argc<3){
    	cout<<"Agregue direccion ip y puerto a la ejecucion"<<endl;
    	return 0;
    }
    Solicitud cliente1;
    int ordenaCadena=0;
    char cadenota[4000]="Nuestra aplicación va a consistir en que el cliente le envíe al servidor una cadena de varias palabras, el servidor las invierte y regresa la cadena conteniendo las palabras en orden inverso. El cliente recibe como parámetro la IP y puerto del servidor y el servidor solo el puerto donde estará atendiendo las solicitudes.\0";
    
    cout<<"La cadena original es:"<<endl<<cadenota<<endl<<endl;
    printf("La respuesta del servidor es: \n%s\n",cliente1.doOperation(argv[1], atoi(argv[2]),ordenaCadena, cadenota));
    return 0;
}
