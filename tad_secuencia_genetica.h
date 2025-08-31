#ifndef __TAD_SECUENCIA_GENETICA__H__
#define __TAD_SECUENCIA_GENETICA__H__

#include <iostream>
#include <vector>

using namespace std;

class SecuenciaGenetica {

    // Funciones públicas
    public:
        SecuenciaGenetica(); // Constructor

        // Getters y setters:
        void setNombre(string nombre);
        void setDatos(vector<char> datos);
        string getNombre();
        vector<char> getDatos();


    // Datos protegidos
    private:
        string nombre;
        vector<char> datos;
};

#endif