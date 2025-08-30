#ifndef __TAD_SECUENCIA_GENETICA__H__
#define __TAD_SECUENCIA_GENETICA__H__

#include <iostream>

using namespace std;

class SecuenciaGenetica {

    // Funciones públicas
    public:
        SecuenciaGenetica(); // Constructor

        // Getters y setters:
        void setNombre(string nombre);
        void setDatos(string datos);
        string getNombre();
        string getDatos();


    // Datos protegidos
    private:
        string nombre;
        string datos;
};

#endif