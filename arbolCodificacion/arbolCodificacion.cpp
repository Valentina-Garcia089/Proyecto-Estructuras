#include <iostream>
#include "arbolCodificacion.h"
#include "../SecuenciaGenetica/tad_base.h"
#include <algorithm>
#include <queue>

struct Comparador {
    bool operator()(NodoCodificacion* a, NodoCodificacion* b) {
        return a->getFrecuencia() > b->getFrecuencia();
    }
};

using namespace std;

ArbolCodificacion::ArbolCodificacion(vector<Base> cantidades){
    priority_queue<NodoCodificacion*, vector<NodoCodificacion*>, Comparador> minHeap;

    for (Base& base : cantidades) {
        if (base.obtenerFrecuencia() > 0) {
            NodoCodificacion* nuevoNodo = new NodoCodificacion(base.obtenerBase(), base.obtenerFrecuencia());
            minHeap.push(nuevoNodo);
        }
    }

    while (minHeap.size() > 1) {
        NodoCodificacion* izquierdo = minHeap.top();
        minHeap.pop();
        NodoCodificacion* derecho = minHeap.top();
        minHeap.pop();

        NodoCodificacion* nuevoNodo = new NodoCodificacion('\0', izquierdo->getFrecuencia() + derecho->getFrecuencia());
        nuevoNodo->setHijoIzq(izquierdo);
        nuevoNodo->setHijoDer(derecho);

        minHeap.push(nuevoNodo);
    }

    this->raiz = minHeap.top();
}

NodoCodificacion *ArbolCodificacion::getRaiz(){
    return this->raiz;
}

void imprimirNodo(NodoCodificacion* nodo, string codigoActual = "", string prefijo = "", bool esIzquierdo = true) {
    if (nodo != nullptr) {
        cout << prefijo;

        // Imprime el conector del nodo
        cout << (esIzquierdo ? "|-- " : "'-- ");

        // Si es un nodo hoja, imprime el carácter, frecuencia y su código binario
        if (nodo->getHijoIzq() == nullptr && nodo->getHijoDer() == nullptr) {
            cout << "'" << nodo->getBase() << "' (" << nodo->getFrecuencia() << ") - Código: " << codigoActual << "\n";
        } else {
            // Si es un nodo interno, imprime solo la frecuencia
            cout << "[Nodo interno] (" << nodo->getFrecuencia() << ")\n";
        }

        // Llama recursivamente para los hijos izquierdo y derecho
        imprimirNodo(nodo->getHijoIzq(), codigoActual + "0", prefijo + (esIzquierdo ? "|   " : "    "), true);
        imprimirNodo(nodo->getHijoDer(), codigoActual + "1", prefijo + (esIzquierdo ? "|   " : "    "), false);
    }
}

void ArbolCodificacion::imprimirArbol() {
    if (this->raiz == nullptr) {
        cout << "El árbol está vacío.\n";
        return;
    }
    imprimirNodo(this->raiz);
}