#ifndef __TAD_SISTEMA__H__
#define __TAD_SISTEMA__H__

#include <iostream>
#include <vector>
#include "tad_secuencia_genetica.h"

using namespace std;

class Sistema {
    private:
        vector <SecuenciaGenetica> conjuntoSecuencias;

    public:
        bool cargaDeArchivo(string archivito);
        void listarSecuencias(vector<SecuenciaGenetica> secuencias);
        void contarSubsecuencias(string subsecuencia);

        vector <SecuenciaGenetica> obtenerConjuntoSec();
};

#endif