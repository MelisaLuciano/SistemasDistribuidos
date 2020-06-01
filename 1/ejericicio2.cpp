#include <iostream>
using namespace std;

int main(){
	int enteroUno, enteroDos;
	float flotanteUno;
	double resultado;

	cout << "Ingrese dos valores enteros \n";
	cin >> enteroUno >> enteroDos;

	resultado = enteroUno/enteroDos;
	cout << "Division = " << resultado;

	cout << "\nIngrese dos un valor entero y un flotante: \n";
	cin >> enteroUno >> flotanteUno;

	resultado = flotanteUno/enteroUno;
	cout << "Division = " << resultado;

	cout << "\n";
}