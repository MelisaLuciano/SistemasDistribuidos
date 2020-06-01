#ifndef SOCKETMULTICAST_H_
#define SOCKETMULTICAST_H_

#include "PaqueteDatagrama.h"
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>

class SocketMulticast {
 public:
  SocketMulticast(int);  // puerto local no se podrá cambiar para el proceso. Si
                         // es cero, lo asigna el sistema operativo
  ~SocketMulticast();
  // Envía un paquete tipo datagrama desde este socket
  int envia(PaqueteDatagrama& p, unsigned char TTL);
  int recibe(PaqueteDatagrama &p, char * ipE);

 private:
  struct sockaddr_in direccionLocal;
  struct sockaddr_in direccionForanea;
  struct ip_mreq multicast;
  int s;  // ID socket
  struct timeval timer;
  bool timeOut;
  static long double RTO;
  static long double srtt;
  static long double rttvar;
  static long double delta;
};

#endif