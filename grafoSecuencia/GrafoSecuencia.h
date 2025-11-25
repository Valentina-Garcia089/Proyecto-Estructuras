#ifndef __GRAFO_SECUENCIA__H__
#define __GRAFO_SECUENCIA__H__

#include "../SecuenciaGenetica/tad_secuencia_genetica.h"
#include <iostream>
#include <vector>

using namespace std;

class GrafoSecuencia {
    private:
        vector<vector<float>> matrizAdyacencia;
        vector<char> nodos;
        int ancho;
        int alto;
    public:
        GrafoSecuencia(SecuenciaGenetica &secuencia);
        void llenarMatrizAdyacencia();
        void mostrarMatrizAdyacencia();
        pair<float, vector<pair<char, pair<int,int>>>> obtenerRutaMasCorta(pair<int,int> origen, pair<int,int> destino);
        pair<float, vector<pair<char, pair<int,int>>>> obtenerBaseRemota(pair<int,int> origen);
        float obtenerCostoRuta(char origen, char destino);
};

#endif