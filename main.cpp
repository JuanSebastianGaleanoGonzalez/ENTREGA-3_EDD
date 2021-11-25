#include <iostream>
#include <list>
#include <iterator>
#include "objeto.h" 
#include "caja.h"
#include "funciones.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {

	list<Objeto> listaObjetos;
	list<Caja> listaCajas;
    vector<Comando> listaComandos;
    generarListaComandosArchivo(&listaComandos);
    char* entradaComando = new char[TAMANNO_COMANDO];
    char* copiaComando = new char[TAMANNO_COMANDO];
    char* nombreObjeto = new char[TAMANNO_COMANDO];
    int status;
    // variables caso 7 vertice cercano
    char* corx= new char[5];
    float cx;
    char* cory= new char[5];
    float cy;
    char* corz= new char[5];
    float cz;
    char* nombre= new char[50];
    char* com= new char[50];
    char* copia2 = new char[TAMANNO_COMANDO];
    float distancia;
    bool continuar = true;

    cout<<"-------------------------------------------------------------------POLIBYUS-------------------------------------------------------------------"<<endl;
    cout<<"Bienvenido a POLIBYUS, sistema que permite manipular archivos que representan objetos 3D a partir de mallas poligonales"<<endl;
    cout<<endl;
    cout<<"Digite un comando para iniciar"<<endl;
    cout<<endl;
    cout<<"******Para mas informacion sobre los comandos digite el comando ayuda******"<<endl;
    do {
        int cont = 0;
        cout << "$";
        cin.getline(entradaComando, TAMANNO_COMANDO);
        strcpy(copiaComando, entradaComando);
        string comando(strtok(entradaComando, " \0"));
        if (strcmp(comando.c_str(), copiaComando) != 0) {
            strcpy(nombreObjeto, strtok(NULL, "\0"));
        }
        else {
            strcpy(nombreObjeto, "");
        }
        switch (extraerIndiceComando(listaComandos, comando)) {
        case -1:
            cout << "El comando ingresado no es un comando valido. Ingrese 'ayuda' para ver la lista de comandos." << endl;
            break;
        case 0:
            menuAyuda(listaComandos, nombreObjeto);
            break;
        case 1:
            cout << endl;

            status = cargar_archivo(&listaObjetos, nombreObjeto);
            if (status == 0) {
                cout << "Resultado exitoso. " << endl;
                cout << endl;
            }
            else if (status == -1) {
                cout << "El archivo no existe. verifique el nombre del archivo o los parametros del comando cargar. " << endl;
                cout << endl;
            }
            else if (status == -2) {
                cout << "Objeto ya existe. " << endl;
                cout << endl;
            }
            else if (status == -3) {
                cout << "Archivo vacio o incompleto. Verifique la estrcutura del archivo de la malla, los vertices deben separarse con salto de linea" << endl;
                cout << endl;
            }
        break;
        case 2:
            cout << endl;
            imprimirListado(listaObjetos, listaCajas);
            break;
        case 3:
            status = cajaEnvolvente(&listaObjetos, &listaCajas, nombreObjeto);         
            if (status ==+ 1) {
                cout << "Ningun objeto ha sido cargado en memoria." << endl;
                cout<<endl;
            }
            else if (status == 2) {
                cout << "La caja envolvente de los objetos en memoria se ha generado con el nombre " << listaCajas.back().obtenerNombre() << " y se ha agregado a los objetos en memoria." << endl;
                cout<<endl;
            }
            else if (status == 3) {
                cout << "El objeto " << nombreObjeto << " no ha sido cargada en memoria." << endl;
                cout<<endl;
            }
            else if (status == 4) {
                cout << "La caja envolvente del objeto " << nombreObjeto << " se ha generado con el nombre " << listaCajas.back().obtenerNombre() << " y se ha agregado a los objetos en memoria." << endl;
                cout<<endl;
            }
            break;
        case 4:
            cout << endl;
            status = descargarObjeto(&listaObjetos, &listaCajas, nombreObjeto);
            if (status == 1) {
                cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
            }
            else if (status == 2) {
                cout << "El objeto "<< nombreObjeto<< " ha sido eliminado de la memoria de trabajo." << endl;
            }
            else{
                cout << "El objeto caja envolvente "<< nombreObjeto<< " ha sido eliminado de la memoria de trabajo." << endl;
            }         
            break;
        case 5:
            cout << guardarObjeto(&listaObjetos, &listaCajas, nombreObjeto) << endl;
            break;
        case 6:
            cout << "Ha elegido la opcion V_cercano ";
            strcpy(copia2, copiaComando);
            com = strtok(copia2, " ");

            while((com = strtok(NULL, " ")) != NULL){
                cont++;
            }
            
            if(cont > 3){
                com = strtok(copiaComando, " ");

                strcpy(corx, strtok(NULL, " "));
                cx = atof(corx);
            
                strcpy(cory, strtok(NULL, " "));
                cy = atof(cory);
            
                strcpy(corz, strtok(NULL, " "));
                cz = atof(corz);

                strcpy(nombre, strtok(NULL, " "));

                cout << "de un objeto."<<endl;
                cout<<endl;
                distancia = v_cercano(&listaObjetos, cx, cy, cz, nombre, 0);
                if(distancia != 0){
                    cout<<"con una distancia de "<<distancia<<endl;
                }
            }else{
                com = strtok(copiaComando, " ");

                strcpy(corx, strtok(NULL, " "));
                cx = atof(corx);
            
                strcpy(cory, strtok(NULL, " "));
                cy = atof(cory);
            
                strcpy(corz, strtok(NULL, " "));
                cz = atof(corz);

                cout << "de todos los objetos en memoria."<<endl;
                cout<<endl;
                distancia = v_cercanoTotal(&listaObjetos, cx, cy, cz);
                if(distancia != 0){
                    cout<<"con una distancia de "<<distancia<<endl;
                }
            }
            cout<<endl;
            break;
        case 7:
            cout<<"hola1"<<endl;
            v_cercanos_caja(&listaObjetos, &listaCajas, nombreObjeto);
            break;
        case 8:
            cout << "Ha elegido la opcion 8: ruta_corta." << endl;
            break;
        case 9:
            cout << "Ha elegido la opcion 9: ruta_corta_centro." << endl;
            break;
        case 10:
            continuar = false;
            break;
        }

    } while (continuar);
}