#ifndef VERTICE_H
#define VERTICE_H

class Vertice {
private:
    int indice;
    float nx;
    float ny;
    float nz;
public:
    Vertice();
    void asignarIndice(int indice_asignar);
    void asignarNx(float nx_asignar);
    void asignarNy(float ny_asignar);
    void asignarNz(float nz_asignar);
    int obtenerIndice();
    float obtenerNx();
    float obtenerNy();
    float obtenerNz();
    void copiar(Vertice verticeCopiar);
};

#include "vertice.hxx"
#endif // !VERTICE_H

