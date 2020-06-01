#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#ifndef Respuesta_h_
#define Respuesta_h_

class Respuesta{
	public:
		Respuesta(int p1);
		struct mensaje *getRequets(void);
		char *ordenaCadena(mensaje cadenota);
		void sendReply(char * respuesta, char *ipCliente, int PuertoCliente);
	private:
		SocketDatagrama *socketLocal;
};

#endif