#ifndef __NODO_CODIFICACION__H__
#define __NODO_CODIFICACION__H__

#include <iostream>
#include <vector>

using namespace std;

class NodoCodificacion {
    private:
        char base;
        int frecuencia;
        NodoCodificacion* hijoIzq = nullptr;
        NodoCodificacion* hijoDer = nullptr;
    public:
        NodoCodificacion(char base, int frecuencia);
        ~NodoCodificacion();
        void setFrecuencia(int frecuencia);
        char getBase() const;
        int getFrecuencia() const;
        NodoCodificacion* getHijoIzq();
        NodoCodificacion* getHijoDer();
        void setHijoIzq(NodoCodificacion* izquierda);
        void setHijoDer(NodoCodificacion* derecha);
        bool esHoja();
};

#endif