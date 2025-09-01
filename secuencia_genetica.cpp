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

vector <Base> SecuenciaGenetica:: getConteo(){
    return conteo;
}

vector<char> SecuenciaGenetica::getDatos(){
    return datos;
}

void SecuenciaGenetica::contarBases(){
    for(char recorre : datos){
        Base obj;
        if (recorre == '\n') continue; // Se ignoran los saltos de línea
        if(!yaExiste(recorre)){
            for(char recorre_2 : datos){
                //if (recorre_2 == '\n') continue; // Se ignoran los saltos de línea
                if(recorre_2 == recorre){
                    obj.actualizaFrecuencia(); // Cada vez que encuentre la base en la secuencia, está aumentará su frecuencia de uno en uno
                }
            }
            obj.setBase(recorre); // Se le pasa el char en el que estamos
            conteo.push_back(obj);
        }
    }
}

// Verifica si la base ya está en el vector
bool SecuenciaGenetica::yaExiste(char base){
    for(Base recorre : conteo){
        if((recorre.obtenerBase() == base)){ // Se ignoran los saltos de línea
            return true;
        }
    }

    return false;
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
