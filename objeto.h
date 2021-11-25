#ifndef OBJETO_H
#define OBJETO_H
#include "cara.h"
#include "vertice.h"
#include <iostream>
using namespace std;

class Objeto {
private:
    string nombre;
    int numVert;
    int numAristas;
    vector<Cara> caras;
    vector<Vertice> vertices;
public:
    Objeto();
    string obtenerNombre();
    int obtenerNumVert();
    vector<Cara>* obtenerCaras();
    vector<Vertice>* obtenerVertices();
    int obtenerNumAristas();
    void asignarNombre(string nombre_asignar);
    void asignarNumVert(int numero_vertices);
    void asignarNumAristas(int numAristas_asignar);
    void asignarCaras(vector<Cara>* caras_asignar);
    void asignarVertices(vector<Vertice>* vertices_asignar);
    void imprimirObjeto();
};

#include "objeto.hxx"
#endif // !OBJETO_H

