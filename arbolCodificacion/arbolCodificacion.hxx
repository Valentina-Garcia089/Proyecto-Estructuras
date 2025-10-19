#include <iostream>
#include "ArbolCodificacion.h"
#include <algorithm>

using namespace std;



ArbolCodificacion::ArbolCodificacion(vector<Base> cantidades){
    vector<NodoCodificacion*> nodos;
    for (int i = 0; i < cantidades.size(); i++){
        if (cantidades[i].obtenerFrecuencia() == 0){
            continue;
        }
        NodoCodificacion* nuevoNodo = new NodoCodificacion(cantidades[i].obtenerBase(), cantidades[i].obtenerFrecuencia());
        nodos.push_back(nuevoNodo);
    }

    while (nodos.size() > 1){
        sort(nodos.begin(), nodos.end());

        NodoCodificacion* izquierdo = nodos[0];
        NodoCodificacion* derecho = nodos[1];

        NodoCodificacion* nuevoNodo = new NodoCodificacion('\0', izquierdo->getFrecuencia() + derecho->getFrecuencia());
        nuevoNodo->setHijoIzq(izquierdo);
        nuevoNodo->setHijoDer(derecho);

        nodos.erase(nodos.begin());
        nodos.erase(nodos.begin());
        nodos.push_back(nuevoNodo);
    }

    this->raiz = nodos[0];
}

NodoCodificacion *ArbolCodificacion::getRaiz(){
    return this->raiz;
}

//TODO: Revisar
void imprimirNodo(NodoCodificacion* nodo, string prefijo = "", bool esIzquierdo = true) {
    if (nodo != nullptr) {
        cout << prefijo;

        // Imprime el conector del nodo
        cout << (esIzquierdo ? "|--- " : "'--- ");

        // Imprime el carácter y la frecuencia del nodo
        if (nodo->getBase() == '\0') {
            cout << "[Nodo interno] (" << nodo->getFrecuencia() << ")\n";
        } else {
            cout << "'" << nodo->getBase() << "' (" << nodo->getFrecuencia() << ")\n";
        }

        // Llama recursivamente para los hijos izquierdo y derecho
        imprimirNodo(nodo->getHijoIzq(), prefijo + (esIzquierdo ? "|   " : "    "), true);
        imprimirNodo(nodo->getHijoDer(), prefijo + (esIzquierdo ? "|   " : "    "), false);
    }
}

void ArbolCodificacion::imprimirArbol() {
    if (this->raiz == nullptr) {
        cout << "El árbol está vacío.\n";
        return;
    }
    imprimirNodo(this->raiz);
}