#include "tad_sistema.h"
#include "tad_secuencia_genetica.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool Sistema::cargaDeArchivo(string archivito){
    ifstream archivo(archivito);
    string linea;
    string codigo = "";
    SecuenciaGenetica sec;
    vector<char> datos;

    if(!archivo.is_open()){
        printf("No fue posible abrir el archivo\n");
        return false;
    }
    
    while(getline(archivo, linea)) {// Se leerá linea por linea
        if((linea[0] == '>') || (archivo.peek() == EOF)) { // Si al iniciar una linea, se encuentra este caracter en la posición 0:
            if(!codigo.empty() ){

                // Guardado de caracteres en el vector de chars
                for (char c : codigo) {
                    datos.push_back(c);
                }

                // Guardado de la secuencia en el objeto 
                sec.setDatos(datos);
                conjuntoSecuencias.push_back(sec);

                // Reinicio de variables para la próxima secuencia
                codigo = "";
                datos.clear();
            }
            sec.setNombre(linea.substr(1)); // Guardará el nombre después del caracter
        }
        else{
            codigo += linea + "\n"; // No se hace push_back porque esto espera un char, no un string completo
        }
    }

    return true;
}



void Sistema::listarSecuencias(vector<SecuenciaGenetica> secuencias){
    vector <SecuenciaGenetica>::iterator it;
    it = secuencias.begin();
    vector <char>::iterator it_char;
    string dato = "";

    //Iteración del vector con iteradores
    for (; it != secuencias.end(); it++){
        cout << it->getNombre() << "\n";
        
        //Armado y imprimido de la secuencia con caracteres del vector mediante iteradores
        it_char = it->getDatos().begin();
        for (; it_char != it->getDatos().end(); it_char++){
            dato += *it_char;
        }
        cout << dato << "\n";
        dato = "";
    }
}


void Sistema::histograma(string nombreSecuencia){
    cout << "[" << nombreSecuencia << "] con tamaño " << nombreSecuencia.size() << "\n";
    for(SecuenciaGenetica& recorre : conjuntoSecuencias){
        cout << "[" << recorre.getNombre() << "] con tamaño " << recorre.getNombre().size() << "\n";
        if(recorre.getNombre() == nombreSecuencia){
            cout << recorre.getNombre();
            recorre.contarBases();

            for(Base muestraFrec : recorre.getConteo()){
                cout << muestraFrec.obtenerBase() << ": " << muestraFrec.obtenerFrecuencia() << " repeticiones.\n";
            }
        }
    }
}



void Sistema::contarSubsecuencias(string subsecuencia)
{
    vector<SecuenciaGenetica>::iterator it = conjuntoSecuencias.begin();
    int total = 0;

    for (; it != conjuntoSecuencias.end(); it++){
        total += it->contarSubsecuencia(subsecuencia);
    }

    printf("Total de ocurrencias de las secuencias es :%d\n", total);
}

vector <SecuenciaGenetica> Sistema:: obtenerConjuntoSec(){
    return conjuntoSecuencias;
}