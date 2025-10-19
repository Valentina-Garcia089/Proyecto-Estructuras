#ifndef __TAD_SISTEMA__H__
#define __TAD_SISTEMA__H__

#include <iostream>
#include <vector>
#include "../SecuenciaGenetica/tad_secuencia_genetica.h"

using namespace std;

class Sistema {
    private:
        vector <SecuenciaGenetica> conjuntoSecuencias;

    public:
        bool cargaDeArchivo(string archivito);
        void listarSecuencias(vector<SecuenciaGenetica> secuencias);
        void histograma(string nombreSecuencia);
        void contarSubsecuencias(string subsecuencia);
        bool verificarSecuencias(string secuencia);
        int verificaJustificacion(string secuencia);
        void guardarSecuencias(string nombre_archivo);
        void enmascararSecuencia(string subsecuencia);
        //TODO: Cambiar a codificar/comprimir
        void arbolCodificacion(string nombreSecuencia);
        vector <SecuenciaGenetica> obtenerConjuntoSec();
        
};

#include "sistema.cpp"

#endif