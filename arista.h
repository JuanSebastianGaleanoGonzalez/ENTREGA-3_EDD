#ifndef ARISTA_H
#define ARISTA_H
#include "vertice.h"

class Arista {
private:
    Vertice p1;
    Vertice p2;
public:
    Arista();
    void asignarP1(Vertice p1_asignar);
    void asignarP2(Vertice p2_asignar);
    Vertice obtenerP1();
    Vertice obtenerP2();
};


#include "arista.hxx"
#endif // !ARISTA_H

