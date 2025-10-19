#ifndef __ARBOL_CODIFICACION__H__
#define __ARBOL_CODIFICACION__H__

#include "nodoCodificacion.h"
#include "../SecuenciaGenetica/tad_base.h"

#include <iostream>
#include <vector>

using namespace std;

class arbolCodificacion {
    private:
        nodoCodificacion* raiz;
    public:
        arbolCodificacion(vector<Base> cantidades);
        
};

#endif