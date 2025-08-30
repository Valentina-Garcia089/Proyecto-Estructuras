#include "tad_secuencia_genetica.h"
#include <iostream>

using namespace std;

SecuenciaGenetica::SecuenciaGenetica() {
    nombre = "";
    datos = "";
}

// Implementación de los getters y setters del TAD de secuencia genetica
void SecuenciaGenetica::setNombre(string nombre){
    // this es un puntero al objeto. Si se quiere usar this. toca usarlo asi: (*this).
    this->nombre = nombre;
}

void SecuenciaGenetica::setDatos(string datos){
    this->datos = datos;
}

string SecuenciaGenetica::getNombre(){
    return nombre;
}

string SecuenciaGenetica::getDatos(){
    return datos;
}