#include "./GrafoSecuencia.h"
#include "GrafoSecuencia.h"
#include <iomanip>
#include <cmath>

GrafoSecuencia::GrafoSecuencia(SecuenciaGenetica &secuencia){
    int tam = secuencia.getDatos().size();
    ancho = secuencia.getAnchoJustificacion();
    alto = ceil(tam/ancho);
    nodos = secuencia.getDatos();
    matrizAdyacencia.resize(tam, vector<float>(tam, 0));
    llenarMatrizAdyacencia();
    //mostrarMatrizAdyacencia();
}

void GrafoSecuencia::llenarMatrizAdyacencia(){
    if (ancho <= 0) return;
    int tam = nodos.size();
    matrizAdyacencia.assign(tam, vector<float>(tam, 0));

    for (int i = 0; i < tam; ++i) {
        int row = i / ancho;
        int col = i % ancho;

        // Arriba
        {
            int r = row - 1;
            int c = col;
            if (r >= 0 && c >= 0) {
                int idx = r * ancho + c;
                if (idx >= 0 && idx < tam) {
                    float costo = obtenerCostoRuta(nodos[i], nodos[idx]);
                    matrizAdyacencia[i][idx] = costo;
                    matrizAdyacencia[idx][i] = costo;
                }
            }
        }

        // Abajo
        {
            int r = row + 1;
            int c = col;
            if (r >= 0 && c >= 0) {
                int idx = r * ancho + c;
                if (idx >= 0 && idx < tam) {
                    float costo = obtenerCostoRuta(nodos[i], nodos[idx]);
                    matrizAdyacencia[i][idx] = costo;
                    matrizAdyacencia[idx][i] = costo;
                }
            }
        }

        // Izquierda
        {
            int r = row;
            int c = col - 1;
            if (r >= 0 && c >= 0) {
                int idx = r * ancho + c;
                if (idx >= 0 && idx < tam) {
                    float costo = obtenerCostoRuta(nodos[i], nodos[idx]);
                    matrizAdyacencia[i][idx] = costo;
                    matrizAdyacencia[idx][i] = costo;
                }
            }
        }

        // Derecha
        {
            int r = row;
            int c = col + 1;
            if (r >= 0 && c >= 0) {
                int idx = r * ancho + c;
                if (idx >= 0 && idx < tam) {
                    float costo = obtenerCostoRuta(nodos[i], nodos[idx]);
                    matrizAdyacencia[i][idx] = costo;
                    matrizAdyacencia[idx][i] = costo;
                }
            }
        }
    }
}

void GrafoSecuencia::mostrarMatrizAdyacencia(){
    vector<vector<float>>::iterator fila = matrizAdyacencia.begin();
    vector<float>::iterator columna;
    for(fila; fila != matrizAdyacencia.end(); fila++){
        for(columna = fila->begin(); columna != fila->end(); columna++){
            cout << setw(2) << setprecision(2) << *columna << " ";
        }
        cout << "\n";
    }
}

pair<int, vector<Base>> GrafoSecuencia::obtenerRutaMasCorta(pair<int,int> origen, pair<int,int> destino){
    //TODO
    return pair<int, vector<Base>>();
}

pair<int, vector<Base>> GrafoSecuencia::obtenerBaseRemota(pair<int,int> origen){
    //TODO
    return pair<int, vector<Base>>();
}

float GrafoSecuencia::obtenerCostoRuta(char origen, char destino){
    
    float distancia = 1.0 / (float)(abs((int)origen - (int)destino) + 1);

    return distancia;
}
