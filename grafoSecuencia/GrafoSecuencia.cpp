#include "./GrafoSecuencia.h"
#include "GrafoSecuencia.h"
#include <iomanip>
#include <cmath>
#include <queue>
#include <algorithm>

GrafoSecuencia::GrafoSecuencia(SecuenciaGenetica &secuencia){
    int tam = secuencia.getDatos().size();
    ancho = secuencia.getAnchoJustificacion();
    alto = ceil((double)tam / (double)ancho);
    nodos = secuencia.getDatos();
    matrizAdyacencia.resize(tam, vector<float>(tam, 0));
    llenarMatrizAdyacencia();
    //mostrarMatrizAdyacencia();
}

void GrafoSecuencia::llenarMatrizAdyacencia(){
    if (ancho <= 0) return;

    int tam = nodos.size();
    matrizAdyacencia.assign(tam, vector<float>(tam, 0.0f));

    for (int i = 0; i < tam; i++) {

        int fila = i / ancho;
        int columna = i % ancho;

        // movimientos arriba, abajo, izquierda, derecha
        int movi[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        for (int movimiento = 0; movimiento < 4; movimiento++) {

            int fil = fila + movi[movimiento][0];
            int col = columna + movi[movimiento][1];

            //validar límites reales
            if (fil < 0 || col < 0 || fil >= alto || col >= ancho) continue;

            //Calcular el indice en la lista
            int indice = fil * ancho + col;

            if (indice >= 0 && indice < tam) {
                float costo = obtenerCostoRuta(nodos[i], nodos[indice]);
                matrizAdyacencia[i][indice] = costo;
                matrizAdyacencia[indice][i] = costo;  // conexion bidireccional / grafo no dirigido
            }
        }
    }
}

void GrafoSecuencia::mostrarMatrizAdyacencia(){
    vector<vector<float>>::iterator fila = matrizAdyacencia.begin();
    vector<float>::iterator columna;
    for(; fila != matrizAdyacencia.end(); fila++){
        for(columna = fila->begin(); columna != fila->end(); columna++){
            cout << setw(2) << setprecision(2) << *columna << " ";
        }
        cout << "\n";
    }
}

pair<float, vector<pair<char, pair<int,int>>>> GrafoSecuencia::obtenerRutaMasCorta(pair<int,int> origen, pair<int,int> destino){
    int tam = nodos.size();

    // Coordenadas (fila, columna)
    int fila_origen = origen.first;
    int col_origen = origen.second;

    int fila_dest = destino.first;
    int col_dest = destino.second;

    // Validar coordenadas (no negativas)
    if (fila_origen < 0 || col_origen < 0) return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, {});
    if (fila_dest < 0 || col_dest < 0) return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, {});

    if (fila_origen >= alto || col_origen >= ancho) return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, {});
    if (fila_dest >= alto || col_dest >= ancho) return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, {});

    // Convertir coordenadas dadas a indices de la lista
    int i_origen = fila_origen * ancho + col_origen;
    int i_destino = fila_dest * ancho + col_dest;

    //Validar que los indices esten correctos
    if (i_origen < 0 || i_origen >= tam) return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, {});
    if (i_destino < 0 || i_destino >= tam) return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, {});

    //Algortimo Dijkstra 
    const float INF = 1e30f;
    vector<float> dist(tam, INF);
    vector<int> anterior(tam, -1);
    vector<bool> visitado(tam, false);

    //Cola de prioridad
    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> cola;

    dist[i_origen] = 0.0f;
    cola.push({0.0f, i_origen});

    while (!cola.empty()) {
        pair<float,int> front = cola.top(); 
        cola.pop();
        int indi = front.second;
        if (visitado[indi]) continue;
        visitado[indi] = true;
        if (indi == i_destino) break;

        for (int v = 0; v < tam; ++v) {
            float peso = matrizAdyacencia[indi][v];
            if (peso <= 0.0f) continue; // no existe arista
            if (visitado[v]) continue;
            float total = dist[indi] + peso;
            if (total < dist[v]) {
                dist[v] = total;
                anterior[v] = indi;
                cola.push({total, v});
            }
        }
    }

    
    if (dist[i_destino] == INF) {
        // no hay ruta entre origen y destino
        return pair<float, vector<pair<char, pair<int,int>>>>(0.0f, {});
    }

    // Reconstruir camino
    vector<int> caminoIndices;
    for (int at = i_destino; at != -1; at = anterior[at]) {
        caminoIndices.push_back(at);
    }
    reverse(caminoIndices.begin(), caminoIndices.end());

    // Construir vector de pares {base, {fila, columna}} con las bases en la ruta
    vector<pair<char, pair<int,int>>> ruta;
    for (int ind : caminoIndices) {
        int fila = ind / ancho;
        int col = ind % ancho;
        ruta.push_back({nodos[ind], {fila, col}});
    }

    // Calcular costo total como suma de pesos (float). Retornamos un int escalado para preservar fracciones.
    float costoTotal = 0.0f;
    for (size_t k = 1; k < caminoIndices.size(); k++) {
        int a = caminoIndices[k-1];
        int b = caminoIndices[k];
        costoTotal += matrizAdyacencia[a][b];
    }

    float costoEntero = costoTotal;

    return pair<float, vector<pair<char, pair<int,int>>>>(costoEntero, ruta);
}

pair<float, vector<pair<char, pair<int,int>>>> 
GrafoSecuencia::obtenerBaseRemota(pair<int,int> origen)
{
    int tam = nodos.size();

    // Validar coordenadas de origen
    int fila_origen = origen.first;
    int col_origen  = origen.second;

    if (fila_origen < 0 || col_origen < 0 || fila_origen >= alto || col_origen >= ancho)
    {
        return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, vector<pair<char, pair<int,int>>>());
    }

    int indic_origen = fila_origen * ancho + col_origen;
    char base = nodos[indic_origen];

    const float INF = 1e30f;
    vector<float> dist(tam, INF);
    vector<int> anterior(tam, -1);
    vector<bool> visitado(tam, false);

    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> cola;

    dist[indic_origen] = 0.0f;
    cola.push(pair<float,int>(0.0f, indic_origen));

    // Dijkstra para todos
    while (!cola.empty()) {

        pair<float,int> top = cola.top();
        cola.pop();

        int ind = top.second;
        if (visitado[ind]) continue;
        visitado[ind] = true;

        for (int v = 0; v < tam; v++) {

            float peso = matrizAdyacencia[ind][v];
            if (peso <= 0.0f) continue;

            float total = dist[ind] + peso;

            if (total < dist[v]) {
                dist[v] = total;
                anterior[v] = ind;
                cola.push(pair<float,int>(total, v));
            }
        }
    }

    // Buscar la base con la misma letra y mayor costo
    int ind_remota = -1;
    float max_dist = -1.0f;

    for (int i = 0; i < tam; i++) {
        if (i == indic_origen) continue;
        if (nodos[i] == base && dist[i] != INF) {
            if (dist[i] > max_dist) {
                max_dist = dist[i];
                ind_remota = i;
            }
        }
    }

    if (ind_remota == -1) {
        return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, vector<pair<char, pair<int,int>>>());
    }

    // Reconstrucción del camino
    vector<int> camino;
    for (int at = ind_remota; at != -1; at = anterior[at]) {
        camino.push_back(at);
    }
    reverse(camino.begin(), camino.end());

    vector<pair<char, pair<int,int>>> ruta;
    for (int k = 0; k < (int)camino.size(); k++) {
        int id = camino[k];
        ruta.push_back(pair<char, pair<int,int>>(nodos[id], pair<int,int>(id / ancho, id % ancho)));
    }

    return pair<float, vector<pair<char, pair<int,int>>>>(max_dist, ruta);
}


float GrafoSecuencia::obtenerCostoRuta(char origen, char destino){
    
    float distancia = 1.0 / (float)(abs((int)origen - (int)destino) + 1);

    return distancia;
}
