#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#ifndef Solicitud_h_
#define Solicitud_h_

class Solicitud{
	public:
		Solicitud();
		char * doOperation(char *IP,int puerto, int operacionId, char *arguments,int requestId);
	private:
		SocketDatagrama *socketLocal;
};

#endif