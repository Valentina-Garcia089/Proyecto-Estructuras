#include "./GrafoSecuencia.h"
#include "GrafoSecuencia.h"

GrafoSecuencia::GrafoSecuencia(SecuenciaGenetica &secuencia){
    //TODO
}

void GrafoSecuencia::llenarMatrizAdyacencia(){
    //TODO
}

void GrafoSecuencia::mostrarMatrizAdyacencia(){
    //TODO
}

tuple<int, vector<Base>> GrafoSecuencia::obtenerRutaMasCorta(tuple<int, int> origen, tuple<int, int> destino){
    //TODO
    return tuple<int, vector<Base>>();
}

tuple<int, vector<Base>> GrafoSecuencia::obtenerBaseRemota(tuple<int, int> origen, tuple<int, int> destino){
    //TODO
    return tuple<int, vector<Base>>();
}

int GrafoSecuencia::obtenerCostoRuta(tuple<int, int> origen, tuple<int, int> destino){
    //TODO
    return 0;
}
