#include "Fecha.h"
#include <iostream>
using namespace std;

Fecha::Fecha(int dd, int mm, int aaaa)
{
 mes = mm;
 dia = dd;
 anio = aaaa;
}
void Fecha::inicializaFecha(int dd, int mm, int aaaa)
{
 anio = aaaa;
 mes = mm;
 dia = dd;
 return;
}
void Fecha::muestraFecha()
{
 cout << "La fecha es(dia-mes-año): " << dia << "-" << mes << "-" << anio << endl;
 return;
}
int Fecha::convierte(){
	return anio*10000+mes*100+dia;
}
bool Fecha::leapyr(int anio_actual){
	if(anio_actual % 4 == 0 && anio_actual % 100 != 0)
		return true;
	if(anio_actual % 400 == 0)
		return true;
	return false;
}
