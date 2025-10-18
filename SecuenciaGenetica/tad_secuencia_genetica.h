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
        int esSubsecuencia(const string &s);
        void setAnchoJustificacion(int ancho);
        int getAnchoJustificacion() const;
        bool esIgual(string secuencia, string subsecuencia);
        bool contieneChar(std::vector<char> vec, char elemento);

    // Datos protegidos
    private:
        string nombre;
        int anchoJustificacion;
        vector<char> datos;
        vector <Base> conteo;
};

#endif