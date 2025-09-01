#ifndef __TAD_BASE__H__
#define __TAD_BASE__H__

#include <iostream>

using namespace std;

class Base {
    private:
        char base;
        int frecuencia;
    
    public:
        Base();
        char obtenerBase();
        int obtenerFrecuencia();
        void setBase(char base);
        void actualizaFrecuencia();
};

#endif