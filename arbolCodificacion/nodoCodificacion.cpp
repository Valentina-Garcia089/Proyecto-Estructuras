#include <iostream>
#include "NodoCodificacion.h"

using namespace std;

NodoCodificacion::NodoCodificacion(char base, int frecuencia){
    if(esHoja()){
        this->base = base;
    }
    this->frecuencia = frecuencia;
}

NodoCodificacion::~NodoCodificacion(){
    delete this->hijoDer;
    delete this->hijoIzq;
    this->hijoDer = nullptr;
    this->hijoIzq = nullptr;
}

char NodoCodificacion::getBase() const{
    return this->base;
}

int NodoCodificacion::getFrecuencia() const{
    return this->frecuencia;
}

NodoCodificacion* NodoCodificacion::getHijoIzq(){
    return this->hijoIzq;
}

NodoCodificacion* NodoCodificacion::getHijoDer(){
    return this->hijoDer;
}

void NodoCodificacion::setHijoIzq(NodoCodificacion* izquierda){
    this->hijoIzq = izquierda;
}

void NodoCodificacion::setHijoDer(NodoCodificacion* derecha){
    this->hijoDer = derecha;
}

bool NodoCodificacion::esHoja(){
    if(this->hijoDer == NULL){
        if(this->hijoIzq == NULL){
            return true;
        }
    }

    return false;
}
