#include <iostream>

using namespace std;

int main (){
	/*
	int n; 
	string line; 
	cin >> n; 
	getline(cin, line); 
	cout << "No funciona como se espera debido a que la funcion 'getline'\nlee el salto de linea despues del número ingresado.\n";
	*/
	string cadena("ESCOM"); 
	cout << cadena[6] << endl;
	
	string cadena("ESCOM"); 
	cout << cadena.at(6) << endl; 

	return 0;
}


