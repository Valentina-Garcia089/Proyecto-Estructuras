#include "tad_secuencia_genetica.h"
#include <iostream>
#include <vector>

using namespace std;

SecuenciaGenetica::SecuenciaGenetica() {
    nombre = "";
    datos = {};
    conteo = {Base('A', 0), Base('C', 0), Base('G', 0), Base('T', 0), Base('U', 0), Base('R', 0), Base('Y', 0), Base('K', 0), Base('M', 0), Base('S', 0), Base('W', 0), Base('B', 0), Base('D', 0), Base('H', 0), Base('V', 0), Base('N', 0), Base('X', 0), Base('-', 0) }; 
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
