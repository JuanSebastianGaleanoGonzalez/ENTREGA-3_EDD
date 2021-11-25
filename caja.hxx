#include "caja.h"
#include "arista.h"
#include "Vertice.h"
#include "Cara.h"
#include "vector"
#include "funciones.h"
#include <iostream>
using namespace std;

Caja::Caja() {
	this->nombre = "";
	this->xMaximo = 0;
	this->xMinimo= 0;
	this->yMaximo = 0;
	this->yMinimo = 0;
	this->zMaximo = 0;
	this->zMinimo = 0;
}

string Caja::obtenerNombre() {
	return this->nombre;
}

float Caja::obtenerXMaximo() {
	return this->xMaximo;
}

float Caja::obtenerXMinimo() {
	return this->xMinimo;
}

float Caja::obtenerYMaximo() {
	return this->yMaximo;
}

float Caja::obtenerYMinimo() {
	return this->yMinimo;
}
float Caja::obtenerZMaximo() {
	return this->zMaximo;
}

float Caja::obtenerZMinimo() {
	return this->zMinimo;
}

int Caja::obtenerDimensiones() {
	return this->dimensiones;
}

vector<Cara>* Caja::obtenerCaras() {
	return &caras;
}

vector<Vertice>* Caja::obtenerVertices() {
	return &vertices;
}

vector<Arista>* Caja::obtenerAristas() {
	return &aristas;
}

int Caja::obtenerNumVert(){
	return this->vertices.size();
}

void Caja::asignarNombre(string nombreAsignar) {
	this->nombre = nombreAsignar;
}

void Caja::asignarXMaximo(float xMaximoAsignar) {
	this->xMaximo = xMaximoAsignar;
}

void Caja::asignarXMinimo(float xMinimoAsignar) {
	this->xMinimo = xMinimoAsignar;
}

void Caja::asignarYMaximo(float yMaximoAsignar) {
	this->yMaximo = yMaximoAsignar;
}

void Caja::asignarYMinimo(float yMinimoAsignar) {
	this->yMinimo = yMinimoAsignar;
}

void Caja::asignarZMaximo(float zMaximoAsignar) {
	this->zMaximo = zMaximoAsignar;
}

void Caja::asignarZMinimo(float zMinimoAsignar) {
	this->zMinimo = zMinimoAsignar;
}

void Caja::asignarDimensiones(int dimensionesAsignar) {
	this->dimensiones = dimensionesAsignar;
}

void Caja::asignarCaras(vector<Cara>* carasAsignar) {
	this->caras = *carasAsignar;
}

void Caja::asignarVertices(vector<Vertice>* verticesAsignar) {
	this->vertices = *verticesAsignar;
}

void Caja::asignarAristas(vector<Arista>* aristasAsignar) {
	this->aristas = *aristasAsignar;
}

void Caja::calcularCaja() {
	this->dimensiones = 0;
	if (this->xMaximo != this->xMinimo) {
		this->dimensiones++;
	}
	if (this->yMaximo != this->yMinimo) {
		this->dimensiones++;
	}
	if (this->zMaximo != this->zMinimo) {
		this->dimensiones++;
	}
	vector<Vertice> verticesTemporal;
	vector<Cara> carasTemporal;
	vector<Arista> aristasTemporal;
	Vertice auxiliarVertice;
	Arista temporalArista;
	Cara temporalCara;
	int numeroVertices = pow(2, dimensiones);
	vector<int> limites;
	limites.push_back(xMaximo);
	limites.push_back(yMaximo);
	limites.push_back(zMaximo);
	limites.push_back(xMinimo);
	limites.push_back(yMinimo);
	limites.push_back(zMinimo);
	int contador = 0;
	while (contador < numeroVertices) {
		auxiliarVertice.asignarIndice(contador);
		verticesTemporal.push_back(auxiliarVertice);
		contador++;
	}
	if (dimensiones == 2) {
		if (xMaximo == xMinimo) {
			for (int posicion = 0; posicion < verticesTemporal.size(); posicion++) {
				verticesTemporal[posicion].asignarNx(xMaximo);
				if (posicion < (verticesTemporal.size() / 2)) {
					verticesTemporal[posicion].asignarNy(yMinimo);
				}
				else {
					verticesTemporal[posicion].asignarNy(yMaximo);
				}
				if ((posicion + 1) % 2 == 0) {
					verticesTemporal[posicion].asignarNz(zMinimo);
				}
				else {
					verticesTemporal[posicion].asignarNz(zMaximo);
				}
			}
		}
		if (yMaximo == yMinimo) {
			for (int posicion = 0; posicion < verticesTemporal.size(); posicion++) {
				verticesTemporal[posicion].asignarNy(yMaximo);
				if (posicion < (verticesTemporal.size() / 2)) {
					verticesTemporal[posicion].asignarNx(xMinimo);
				}
				else {
					verticesTemporal[posicion].asignarNx(xMaximo);
				}
				if ((posicion + 1) % 2 == 0) {
					verticesTemporal[posicion].asignarNz(zMinimo);
				}
				else {
					verticesTemporal[posicion].asignarNz(zMaximo);
				}
			}
		}
		if (zMaximo == zMinimo) {
			for (int posicion = 0; posicion < verticesTemporal.size(); posicion++) {
				verticesTemporal[posicion].asignarNz(zMaximo);
				if (posicion < (verticesTemporal.size() / 2)) {
					verticesTemporal[posicion].asignarNy(yMinimo);
				}
				else {
					verticesTemporal[posicion].asignarNy(yMaximo);
				}
				if ((posicion + 1) % 2 == 0) {
					verticesTemporal[posicion].asignarNx(xMinimo);
				}
				else {
					verticesTemporal[posicion].asignarNx(xMaximo);
				}
			}
		}
		temporalCara.asignarVertices(verticesTemporal);
		carasTemporal.push_back(temporalCara);
	}
	else if (dimensiones == 3) {
		for (int posicion = 0; posicion < verticesTemporal.size(); posicion++) {
			if (posicion < (verticesTemporal.size() / 2)) {
				verticesTemporal[posicion].asignarNx(xMinimo);
			}
			else {
				verticesTemporal[posicion].asignarNx(xMaximo);
			}
			if ((posicion + 1) % 4 < 3 && (posicion + 1) % 4 != 0) {
				verticesTemporal[posicion].asignarNy(yMinimo);
			}
			else {
				verticesTemporal[posicion].asignarNy(yMaximo);
			}
			if ((posicion + 1) % 2 == 0) {
				verticesTemporal[posicion].asignarNz(zMinimo);
			}
			else {
				verticesTemporal[posicion].asignarNz(zMaximo);
			}
		}
		for (int posicion = 0; posicion < limites.size(); posicion++) {
			temporalCara.obtenerVertices()->clear();
			if ((posicion + 1) % 3 == 1) {
				for (auto iterador = verticesTemporal.begin(); iterador != verticesTemporal.end(); iterador++) {
					if (limites[posicion] == iterador->obtenerNx()) {
						temporalCara.obtenerVertices()->push_back(*iterador);
					}
				}
			}
			else if ((posicion + 1) % 3 == 2) {
				for (auto iterador = verticesTemporal.begin(); iterador != verticesTemporal.end(); iterador++) {
					if (limites[posicion] == iterador->obtenerNy()) {
						temporalCara.obtenerVertices()->push_back(*iterador);
					}
				}
			}
			else if ((posicion + 1) % 3 == 0) {
				for (auto iterador = verticesTemporal.begin(); iterador != verticesTemporal.end(); iterador++) {
					if (limites[posicion] == iterador->obtenerNz()) {
						temporalCara.obtenerVertices()->push_back(*iterador);
					}
				}
			}
			carasTemporal.push_back(temporalCara);
		}
	}

	for (auto iterador = verticesTemporal.begin(); iterador != verticesTemporal.end(); iterador++) {
		for (auto iterador2 = verticesTemporal.begin(); iterador2 != verticesTemporal.end(); iterador2++) {
			if (iterador2->obtenerIndice() != iterador->obtenerIndice()) {
				temporalArista.asignarP1(*iterador);
				temporalArista.asignarP2(*iterador2);
				if ((temporalArista.obtenerP1().obtenerNx() == temporalArista.obtenerP2().obtenerNx() && temporalArista.obtenerP1().obtenerNy() == temporalArista.obtenerP2().obtenerNy()) || (temporalArista.obtenerP1().obtenerNy() == temporalArista.obtenerP2().obtenerNy() && temporalArista.obtenerP1().obtenerNz() == temporalArista.obtenerP2().obtenerNz()) || (temporalArista.obtenerP1().obtenerNz() == temporalArista.obtenerP2().obtenerNz() && temporalArista.obtenerP1().obtenerNx() == temporalArista.obtenerP2().obtenerNx())) {
					if (!buscarArista(aristasTemporal, temporalArista)) {
						aristasTemporal.push_back(temporalArista);
					}
				}
			}
		}
	}

	this->asignarVertices(&verticesTemporal);
	this->asignarAristas(&aristasTemporal);
	this->asignarCaras(&carasTemporal);

	cout << this->vertices.size() << " vertices, " << this->aristas.size() << " aristas y " << this->caras.size() << " caras."<< endl;
}

void Caja::imprimirCaja() {
    cout << this->nombre << " contiene " << this->vertices.size() << " vertices, " << this->aristas.size() << " aristas y " << this->caras.size() << " caras." << endl;
}