#include <iostream>
#include <math.h>
using namespace std;

const double PI = 3.1415926;
int main(){
	int radio;
	double resultado;

	cout << "Ingresa el radio: ";
	cin >> radio;

	resultado = PI * pow(radio,2.0);

	cout << "El área del círculo es: " << to_string(resultado) << "\n";

	//PI = 3.1416;
	//cout << "Modificando el valor de la variable";
}