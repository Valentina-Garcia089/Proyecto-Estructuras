#ifndef __GRAFO_SECUENCIA__H__
#define __GRAFO_SECUENCIA__H__

#include "../SecuenciaGenetica/tad_secuencia_genetica.h"
#include <iostream>
#include <vector>

using namespace std;

class GrafoSecuencia {
    private:
        vector<vector<int>> matrizAdyacencia;
        vector<Base> nodos;
    public:
        GrafoSecuencia(SecuenciaGenetica &secuencia);
        void llenarMatrizAdyacencia();
        void mostrarMatrizAdyacencia();
        tuple<int,vector<Base>> obtenerRutaMasCorta(tuple<int,int> origen, tuple<int,int> destino);
        tuple<int,vector<Base>> obtenerBaseRemota(tuple<int,int> origen, tuple<int,int> destino);
        int obtenerCostoRuta(tuple<int,int> origen, tuple<int,int> destino);
};

#endif