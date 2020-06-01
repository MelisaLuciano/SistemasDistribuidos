#include <iostream>
#include <vector>
using namespace std;
class Coordenada
{
	private:
	double x;
	double y;
	public:
	Coordenada(double = 0, double = 0);
	double obtenerX();
	double obtenerY();
};

class PoligonoIrreg
{
	private:
		vector<Coordenada> vertice;
	public:
		PoligonoIrreg();
		void anadeVertice(double x, double y);
		void imprime();
};

int main( )
{
	PoligonoIrreg pol1;
	pol1.anadeVertice(3,4);
	pol1.anadeVertice(2,5);
	pol1.anadeVertice(7,5);
	pol1.anadeVertice(8,9);
	pol1.anadeVertice(1,0);
	pol1.anadeVertice(2,-2);
	pol1.imprime();
	return 0;
}

Coordenada::Coordenada(double xx, double yy) : x(xx), y(yy)
{ }

double Coordenada::obtenerX()
{
	return x;
}

double Coordenada::obtenerY()
{
	return y;
}

PoligonoIrreg::PoligonoIrreg()
{

}

void PoligonoIrreg::anadeVertice(double x,double y)
{
	Coordenada nva(x,y);
	vertice.push_back(nva);
}

void PoligonoIrreg::imprime()
{
	int i=0;
	for(i=0;i<vertice.size();i++)
	{
		cout<<vertice[i].obtenerX()<<","<<vertice[i].obtenerY()<<endl;
	}
}
