#include "SocketDatagrama.h"
#include <iostream>
using namespace std;

int main(){
	cout << "Este es el servidor UDP con envio y recepcion por datagramas" << endl;
	unsigned int *num;
	SocketDatagrama socket(7200);
	while(true){
		PaqueteDatagrama paquete(sizeof(num)*2);
		if(socket.recibe(paquete)>0){
			cout << "\n\nConexión exitosa" << endl;
			cout << "\tIP cliente: " << paquete.obtieneDireccion() << endl;
			cout << "\tPuerto: " << paquete.obtienePuerto() << endl;
			num = (unsigned int *)paquete.obtieneDatos();
			cout << "\tLos datos recibidos son: " << endl;
			int suma = num[0] + num[1];
			cout << "\t\t" << num[0] << " + " << num[1] << " = " << suma << endl;
		
			PaqueteDatagrama respuesta((char *)&suma, sizeof(int), paquete.obtieneDireccion(), paquete.obtienePuerto());
			socket.envia(respuesta);
		}
		
	}
}
