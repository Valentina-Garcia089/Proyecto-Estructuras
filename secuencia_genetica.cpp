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
             Base('R', 0, {'A', 'G'}), 
             Base('Y', 0, {'C', 'T', 'U'}), 
             Base('K', 0, {'G', 'T', 'U'}), 
             Base('M', 0, {'A', 'C'}), 
             Base('S', 0, {'C', 'G'}), 
             Base('W', 0, {'A', 'T', 'U'}), 
             Base('B', 0, {'C', 'G', 'T', 'U'}), 
             Base('D', 0, {'A', 'G', 'T', 'U'}), 
             Base('H', 0, {'A', 'C', 'T', 'U'}), 
             Base('V', 0, {'A', 'C', 'G'}), 
             Base('N', 0, {'A', 'C', 'G', 'T', 'U'}), 
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
