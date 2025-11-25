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

        int row = i / ancho;
        int col = i % ancho;

        // movimientos arriba, abajo, izquierda, derecha
        int movs[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        for (int k = 0; k < 4; k++) {

            int r = row + movs[k][0];
            int c = col + movs[k][1];

            // validar límites reales
            if (r < 0 || c < 0 || r >= alto || c >= ancho) continue;

            int idx = r * ancho + c;

            if (idx >= 0 && idx < tam) {
                float costo = obtenerCostoRuta(nodos[i], nodos[idx]);
                matrizAdyacencia[i][idx] = costo;
                matrizAdyacencia[idx][i] = costo;  // conexión bidireccional
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
    // Interpretamos el par de entrada como (fila, columna)
    int fila_origen = origen.first;
    int col_origen = origen.second;

    int fila_dest = destino.first;
    int col_dest = destino.second;
    // Validar coordenadas (no negativas)
    if (fila_origen < 0 || col_origen < 0) return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, {});
    if (fila_dest < 0 || col_dest < 0) return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, {});

    // Convertir (fila, columna) a índice: idx = fila * ancho + columna
    int idx_origen = fila_origen * ancho + col_origen;
    int idx_dest = fila_dest * ancho + col_dest;

    if (idx_origen < 0 || idx_origen >= tam) return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, {});
    if (idx_dest < 0 || idx_dest >= tam) return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, {});

    // Dijkstra
    const float INF = 1e30f;
    vector<float> dist(tam, INF);
    vector<int> prev(tam, -1);
    vector<bool> visited(tam, false);

    // min-heap (dist, node)
    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> pq;

    dist[idx_origen] = 0.0f;
    pq.push({0.0f, idx_origen});

    while (!pq.empty()) {
        pair<float,int> front = pq.top(); 
        pq.pop();
        int u = front.second;
        if (visited[u]) continue;
        visited[u] = true;
        if (u == idx_dest) break;

        for (int v = 0; v < tam; ++v) {
            float w = matrizAdyacencia[u][v];
            if (w <= 0.0f) continue; // sin arista
            if (visited[v]) continue;
            float nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.push({nd, v});
            }
        }
    }

    
    if (dist[idx_dest] == INF) {
        // No hay ruta entre origen y destino, devolver ruta vacía con costo 0
        return pair<float, vector<pair<char, pair<int,int>>>>(0.0f, {});
    }

    // Reconstruir camino
    vector<int> caminoIndices;
    for (int at = idx_dest; at != -1; at = prev[at]) {
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
    for (size_t k = 1; k < caminoIndices.size(); ++k) {
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

    if (fila_origen < 0 || col_origen < 0 || 
        fila_origen >= alto || col_origen >= ancho)
    {
        return pair<float, vector<pair<char, pair<int,int>>>>(-1.0f, vector<pair<char, pair<int,int>>>());
    }

    int idx_origen = fila_origen * ancho + col_origen;
    char base = nodos[idx_origen];

    const float INF = 1e30f;
    vector<float> dist(tam, INF);
    vector<int> prev(tam, -1);
    vector<bool> visited(tam, false);

    priority_queue<pair<float,int>, vector<pair<float,int>>, greater<pair<float,int>>> pq;

    dist[idx_origen] = 0.0f;
    pq.push(pair<float,int>(0.0f, idx_origen));

    // Dijkstra para todos
    while (!pq.empty()) {

        pair<float,int> top = pq.top();
        pq.pop();

        int u = top.second;
        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < tam; v++) {

            float w = matrizAdyacencia[u][v];
            if (w <= 0.0f) continue;

            float nd = dist[u] + w;

            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                pq.push(pair<float,int>(nd, v));
            }
        }
    }

    // Buscar la base con la misma letra MÁS LEJANA (mayor costo acumulado)
    int idx_remoto = -1;
    float max_dist = -1.0f;

    for (int i = 0; i < tam; i++) {
        if (i == idx_origen) continue;
        if (nodos[i] == base && dist[i] != INF) {
            if (dist[i] > max_dist) {
                max_dist = dist[i];
                idx_remoto = i;
            }
        }
    }

    if (idx_remoto == -1) {
        return pair<float, vector<pair<char, pair<int,int>>>>(-2.0f, vector<pair<char, pair<int,int>>>());
    }

    // Reconstrucción del camino
    vector<int> camino;
    for (int at = idx_remoto; at != -1; at = prev[at]) {
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
