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

int SecuenciaGenetica::contarSubsecuencia(const string &s)
{
    int count = 0;
    //Creación de un string a partir de un vector
    string hola(datos.begin(), datos.end());
    while (hola.find('\n') != string::npos)
        hola.erase(hola.find('\n'), 1);

    try
    {
        for (size_t t = 0; t <= hola.size()-s.size(); t++){
            if (s == hola.substr(t, s.size())){
                count++;
                t += s.size() - 1; // Evita contar dos veces o de manera repetida
            }
        }
    }
    catch(const std::exception& e)
    {
        return count;
    } 

    return count;
    
}
