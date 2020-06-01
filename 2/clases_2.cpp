#include "Fecha.h"
#include <iostream>
using namespace std;

int main()
{
	Fecha a, b, c(21, 9, 1973);

	b.inicializaFecha(17, 6 , 2000);

	a.muestraFecha();

	cout << a.convierte();
	cout << "\n";
	cout << a.leapyr(2014);
	cout << "\n";

	b.muestraFecha();
	cout << b.convierte();
	cout << "\n";
	cout << b.leapyr(2000);
	cout << "\n";

	c.muestraFecha(); 
	cout << c.convierte();
	cout << "\n";
	cout << c.leapyr(1973);
	cout << "\n";

	int j = 0;
	for(int i = 1; i < 2019; i++)
	{
		if(c.leapyr(i))
		{
			j++;
		}
	}
	cout << j;
}