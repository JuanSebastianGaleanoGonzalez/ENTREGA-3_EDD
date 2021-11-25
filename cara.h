#ifndef CARA_H
#define CARA_H
#include "vertice.h"
#include "arista.h"
#include <vector>
using namespace std;

class Cara {
private:
    int tam;
    vector <Vertice> vertices;
    vector <Arista> aristas;

public:
    Cara();
    int obtenerTam();
    vector <Vertice>* obtenerVertices();
    vector <Arista>* obtenerAristas();
    void asignarTam(int tam_asignar);
    void asignarVertices(vector <Vertice> vertices_asignar);
    void asignarAristas(vector <Arista> aristas_asignar);
};


#include "cara.hxx"
#endif // !CARA_H
