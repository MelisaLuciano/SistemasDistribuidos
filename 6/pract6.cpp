
#include "Coordenada.h"
#include <iostream>
#include "math.h"
#include <vector>
#include <algorithm>
using namespace std;

Coordenada::Coordenada(double xx, double yy) : x(xx), y(yy) {
    magnitud = sqrt(x*x + y*y);
}

double Coordenada::obtenerX() {
    return x;
}

double Coordenada::obtenerY() {
    return y;
}

double Coordenada::get_magnitud() {
    return magnitud;
}

PoligonoIrreg::PoligonoIrreg(){}

bool PoligonoIrreg::comparacion(Coordenada a, Coordenada b) {
    if (a.get_magnitud() < b.get_magnitud())
        return true;
    return false;
}

void PoligonoIrreg::anadeVertice(Coordenada c) {
    vertices.push_back(c);
}

void PoligonoIrreg::imprimeVertices() {
    cout << "Vértices: \n";
    for(int i=0; i<vertices.size(); i++){
        cout << "(" << vertices[i].obtenerX() <<", " << vertices[i].obtenerY() << ") = " << vertices[i].get_magnitud() << endl;
    }
}
void PoligonoIrreg::ordenarVertices() {
    sort(vertices.begin(), vertices.end(), comparacion);
}

class Coordenada{
    private:
        double x;
        double y;
        double magnitud;
    public:
        Coordenada( double = 0, double = 0);
        double obtenerX();
        double obtenerY();

        double get_magnitud();
};
class PoligonoIrreg{
    private:
        vector<Coordenada> vertices;
    public:
        PoligonoIrreg();
        
    void anadeVertice(Coordenada);
    void imprimeVertices();

    void ordenarVertices();

    static bool comparacion(Coordenada a, Coordenada b);
};
int main(){
    PoligonoIrreg p;


    p.anadeVertice(Coordenada(5,6));
    p.anadeVertice(Coordenada(1,2));
    //p.imprimeVertices();
    
    p.imprimeVertices();
    p.ordenarVertices();
    cout << "Despues de ordenar" << endl;
    p.imprimeVertices();

    
    return 0;
}