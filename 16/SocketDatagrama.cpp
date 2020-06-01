#include "SocketDatagrama.h"
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
long double SocketDatagrama::RTO;
long double SocketDatagrama::srtt;
long double SocketDatagrama::rttvar;
long double SocketDatagrama::delta;

long double absoluto(long double valor);

SocketDatagrama::SocketDatagrama(int puertoL) {
  s = socket(AF_INET, SOCK_DGRAM, 0);
  bzero((char *)&direccionLocal, sizeof(struct sockaddr_in));
  bzero((char *)&direccionForanea, sizeof(struct sockaddr_in));

  direccionLocal.sin_family = AF_INET;
  direccionLocal.sin_addr.s_addr = INADDR_ANY;
  direccionLocal.sin_port = htons(puertoL);
  bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
  timeOut = false;
  srtt = 0;
  rttvar = 3;
  RTO = srtt + 2 * rttvar;
}

SocketDatagrama::~SocketDatagrama() { close(s); }

// Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibe(PaqueteDatagrama &p) {
  int retorno;
  socklen_t clilen;  // Ojo no compila si es un tipo int en C
  clilen = sizeof(direccionForanea);
  retorno = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0,
                     (struct sockaddr *)&direccionForanea, &clilen);
  p.inicializaPuerto(ntohs(direccionForanea.sin_port));
  p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));

  return retorno;
}

// Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibeTimeOut(PaqueteDatagrama &p) {
  int retorno;
  socklen_t clilen;  // Ojo no compila si es un tipo int en C
  clilen = sizeof(direccionForanea);
  retorno = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0,
                     (struct sockaddr *)&direccionForanea, &clilen);
  p.inicializaPuerto(ntohs(direccionForanea.sin_port));
  p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
  if (retorno < 0) {
    if (errno == EWOULDBLOCK)
      fprintf(stderr, "Tiempo para recepción transcurrido\n");
    else
      fprintf(stderr, "Error en recvfrom\n");
  }
  return retorno;
}

// Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama &p) {
  int tam;
  direccionForanea.sin_family = AF_INET;
  direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
  direccionForanea.sin_port = htons(p.obtienePuerto());
  tam = sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0,
               (struct sockaddr *)&direccionForanea, sizeof(direccionForanea));
  return tam;
}

void SocketDatagrama::setTimeOut(time_t segundos, suseconds_t microsegundos) {
  timer.tv_sec = segundos;
  timer.tv_usec = microsegundos;
  timeOut = true;
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timer, sizeof(timer));
}

void SocketDatagrama::setTimeOut(timeval RTT) {
  // delta = lalala - srtt;
  //       srtt = srtt + 0.125 * delta;
  //       rttvar = rttvar + 0.25 * (absoluto(delta) - rttvar);
  //       RTO = srtt + 4 * rttvar;
  //       cout << "RTT Medido: " << ceil(lalala) << "s "
  //            << (ceil(lalala) - lalala) * 1000000 << "us delta: " << delta
  //            << " srtt: " << srtt << " rttvar " << rttvar << endl;
  //       cout << "RTO:  " << floor(RTO)
  //            << " micros: " << ceill((RTO - floor(RTO)) * 1000000) << endl;
  //srtt = RTT;
  long double lalala =
            RTT.tv_usec / float(1000000) + RTT.tv_sec;
  delta = lalala - srtt;
  srtt = srtt + 0.125 * delta;
  rttvar = rttvar + 0.25 * (absoluto(delta) - rttvar);
  RTO = srtt + 4 * rttvar;
  cout << RTO << endl;
  timer.tv_sec =floor(RTO);
  timer.tv_usec =ceill((RTO - floor(RTO)) * 1000000);
  timeOut = true;
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timer, sizeof(timer));
}

void SocketDatagrama::unsetTimeOut() {
  timeOut = false;
  setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, NULL, sizeof(timer));
}

void SocketDatagrama::setBroadcast(){
  int yes = 1;
  setsockopt(s, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
}

long double absoluto(long double valor) {
  if (valor >= 0) {
    return valor;
  } else {
    return -valor;
  }
}
