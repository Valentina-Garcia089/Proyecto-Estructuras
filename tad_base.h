#ifndef __TAD_BASE__H__
#define __TAD_BASE__H__

#include <iostream>
#include <vector>

using namespace std;

class Base {
    private:
        char base;
        int frecuencia;
        vector<char> representa;
    
    public:
        Base(char base, int frecuencia, vector<char> representa); // Nuevo constructor
        char obtenerBase();
        int obtenerFrecuencia();
        void setBase(char base);
        void actualizaFrecuencia();
};

#endif