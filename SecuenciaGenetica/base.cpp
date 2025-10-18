#include "tad_base.h"

#include <iostream>

using namespace std;

Base::Base(char base, int frecuencia, vector<char> representa) {
    this->base = base;
    this->frecuencia = frecuencia;
    this->representa = representa;
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

vector<char> Base::getRepresenta() const
{
    return representa;
}