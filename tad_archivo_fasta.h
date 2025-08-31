#ifndef __TAD_ARCHIVO_FASTA__H__
#define __TAD_ARCHIVO_FASTA__H__

#include <iostream>
#include <vector>
#include "tad_secuencia_genetica.h"

using namespace std;

class ArchivoFasta {
    public:
        vector <SecuenciaGenetica> cargaDeArchivo(string archivito);
};

#endif