#ifndef CAJA_H
#define CAJA_H
#include "objeto.h"
#include "arista.h"
#include "Vertice.h"
#include "Cara.h"
#include "vector"
#include <iostream>
using namespace std;

class Caja {
private:
	string nombre;
	float xMaximo;
	float xMinimo;
	float yMaximo;
	float yMinimo;
	float zMaximo;
	float zMinimo;
	int dimensiones;
	vector<Cara> caras;
	vector<Vertice> vertices;
	vector<Arista> aristas;
public:
	Caja();
	string obtenerNombre();
	float obtenerXMaximo();
	float obtenerXMinimo();
	float obtenerYMaximo();
	float obtenerYMinimo();
	float obtenerZMaximo();
	float obtenerZMinimo();
	int obtenerDimensiones();
	vector<Cara>* obtenerCaras();
	vector<Vertice>* obtenerVertices();
	vector<Arista>* obtenerAristas();
	int obtenerNumVert();
	void asignarNombre(string nombreAsignar);
	void asignarXMaximo(float xMaximoAsignar);
	void asignarXMinimo(float xMinimoAsignar);
	void asignarYMaximo(float yMaximoAsignar);
	void asignarYMinimo(float yMinimoAsignar);
	void asignarZMaximo(float zMaximoAsignar);
	void asignarZMinimo(float zMinimoAsignar);
	void asignarDimensiones(int dimensionesAsignar);
	void asignarCaras(vector<Cara>* carasAsignar);
	void asignarVertices(vector<Vertice>* verticesAsignar);
	void asignarAristas(vector<Arista>* aristasAsignar);
	void calcularCaja();
	void imprimirCaja();
};

#include "caja.hxx"
#endif // !CAJA_H
