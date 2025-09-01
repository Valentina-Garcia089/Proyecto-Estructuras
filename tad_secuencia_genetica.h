#ifndef __TAD_SECUENCIA_GENETICA__H__
#define __TAD_SECUENCIA_GENETICA__H__

#include <iostream>
#include <vector>
#include "tad_base.h"

using namespace std;

class SecuenciaGenetica {

    // Funciones públicas
    public:
        SecuenciaGenetica(); // Constructor

        // Getters y setters:
        void setNombre(string nombre);
        void setDatos(vector<char> datos);
        string getNombre();
        vector <Base> getConteo();
        vector<char> getDatos();
        void contarBases();
        int contarSubsecuencia(const string &s);

        //Se requiere de una función que verifique si la base ya se encuentra en la colección de conteo
        bool yaExiste(char base);

    // Datos protegidos
    private:
        string nombre;
        vector<char> datos;
        vector <Base> conteo;
};

#endif