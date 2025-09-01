#include "tad_secuencia_genetica.h"
#include <iostream>
#include <vector>

using namespace std;

SecuenciaGenetica::SecuenciaGenetica() {
    nombre = "";
    datos = {};
}

// Implementación de los getters y setters del TAD de secuencia genetica
void SecuenciaGenetica::setNombre(string nombre){
    // this es un puntero al objeto. Si se quiere usar this. toca usarlo asi: (*this).
    this->nombre = nombre;
}

void SecuenciaGenetica::setDatos(vector<char> datos){
    this->datos = datos;
}

string SecuenciaGenetica::getNombre(){
    return nombre;
}

vector<char> SecuenciaGenetica::getDatos(){
    return datos;
}

int SecuenciaGenetica::contarBases(){
    
}