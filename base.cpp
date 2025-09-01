#include "tad_base.h"

#include <iostream>

using namespace std;

Base::Base(){
    frecuencia = 0;
}


char Base::obtenerBase(){
    return base;
}


int Base::obtenerFrecuencia(){
    return frecuencia;
}


void Base::setBase(char base){
    this->base = base;
}


void Base::actualizaFrecuencia(){
    frecuencia++;
}