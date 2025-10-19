#include "tad_secuencia_genetica.h"
#include <iostream>
#include <vector>

using namespace std;

SecuenciaGenetica::SecuenciaGenetica() {
    nombre = "";
    datos = {};
    conteo = {Base('A', 0, {'A'}),
             Base('C', 0, {'C'}), 
             Base('G', 0, {'G'}), 
             Base('T', 0, {'T'}), 
             Base('U', 0, {'U'}), 
             Base('R', 0, {'R', 'A', 'G'}), 
             Base('Y', 0, {'Y', 'C', 'T', 'U'}), 
             Base('K', 0, {'K','G', 'T', 'U'}), 
             Base('M', 0, {'M', 'A', 'C'}), 
             Base('S', 0, {'S', 'C', 'G'}), 
             Base('W', 0, {'W','A', 'T', 'U'}), 
             Base('B', 0, {'B', 'C', 'G', 'T', 'U'}), 
             Base('D', 0, {'D','A', 'G', 'T', 'U'}), 
             Base('H', 0, {'H','A', 'C', 'T', 'U'}), 
             Base('V', 0, {'V','A', 'C', 'G'}), 
             Base('N', 0, {'N', 'A', 'C', 'G', 'T', 'U'}), 
             Base('X', 0, {'X'}), 
             Base('-', 0, {'-'})}; 
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

vector <Base> SecuenciaGenetica:: getConteo(){
    return conteo;
}

vector<char> SecuenciaGenetica::getDatos(){
    return datos;
}

void SecuenciaGenetica::setAnchoJustificacion(int ancho){
    this->anchoJustificacion = ancho;
}

int SecuenciaGenetica::getAnchoJustificacion() const {
    return anchoJustificacion;
}



void SecuenciaGenetica::contarBases(){
    for(Base& recorre : conteo){
        for(char recorre_2 : datos){
            if(recorre_2 == '\n') continue; // Se ignoran los saltos de línea
            if(recorre.obtenerBase() == recorre_2){
                recorre.actualizaFrecuencia();
            }
        }
    }
}



int SecuenciaGenetica::esSubsecuencia(const string &s)
{
    string secuencia(this->datos.begin(), this->datos.end());
    int tam = s.size();
    int cont = 0;
    for (int t = 0; t <= secuencia.size() - tam; t++){
        if (esIgual(secuencia.substr(t, tam), s)){
            cont++;
        }
    }

    return cont;
}

bool SecuenciaGenetica::esIgual(string secuencia, string subsecuencia)
{
    vector<Base> bases = {};
    vector<Base>::iterator it;
    
    for (int i = 0; i < secuencia.size(); ++i) {
        it = conteo.begin();
        for (; it != conteo.end(); it++){
            if (secuencia[i] == it->obtenerBase()){
                bases.push_back(*it);
            }
        }
    }

    // Verificar tamaños
    if (bases.size() < subsecuencia.size()) {
        return 0;
    }

    for (int i = 0; i < subsecuencia.size(); ++i) {
        if (contieneChar(bases[i].getRepresenta(), subsecuencia[i])){
            continue;
        } else {
            return 0;   
        }
    }

    return 1; 
}

bool SecuenciaGenetica::contieneChar(vector<char> vec, char elemento)
{
    vector<char>::iterator it = vec.begin();

    for (; it != vec.end(); it++) {
        if (*it == elemento) 
            return true;
    }

    return false;
}

