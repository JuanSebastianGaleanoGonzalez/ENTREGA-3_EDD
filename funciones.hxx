#define TAMANNO_COMANDO 500
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include "funciones.h"
#pragma warning(disable : 4996)
using namespace std;



void generarListaComandosArchivo(vector<Comando>* listaComandos) {
    char* linea = new char[TAMANNO_COMANDO];

    ifstream entradaArchivo("comandos.txt", ios::in);
    if (!entradaArchivo.is_open()) {
        cout << "Error en la apertura del archivo comandos.txt" << endl;
        system("PAUSE");
        exit(1);
    }
    else {
        while (!entradaArchivo.eof()) {
            entradaArchivo.getline(linea, TAMANNO_COMANDO);
            if ((strcmp(linea, "FINAL") == 0)) {
                break;
            }
            else {
                listaComandos->push_back(generarComando(linea));
                linea = new char[TAMANNO_COMANDO];
            }
        }
    }
    entradaArchivo.close();
    delete linea;
}

Comando generarComando(char* cadena) {
    Comando generado;
    generado.comando = new char[TAMANNO_COMANDO];
    generado.sintaxis = new char[TAMANNO_COMANDO];
    char* token = new char[TAMANNO_COMANDO];
    char* aux = new char[TAMANNO_COMANDO];

    strcpy(aux, cadena);
    token = strtok(aux, "/");
    generado.indice = atoi(token);

    token = strtok(NULL, "/");
    strcpy(generado.comando, token);

    token = strtok(NULL, "/");

    if (token != NULL) {
        while (token != NULL) {
            strcpy(generado.sintaxis, token);
            strcat(generado.sintaxis, " ");
            token = strtok(NULL, "/");
        }
    }
    else {
        strcpy(generado.sintaxis, "");
    }
    delete token;
    delete aux;
    return generado;
}

int extraerIndiceComando(vector<Comando> listaComandos, string comando) {
    int indice = -1;
    Comando auxiliar;
    for (int posicion = 0; posicion < listaComandos.size(); posicion++) {
        auxiliar = listaComandos[posicion];
        if (strcmp(comando.c_str(), auxiliar.comando) == 0) {
            indice = auxiliar.indice;
            break;
        }
    }
    return indice;
}

void menuAyuda(vector<Comando> listaComandos, const char* comando) {
    Comando auxiliar;
    if (strcmp(comando, "") == 0) {
        imprimirListaAyuda(listaComandos);
    }
    else {
        auxiliar = buscarComando(comando, listaComandos);
        if (auxiliar.comando == NULL) {
            cout << "El comando con el nombre solicitado no existe." << endl;
        }
        else {
            cout << endl;
            cout << "Explicacion del comando: ";
            cout << auxiliar.sintaxis << endl;
            cout << endl;
        }
    }
}

void imprimirListaAyuda(vector<Comando> lista) {
    if (lista.empty()) {
        cout << "La lista de comandos no contiene informacion." << endl;
    }
    else {
        Comando auxiliar;
        cout << endl;
        cout << "\tLista de comandos\n" << endl;
        for (int posicion = 0; posicion < lista.size(); posicion++) {
            auxiliar = lista[posicion];
            cout << auxiliar.indice << ". " << auxiliar.comando << endl;
        }
        cout << endl;
    }
}

Comando buscarComando(const char* comando, vector<Comando> listaComandos) {
    Comando auxiliar;
    auxiliar.comando = NULL;
    auxiliar.sintaxis = NULL;
    auxiliar.indice = -1;
    for (int posicion = 0; posicion < listaComandos.size(); posicion++) {
        if (strcmp(comando, listaComandos[posicion].comando) == 0) {
            auxiliar = listaComandos[posicion];
            return listaComandos[posicion];
        }
    }
    return auxiliar;
}

int cargar_archivo(list<Objeto>* listaObjetos, char* nombreArchivo) {
    char* nombreObjeto = new char[TAMANNO_COMANDO];
    char* token = new char[TAMANNO_COMANDO];
    string nombreAsignarObjeto;
    Objeto auxiliar;
    vector<Vertice> temporalVertices;
    vector<Vertice>::iterator iteradorVertices;
    vector<Cara> ::iterator iteradorCaras;
    vector<Arista> ::iterator iteradorAristas;
    vector<Cara> temporalCaras;
    int acumulador = 0;
    int contCaras = 0;

    ifstream entradaNombre(nombreArchivo);
    if (entradaNombre.fail()) {
        return -1;
    }
    else {
        entradaNombre >> nombreAsignarObjeto;
        auxiliar.asignarNombre(nombreAsignarObjeto);
    }
    entradaNombre.close();

    ifstream entradaArchivo(nombreArchivo);
    if (entradaArchivo.fail()) {
        return -1;                                                  //Archivo no existe
    }
    else {
        entradaArchivo.getline(nombreObjeto, TAMANNO_COMANDO);
        if (buscarObjeto(*listaObjetos, auxiliar.obtenerNombre().c_str())) {
            return -2;                                              //Objeto ya existe
        }
        else {
            try {
                entradaArchivo.getline(nombreObjeto, TAMANNO_COMANDO);
                auxiliar.asignarNumVert(atoi(nombreObjeto));
                for (int vertice = 0; vertice < auxiliar.obtenerNumVert(); vertice++) {
                    entradaArchivo.getline(nombreObjeto, TAMANNO_COMANDO);
                    temporalVertices.push_back(generarVertice(nombreObjeto, vertice));
                }

                entradaArchivo.getline(nombreObjeto, TAMANNO_COMANDO);
                while (!(strcmp(nombreObjeto, "-1") == 0)) {
                    auxiliar.obtenerCaras()->push_back(generarCara(temporalVertices, nombreObjeto));
                    entradaArchivo.getline(nombreObjeto, TAMANNO_COMANDO);
                    contCaras++;
                }
            }
            catch (std::exception e) {
                return -3;                                          //Archivo incompleto o ilegible
            }
            for (iteradorCaras = auxiliar.obtenerCaras()->begin(); iteradorCaras != auxiliar.obtenerCaras()->end(); iteradorCaras++) {
                iteradorCaras->obtenerVertices()->erase(iteradorCaras->obtenerVertices()->begin());       
                for (iteradorAristas = iteradorCaras->obtenerAristas()->begin(); iteradorAristas != iteradorCaras->obtenerAristas()->end(); iteradorAristas++) {
                    acumulador++;
                }
            }
            auxiliar.asignarVertices(&temporalVertices);
            auxiliar.asignarNumAristas(acumulador);
        }
        listaObjetos->push_back(auxiliar);
    }

    nombreObjeto = new char[TAMANNO_COMANDO];
    token = new char[TAMANNO_COMANDO];
    delete nombreObjeto;
    delete token;
    return 0;
}

bool buscarObjeto(list <Objeto> listaObjetos, const char* nombreObjeto) {
    list<Objeto>::iterator iterador;
    bool comprobante = false;
    for (iterador = (listaObjetos).begin(); iterador != (listaObjetos).end(); iterador++) {
        if (strcmp(iterador->obtenerNombre().c_str(), nombreObjeto) == 0) {
            comprobante = true;
            break;
        }
    }
    return comprobante;
}

Objeto encontrarObjeto(list <Objeto> listaObjetos, const char* nombreObjeto) {
    list<Objeto>::iterator iteradorList;
    Objeto comprobante;

    for (iteradorList = (listaObjetos).begin(); iteradorList != (listaObjetos).end(); iteradorList++) {
        if (strcmp(iteradorList->obtenerNombre().c_str(), nombreObjeto) == 0) {
            comprobante = *iteradorList;
            break;
        }
    }
    return comprobante;
}


Vertice generarVertice(char* cadena, int indice) {
    Vertice auxiliar;
    char* token = new char[TAMANNO_COMANDO];
    char* aux = new char[TAMANNO_COMANDO];
    auxiliar.asignarIndice(indice);

    strcpy(aux, cadena);
    token = strtok(aux, " ");
    auxiliar.asignarNx(stof(token));
    token = strtok(NULL, " ");
    auxiliar.asignarNy(stof(token));
    token = strtok(NULL, " ");
    auxiliar.asignarNz(stof(token));
    token = new char[TAMANNO_COMANDO];
    delete aux;
    delete token;
    return auxiliar;
}


Cara generarCara(vector<Vertice> vertices, char* cadena) {
    Cara auxiliar;
    vector<Vertice>::iterator iterador;
    vector<Vertice>::iterator iterador2;
    vector<Vertice> verticesCara;
    char* token = new char[TAMANNO_COMANDO];
    char* aux = new char[TAMANNO_COMANDO];

    strcpy(aux, cadena);
    token = strtok(aux, " ");
    auxiliar.asignarTam(atoi(token));
    
    Vertice copia;

    for (int cantVertices = 0; cantVertices <= auxiliar.obtenerTam(); cantVertices++) {
        copia = buscarVertice(&vertices, atoi(token));
        if (copia.obtenerIndice() != -1) {
            verticesCara.push_back(copia);
        }
        token = strtok(NULL, " ");
    }
    auxiliar.asignarVertices(verticesCara);
    vector<Arista> temporalAristas;
    Arista temporal;
    for (iterador = verticesCara.begin(); iterador != verticesCara.end(); iterador++) {
        for (iterador2 = verticesCara.begin(); iterador2 != verticesCara.end(); iterador2++) {
            if (iterador != iterador2) {
                temporal.asignarP1(*iterador);
                temporal.asignarP2(*iterador2);
                if (!buscarArista(temporalAristas, temporal)) {
                    temporalAristas.push_back(temporal);
                }
            }
        } 
    }
    temporalAristas.erase(temporalAristas.begin());
    auxiliar.asignarAristas(temporalAristas);
    token = new char[TAMANNO_COMANDO];
    delete aux;
    delete token;
    return auxiliar;
}

Vertice buscarVertice(vector<Vertice>* vectorVertices, int indice) {
    vector<Vertice>::iterator iterador;
    Vertice auxiliar;
    auxiliar.asignarIndice(-1);
    for (iterador = vectorVertices->begin(); iterador != vectorVertices->end(); iterador++) {
        if (indice == iterador->obtenerIndice()) {
            auxiliar = *iterador;
        }
    }
    return auxiliar;
}

bool buscarArista(vector<Arista> vectorAristas, Arista arista) {
    bool comprobante = false;
    vector<Arista>::iterator iterador;
    for (iterador = vectorAristas.begin(); iterador != vectorAristas.end(); iterador++) {
        if ((arista.obtenerP1().obtenerIndice() == iterador->obtenerP1().obtenerIndice()) && (arista.obtenerP2().obtenerIndice() == iterador->obtenerP2().obtenerIndice())) {
            comprobante = true;
        }
    }

    for (iterador = vectorAristas.begin(); iterador != vectorAristas.end(); iterador++) {
        if ((arista.obtenerP2().obtenerIndice() == iterador->obtenerP1().obtenerIndice()) && (arista.obtenerP1().obtenerIndice() == iterador->obtenerP2().obtenerIndice())) {
            comprobante = true;
        }
    }
    return comprobante;
}

void imprimirListado(list<Objeto> listaObjetos, list<Caja> listaCajas) {
    list<Objeto>::iterator iterador;
    list<Caja>::iterator iteradorC;
    cout << "Hay " << listaObjetos.size() << " objetos en memoria." << endl;
    for (iterador = listaObjetos.begin(); iterador != listaObjetos.end(); iterador++) {
        iterador->imprimirObjeto();
    }
    cout<<endl;
    cout << "Hay " << listaCajas.size() << " cajas envolventes en memoria." << endl;
    for (iteradorC = listaCajas.begin(); iteradorC != listaCajas.end(); iteradorC++) {
        iteradorC->imprimirCaja();
    }
    cout << endl;
}

int cajaEnvolvente(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* nombreObjeto) {
    list<Objeto>::iterator iteradorObjetos;
    int retorno = 0;
    if (strcmp(nombreObjeto, "") == 0) {
        if (listaObjetos->empty()) {
            retorno = 1;
        }
        else {
            listaCajas->push_back(generarCajaListadoObjetos(listaObjetos, listaCajas));
            retorno = 2;
        }   
    }
    else {
        if (!buscarObjeto(*listaObjetos, (const char*) nombreObjeto)) {
            retorno = 3;
        }
        else {
            for (iteradorObjetos = listaObjetos->begin(); iteradorObjetos != listaObjetos->end(); iteradorObjetos++) {
                if (strcmp(nombreObjeto, iteradorObjetos->obtenerNombre().c_str()) == 0) {
                    listaCajas->push_back(generarCaja(*iteradorObjetos));
                    retorno = 4;
                }
            }
        }
    }
    return retorno;
}

Caja generarCaja(Objeto objeto) {
    Caja auxiliar;
    float xMax = 0;
    float yMax = 0;
    float zMax = 0;
    float xMin, yMin, zMin;
    vector<Cara>::iterator iteradorCaras;
    vector<Vertice>::iterator iteradorVertices;

    for (iteradorCaras = objeto.obtenerCaras()->begin(); iteradorCaras != objeto.obtenerCaras()->end(); iteradorCaras++) {
        for (iteradorVertices = iteradorCaras->obtenerVertices()->begin(); iteradorVertices != iteradorCaras->obtenerVertices()->end(); iteradorVertices++) {
            if (iteradorVertices->obtenerNx() > xMax) {
                xMax = iteradorVertices->obtenerNx();
            }
            if (iteradorVertices->obtenerNy() > yMax) {
                yMax = iteradorVertices->obtenerNy();
            }
            if (iteradorVertices->obtenerNz() > zMax) {
                zMax = iteradorVertices->obtenerNz();
            }
        }
    }
    xMin = xMax;
    yMin = yMax;
    zMin = zMax;

    for (iteradorCaras = objeto.obtenerCaras()->begin(); iteradorCaras != objeto.obtenerCaras()->end(); iteradorCaras++) {
        for (iteradorVertices = iteradorCaras->obtenerVertices()->begin(); iteradorVertices != iteradorCaras->obtenerVertices()->end(); iteradorVertices++) {
            if (iteradorVertices->obtenerNx() < xMin) {
                xMin = iteradorVertices->obtenerNx();
            }
            if (iteradorVertices->obtenerNy() < yMin) {
                yMin = iteradorVertices->obtenerNy();
            }
            if (iteradorVertices->obtenerNz() < zMin) {
                zMin = iteradorVertices->obtenerNz();
            }
        }
    }

    char* nombreObjeto = new char[TAMANNO_COMANDO];
    strcpy(nombreObjeto, "Caja");
    auxiliar.asignarNombre(strcat(nombreObjeto, objeto.obtenerNombre().c_str()));
    auxiliar.asignarXMaximo(xMax);
    auxiliar.asignarXMinimo(xMin);
    auxiliar.asignarYMaximo(yMax);
    auxiliar.asignarYMinimo(yMin);
    auxiliar.asignarZMaximo(zMax);
    auxiliar.asignarZMinimo(zMin);
    auxiliar.calcularCaja();
    return auxiliar;
    delete nombreObjeto;
}

Caja generarCajaListadoObjetos(list<Objeto>* listaObjetos, list<Caja>* listaCajas) {
    Caja auxiliar;
    list<Objeto>::iterator iteradorObjetos = listaObjetos->begin();
    vector<Cara>::iterator iteradorCaras;
    vector<Vertice>::iterator iteradorVertices;
    
    float xMax = 0;
    float yMax = 0;
    float zMax = 0;
    float xMin, yMin, zMin;
    auxiliar.asignarNombre("Envolvente_Objetos_Memoria");

    for (iteradorObjetos = listaObjetos->begin(); iteradorObjetos != listaObjetos->end(); iteradorObjetos++) {
        for (iteradorCaras = iteradorObjetos->obtenerCaras()->begin(); iteradorCaras != iteradorObjetos->obtenerCaras()->end(); iteradorCaras++) {
            for (iteradorVertices = iteradorCaras->obtenerVertices()->begin(); iteradorVertices != iteradorCaras->obtenerVertices()->end(); iteradorVertices++) {
                if (iteradorVertices->obtenerNx() > xMax) {
                    xMax = iteradorVertices->obtenerNx();
                }
                if (iteradorVertices->obtenerNy() > yMax) {
                    yMax = iteradorVertices->obtenerNy();
                }
                if (iteradorVertices->obtenerNz() > zMax) {
                    zMax = iteradorVertices->obtenerNz();
                }
            }
        }
    }
    xMin = xMax;
    yMin = yMax;
    zMin = zMax;

    for (iteradorObjetos = listaObjetos->begin(); iteradorObjetos != listaObjetos->end(); iteradorObjetos++) {
        for (iteradorCaras = iteradorObjetos->obtenerCaras()->begin(); iteradorCaras != iteradorObjetos->obtenerCaras()->end(); iteradorCaras++) {
            for (iteradorVertices = iteradorCaras->obtenerVertices()->begin(); iteradorVertices != iteradorCaras->obtenerVertices()->end(); iteradorVertices++) {
                if (iteradorVertices->obtenerNx() < xMin) {
                    xMin = iteradorVertices->obtenerNx();
                }
                if (iteradorVertices->obtenerNy() < yMin) {
                    yMin = iteradorVertices->obtenerNy();
                }
                if (iteradorVertices->obtenerNz() < zMin) {
                    zMin = iteradorVertices->obtenerNz();
                }
            }
        }
    }

    auxiliar.asignarXMaximo(xMax);
    auxiliar.asignarXMinimo(xMin);
    auxiliar.asignarYMaximo(yMax);
    auxiliar.asignarYMinimo(yMin);
    auxiliar.asignarZMaximo(zMax);
    auxiliar.asignarZMinimo(zMin);
    auxiliar.calcularCaja();
    return auxiliar;
}


int descargarObjeto(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* nombreObjeto) {
    int retorno = 1;
    bool objeto = false;
    list<Caja>::iterator iteradorCajas;
    for (auto iterador = listaObjetos->begin(); iterador != listaObjetos->end(); iterador++) {
        if (strcmp(nombreObjeto, iterador->obtenerNombre().c_str()) == 0) {
            listaObjetos->erase(iterador);
            objeto = true;
            retorno = 2;
            break;
        }
    }

    if(!objeto){
        for (iteradorCajas = listaCajas->begin(); iteradorCajas != listaCajas->end(); iteradorCajas++) {
            if (strcmp(nombreObjeto, iteradorCajas->obtenerNombre().c_str()) == 0) {
                listaCajas->erase(iteradorCajas);
                retorno = 3;
                break;
            }
        }
    }
    return retorno;
}

char* guardarObjeto(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* cadena) {
    char* retorno = new char[TAMANNO_COMANDO];
    char* nombreObjeto = new char[TAMANNO_COMANDO];
    char* nombreArchivo = new char[TAMANNO_COMANDO];
    bool esta = false;
    Objeto guardar;
    Caja guardarC;
    list<Caja>::iterator iteraCaja;
    vector<Cara>::iterator iteraCara;
    vector<Vertice>::iterator iteraVert;

    guardar.asignarNombre("NULL");
    nombreObjeto = strtok(cadena, " ");
    nombreArchivo = strtok(NULL, " \0");
    if (nombreArchivo == NULL) {
        strcpy(retorno, "Los parametros recibidos en el comando no son validos. ");
    }
    else {
        for (auto iterador = listaObjetos->begin(); iterador != listaObjetos->end(); iterador++) {
            if (strcmp(iterador->obtenerNombre().c_str(), nombreObjeto) == 0) {
                guardar = *iterador;
                esta = true;
                break;
            }
        }

        if(esta){
            if (strcmp(guardar.obtenerNombre().c_str(), "NULL") == 0) {
                strcpy(retorno, "El objeto ");
                strcat(retorno, nombreObjeto);//Objeto no existe
                strcat(retorno, " no ha sido cargado en memoria. ");
            }   
            else {
                ofstream salidaArchivo;
                salidaArchivo.open(nombreArchivo);
                if (!salidaArchivo.is_open()) {
                    strcpy(retorno, "Error en la creacion del archivo ");
                    strcat(retorno, nombreArchivo);                                        //Error en la creacion del archivo
                }
                else {
                    strcpy(retorno, "La informacion del objeto ");
                    strcat(retorno, nombreObjeto);
                    strcat(retorno, " ha sido guardada exitosamente en el archivo ");
                    strcat(retorno, nombreArchivo);
                    salidaArchivo << guardar.obtenerNombre() << endl;
                    salidaArchivo << guardar.obtenerNumVert() << endl;
                    for (auto iterador = guardar.obtenerVertices()->begin(); iterador != guardar.obtenerVertices()->end(); iterador++) {
                        salidaArchivo << iterador->obtenerNx() << " " << iterador->obtenerNy() << " " << iterador->obtenerNz() << endl;
                    }
                    for (auto iterador = guardar.obtenerCaras()->begin(); iterador != guardar.obtenerCaras()->end(); iterador++) {
                        salidaArchivo << iterador->obtenerTam();
                        for (auto iterador2 = iterador->obtenerVertices()->begin(); iterador2 != iterador->obtenerVertices()->end(); iterador2++) {
                            salidaArchivo << " " << iterador2->obtenerIndice();
                        }
                        salidaArchivo << endl;
                                                                       }
                    salidaArchivo << "-1";
                }
            }
        }else{
            for (iteraCaja = listaCajas->begin(); iteraCaja != listaCajas->end(); iteraCaja++) {
                if (strcmp(iteraCaja->obtenerNombre().c_str(), nombreObjeto) == 0) {
                    guardarC = *iteraCaja;
                    break;
                }
            }
            if (strcmp(guardarC.obtenerNombre().c_str(), "NULL") == 0) {
                strcpy(retorno, "El objeto caja envolvente ");
                strcat(retorno, nombreObjeto);//Objeto no existe
                strcat(retorno, " no ha sido cargado en memoria. ");
            }   
            else {
                ofstream salidaArchivo;
                salidaArchivo.open(nombreArchivo);
                if (!salidaArchivo.is_open()) {
                    strcpy(retorno, "Error en la creacion del archivo ");
                    strcat(retorno, nombreArchivo);                                        //Error en la creacion del archivo
                }
                else {
                    strcpy(retorno, "La informacion del objeto ");
                    strcat(retorno, nombreObjeto);
                    strcat(retorno, " ha sido guardada exitosamente en el archivo ");
                    strcat(retorno, nombreArchivo);
                    salidaArchivo << guardarC.obtenerNombre() << endl;
                    salidaArchivo << guardarC.obtenerNumVert() << endl;
                    for (iteraVert = guardarC.obtenerVertices()->begin(); iteraVert!= guardarC.obtenerVertices()->end(); iteraVert ++) {
                        salidaArchivo << iteraVert->obtenerNx() << " " << iteraVert->obtenerNy() << " "<< iteraVert->obtenerNz() << endl;
                    }
                    for (iteraCara = guardarC.obtenerCaras()->begin(); iteraCara != guardarC.obtenerCaras()->end(); iteraCara++) {
                        salidaArchivo << iteraCara->obtenerTam();
                        for (iteraVert = iteraCara->obtenerVertices()->begin(); iteraVert != iteraCara->obtenerVertices()->end(); iteraVert++) {
                            salidaArchivo << " " << iteraVert->obtenerIndice();
                        }
                        salidaArchivo << endl;
                    }
                    salidaArchivo << "-1";
                }
            }
        }
    }
    return retorno;
}

float v_cercanoTotal(list<Objeto>* listaObjetos, float x, float y, float z){
    float distanciaMinima = 1000;
    float sa;
    float xc;
    float yc;
    float zc;
    int indice;
    const char* nombre = NULL;
    const char* nombreAux = NULL;
    list<Objeto>:: iterator iteradorObjeto;

    for(iteradorObjeto =(listaObjetos)->begin();iteradorObjeto!=(listaObjetos)->end();iteradorObjeto++){
        nombreAux = iteradorObjeto->obtenerNombre().c_str(); 
        sa = v_cercano(listaObjetos,x,y,z,nombreAux, 1);
        if(sa <= distanciaMinima){
            distanciaMinima = sa;
            nombre = iteradorObjeto->obtenerNombre().c_str();
        }
    }
    return v_cercano(listaObjetos,x,y,z,nombre, 0);
}

float v_cercano(list<Objeto>* listaObjetos, float x, float y, float z, const char* nombre_objeto, int estado){
    Objeto objetoActual;
    float distanciaMinima = 1000;
    float sa;
    float xc;
    float yc;
    float zc;
    int indice;
    vector<Vertice>::iterator iteradorVertices;
    
    if(!buscarObjeto(*listaObjetos, nombre_objeto)){
        cout<<" el objeto no ha sido cargado en memoria"<<endl;
        return 0;
    }

    objetoActual = encontrarObjeto(*listaObjetos, nombre_objeto);

    for(iteradorVertices = objetoActual.obtenerVertices()->begin(); iteradorVertices != objetoActual.obtenerVertices()->end(); iteradorVertices++){
        sa= sqrt(pow(x-iteradorVertices->obtenerNx(),2)+pow(y-iteradorVertices->obtenerNy(),2)+pow(z-iteradorVertices->obtenerNz(),2));
        if(sa <= distanciaMinima){
            distanciaMinima = sa;
            xc = iteradorVertices->obtenerNx();
            yc = iteradorVertices->obtenerNy();
            zc = iteradorVertices->obtenerNz();
            indice = iteradorVertices->obtenerIndice();
        } 
    }

    if(estado == 0){
        cout<<"El vertice "<<indice<<" ("<<xc<<", "<<yc<<", "<<zc<<") del objeto "<<nombre_objeto<<" es el mas cercano al punto ("<<x<<", "<<y<<", "<<z<<"), ";
    }
    
    return distanciaMinima;
}



void v_cercanos_caja(list<Objeto>* listaObjetos, list<Caja>* listaCajas, char* nombre_objeto){
    Objeto objetoAct;
    Caja cajaAct;
    bool estaCaja = false;
    list<Caja>:: iterator iteradorCajas;
    vector<Vertice>::iterator iteradorVertices;
    vector<Vertice>::iterator iteradorVertices2;
    char * copiaNombre = new char[100];
    char * copiaNCaja = new char[100];
    char * tok = new char[50];
    float distanciaMinima = 1000;
    float sa;
    float xc;
    float yc;
    float zc;
    int indice;

    if(!buscarObjeto(*listaObjetos, nombre_objeto)){
        cout<<" el objeto no ha sido cargado en memoria"<<endl;
        return;
    }
    cout<<"hola2"<<endl;

    objetoAct = encontrarObjeto(*listaObjetos, nombre_objeto);
    strcpy(copiaNombre, "Caja");
    strcat(copiaNombre, objetoAct.obtenerNombre().c_str());

    cout<<"hola3"<<endl;

    if(!listaCajas->empty()){
        for(iteradorCajas = listaCajas->begin(); iteradorCajas != listaCajas->end(); iteradorCajas++){
            cout<<"hola4"<<endl;
            strcpy(copiaNCaja, "Caja");
            strcat(copiaNCaja, iteradorCajas->obtenerNombre().c_str());
        
            if(strcmp(copiaNCaja, copiaNombre) == 0){
                estaCaja = true;
                cajaAct = *iteradorCajas;
            }
        }
    }
    

    cout<<endl;
    cout<<"Los vertices del objeto "<<objetoAct.obtenerNombre()<<" mas cercanos a las esquinas de su caja envolvente son:"<<endl;
    cout<<"Esquina              Vertice                 Distancia"<<endl;
    if(estaCaja){
        for(iteradorVertices2 = cajaAct.obtenerVertices()->begin(); iteradorVertices2 != cajaAct.obtenerVertices()->end(); iteradorVertices2++){
            for(iteradorVertices = objetoAct.obtenerVertices()->begin(); iteradorVertices != objetoAct.obtenerVertices()->end(); iteradorVertices++){
                sa= sqrt(pow(iteradorVertices2->obtenerNx()-iteradorVertices->obtenerNx(),2)+pow(iteradorVertices2->obtenerNy()-iteradorVertices->obtenerNy(),2)+pow(iteradorVertices2->obtenerNz()-iteradorVertices->obtenerNz(),2));
                if(sa <= distanciaMinima){
                    distanciaMinima = sa;
                    xc = iteradorVertices->obtenerNx();
                    yc = iteradorVertices->obtenerNy();
                    zc = iteradorVertices->obtenerNz();
                    indice = iteradorVertices->obtenerIndice();
                } 
            }
            cout<<iteradorVertices2->obtenerIndice()+1<<" ("<<iteradorVertices2->obtenerNx()<<", "<<iteradorVertices2->obtenerNy()<<", "<<iteradorVertices2->obtenerNz()<<")    ";
            cout<<indice+1<<" ("<<xc<<", "<<yc<<", "<<zc<<")    ";
            cout<<distanciaMinima<<endl;
        }
    }else{
        int res = cajaEnvolvente(listaObjetos, listaCajas, copiaNombre);
        for(iteradorCajas == listaCajas->begin(); iteradorCajas!= listaCajas->end(); iteradorCajas++){
            strcpy(copiaNCaja, iteradorCajas->obtenerNombre().c_str());
            tok = strtok(copiaNCaja, "M");
            tok = strtok(NULL, " ");
            if(strcmp(tok, copiaNombre) == 0){
                cajaAct = *iteradorCajas;
            }
        }
        for(iteradorVertices2 = cajaAct.obtenerVertices()->begin(); iteradorVertices2 != cajaAct.obtenerVertices()->end(); iteradorVertices2++){
            for(iteradorVertices = objetoAct.obtenerVertices()->begin(); iteradorVertices != objetoAct.obtenerVertices()->end(); iteradorVertices++){
                sa= sqrt(pow(iteradorVertices2->obtenerNx()-iteradorVertices->obtenerNx(),2)+pow(iteradorVertices2->obtenerNy()-iteradorVertices->obtenerNy(),2)+pow(iteradorVertices2->obtenerNz()-iteradorVertices->obtenerNz(),2));
                if(sa <= distanciaMinima){
                    distanciaMinima = sa;
                    xc = iteradorVertices->obtenerNx();
                    yc = iteradorVertices->obtenerNy();
                    zc = iteradorVertices->obtenerNz();
                    indice = iteradorVertices->obtenerIndice();
                } 
            }
            cout<<iteradorVertices2->obtenerIndice()+1<<" ("<<iteradorVertices2->obtenerNx()<<", "<<iteradorVertices2->obtenerNy()<<", "<<iteradorVertices2->obtenerNz()<<")    ";
            cout<<indice+1<<" ("<<xc<<", "<<yc<<", "<<zc<<")    ";
            cout<<distanciaMinima<<endl;
        } 
    }
    cout<<endl;
}