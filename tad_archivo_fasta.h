#ifndef __TAD_ARCHIVO_FASTA__H__
#define __TAD_ARCHIVO_FASTA__H__

#include <iostream>
#include <vector>
#include "tad_secuencia_genetica.h"

using namespace std;

class ArchivoFasta {
    private:
        vector <SecuenciaGenetica> secuencias;

    public:
        bool cargaDeArchivo(string archivito);
};

#endif