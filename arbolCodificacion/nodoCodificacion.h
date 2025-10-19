#ifndef __NODO_CODIFICACION__H__
#define __NODO_CODIFICACION__H__

#include <iostream>
#include <vector>

using namespace std;

class nodoCodificacion {
    private:
        char base;
        int frecuencia;
    public:
        nodoCodificacion(char base, int frecuencia);
        char getBase();
        int getFrecuencia();
};

#endif