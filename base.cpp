#include "tad_base.h"

#include <iostream>

using namespace std;

Base::Base(char base, int frecuencia){
    this->base = base;
    this->frecuencia = frecuencia;
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