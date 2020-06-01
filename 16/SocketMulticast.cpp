#include "SocketMulticast.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <errno.h>
#include <math.h>

using namespace std;
long double SocketMulticast::RTO;
long double SocketMulticast::srtt;
long double SocketMulticast::rttvar;
long double SocketMulticast::delta;

long double absoluto(long double valor);

SocketMulticast::SocketMulticast(int puertoL) {
  s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  bzero((char *)&direccionLocal, sizeof(struct sockaddr_in));
  bzero((char *)&direccionForanea, sizeof(struct sockaddr_in));

  direccionLocal.sin_family = AF_INET;
  direccionLocal.sin_addr.s_addr = INADDR_ANY;
  direccionLocal.sin_port = htons(puertoL);
  bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketMulticast::~SocketMulticast() { close(s); }

// Envía un paquete tipo datagrama desde este socket
int SocketMulticast::envia(PaqueteDatagrama &p, unsigned char TTL) {
  int tam;
  setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&TTL, sizeof(TTL));
  direccionForanea.sin_family = AF_INET;
  direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
  direccionForanea.sin_port = htons(p.obtienePuerto());
  tam = sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0,
               (struct sockaddr *)&direccionForanea, sizeof(direccionForanea));
  return tam;
}

// Recibe un paquete tipo datagrama proveniente de este socket
int SocketMulticast::recibe(PaqueteDatagrama &p, char * ipE) {
  int retorno;
  multicast.imr_multiaddr.s_addr = inet_addr(ipE);
  multicast.imr_interface.s_addr = htonl(INADDR_ANY);
  setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&multicast, sizeof(multicast));
  socklen_t clilen;  // Ojo no compila si es un tipo int en C
  clilen = sizeof(direccionForanea);
  retorno = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0,
                     (struct sockaddr *)&direccionForanea, &clilen);
  p.inicializaPuerto(ntohs(direccionForanea.sin_port));
  p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));

  return retorno;
}

long double absoluto(long double valor) {
  if (valor >= 0) {
    return valor;
  } else {
    return -valor;
  }
}