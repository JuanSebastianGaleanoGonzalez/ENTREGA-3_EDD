#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <vector>
using namespace std;

struct Comando {
    int indice;
    char* comando;
    char* sintaxis;
};


void generarListaComandosArchivo(vector<Comando>* listaComandos);
Comando generarComando(char* cadena);
int extraerIndiceComando(vector<Comando> listaComandos, string comando);
void menuAyuda(vector<Comando> listaComandos, const char* entradaU);
void imprimirListaAyuda(vector<Comando> lista);
Comando buscarComando(const char* comando, vector<Comando> listaComandos);
int cargar_archivo(list<Objeto>* listaObjetos, char* nombreArchivo);
bool buscarObjeto(list <Objeto> listaObjetos, const char* nombreObjeto);
Objeto encontrarObjeto(list <Objeto> listaObjetos, const char* nombreObjeto);
Vertice generarVertice(char* cadena, int indice);
Cara generarCara(vector<Vertice> vertices, char* cadena);
bool buscarArista(vector<Arista> vectorAristas, Arista arista);
void imprimirListado(list<Objeto> listaObjetos, list<Caja> listaCajas);
int cajaEnvolvente(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* nombreObjeto);
Caja generarCaja(Objeto objeto);
Caja generarCajaListadoObjetos(list<Objeto>* listaObjetos, list<Caja>* listaCajas);
Vertice buscarVertice(vector<Vertice>* vectorVertices, int indice);
int descargarObjeto(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* nombreObjeto);
char* guardarObjeto(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* cadena);
float v_cercano(list<Objeto>* listaObjetos, float x, float y, float z, const char* nombre_objeto, int estado);
float v_cercanoTotal(list<Objeto>* listaObjetos, float x, float y, float z);
void v_cercanos_caja(list<Objeto>* listaObjetos, list<Objeto>* listaCajas, char* nombre_objeto);

#include "funciones.hxx"
#endif
