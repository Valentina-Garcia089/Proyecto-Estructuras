#ifndef __NODO_CODIFICACION__H__
#define __NODO_CODIFICACION__H__

#include <iostream>
#include <vector>

using namespace std;

class nodoCodificacion {
    private:
        char base;
        int frecuencia;
        nodoCodificacion* izquierda = nullptr;
        nodoCodificacion* derecha = nullptr;
    public:
        nodoCodificacion(char base, int frecuencia);
        char getBase();
        int getFrecuencia();
        nodoCodificacion* getIzquierda();
        nodoCodificacion* getDerecha();
        void setIzquierda(nodoCodificacion* izquierda);
        void setDerecha(nodoCodificacion* derecha);
};

#endif