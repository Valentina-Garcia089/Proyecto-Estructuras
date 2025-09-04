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
   /*  int count;
    vector<std::string> combinaciones = combinacionesString(s); 
    vector<std::string>::iterator it = combinaciones.begin();
    vector<int> ocurrencias;

    while (it != combinaciones.end()){
        count = 0;
        try
        {
            for (size_t t = 0; t <= it->size()-s.size(); t++){
                if (s == it->substr(t, s.size())){
                    count++;
                    t += s.size() - 1; // Evita contar dos veces o de manera repetida
                }
            }
        }
        catch(const std::exception& e)
        {
            ocurrencias.push_back(count);
        } 
        it++;
    }

    for (int n : ocurrencias){
        if (n > 0) return n;
    }
 */
    return 0;
}

bool SecuenciaGenetica::esIgual(string secuencia, string subsecuencia)
{
    // La secuencia y la subsecuencia deben tener el mismo tamaño para comparar
    if (secuencia.size() != subsecuencia.size()) return false;

    // Para cada posición, verifica si el caracter de la subsecuencia está representado por la base de la secuencia
    for (size_t i = 0; i < secuencia.size(); ++i) {
        char baseSec = secuencia[i];
        char baseSub = subsecuencia[i];
        bool match = false;

        // Busca la base en el vector conteo para obtener sus representaciones
        for (Base& b : conteo) {
            if (b.obtenerBase() == baseSec) {
                vector<char> representa = b.getRepresenta();
                // Búsqueda manual en vez de std::find
                for (size_t j = 0; j < representa.size(); ++j) {
                    if (representa[j] == baseSub) {
                        match = true;
                        break;
                    }
                }
                break; // Ya encontramos la base, no hace falta seguir buscando en conteo
            }
        }
        if (!match) return false;
    }
    // Si todas las posiciones coinciden, retorna true
    return true;
}
