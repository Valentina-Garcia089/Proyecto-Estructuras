#ifndef __ARBOL_CODIFICACION__H__
#define __ARBOL_CODIFICACION__H__

#include "NodoCodificacion.h"
#include "../SecuenciaGenetica/tad_base.h"

#include <iostream>
#include <vector>

using namespace std;

class ArbolCodificacion {
    private:
        NodoCodificacion* raiz;
    public:
        ArbolCodificacion(vector<Base> cantidades);
        NodoCodificacion* getRaiz();
        vector<bool> obtenerCodigoDeBase(char baseBuscada);
        vector<bool> obtenerCodigo(NodoCodificacion* nodo, char baseBuscada, vector<bool> codigoActual);
        void imprimirArbol();
        char obtenerBaseDeDato(vector<bool> codigoBuscado);
};

#endif