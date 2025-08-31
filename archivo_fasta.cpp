#include "tad_archivo_fasta.h"
#include "tad_secuencia_genetica.h"
#include <iostream>
#include <fstream>

using namespace std;

vector <SecuenciaGenetica> ArchivoFasta::cargaDeArchivo(string archivito){
    ifstream archivo(archivito);
    string linea;
    string codigo = "";
    SecuenciaGenetica sec;
    vector <SecuenciaGenetica> secuenciaRetorno;
    bool archivoCargado = false;

    if(!archivo.is_open()){
        printf("No fue posible abrir el archivo\n");
    }
    
    while(getline(archivo, linea)) {// Se leerá linea por linea
        if((linea[0] == '>') || (archivo.peek() == EOF)) { // Si al iniciar una linea, se encuentra este caracter en la posición 0:
            if(!codigo.empty() ){
                sec.setDatos(codigo);
                secuenciaRetorno.push_back(sec);
                codigo = "";
            }
            sec.setNombre(linea.substr(1)); // Guardará el nombre después del caracter
        }
        else{
            codigo += linea + "\n"; // No se hace push_back porque esto espera un char, no un string completo
        }
    }

    return secuenciaRetorno;
}

void ArchivoFasta::listarSecuencias(vector<SecuenciaGenetica> secuencias){
    vector <SecuenciaGenetica>::iterator it;
    it = secuencias.begin();

    for (; it != secuencias.end(); it++){
        cout << it->getNombre() << "\n";
        cout << it->getDatos() << "\n";
    }

}