#include <iostream>
#include "arbolCodificacion.h"
#include "../SecuenciaGenetica/tad_base.h"
#include <algorithm>

struct Comparador {
    bool operator()(NodoCodificacion* a, NodoCodificacion* b) {
        return a->getFrecuencia() > b->getFrecuencia();
    }
};

using namespace std;

ArbolCodificacion::ArbolCodificacion(vector<Base> cantidades){
    priority_queue<NodoCodificacion*, vector<NodoCodificacion*>, Comparador> cola;
    priority_queue<NodoCodificacion*, vector<NodoCodificacion*>, Comparador> minHeap;

    for (Base& base : cantidades) {
        if (base.obtenerFrecuencia() > 0) {
            NodoCodificacion* nuevoNodo = new NodoCodificacion(base.obtenerBase(), base.obtenerFrecuencia());
            cola.push(nuevoNodo);
        }
    }

    cola.push(new NodoCodificacion('L', 0)); // Nodo de delimitador

    int contador = 1;

    //Posible uso para mantener el rango en 8 bits
    while (!cola.empty()) {
        NodoCodificacion* nodoActual = cola.top();
        nodoActual->setFrecuencia(contador);
        minHeap.push(nodoActual);
        if (nodoActual->getBase() != 'L'){
            bases.push_back(Base(nodoActual->getBase(),nodoActual->getFrecuencia(),{}));   
        }
        cola.pop();
        contador+=2;
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

    for (Base& base : cantidades) {
        cout << base.obtenerBase() << ": " << base.obtenerFrecuencia() << " repeticiones.\n";
    }
}

NodoCodificacion *ArbolCodificacion::getRaiz(){
    return this->raiz;
}

vector<bool> ArbolCodificacion::obtenerCodigoDeBase(char baseBuscada) {
    return obtenerCodigo(this->raiz, baseBuscada, {});
}

vector<bool> ArbolCodificacion::obtenerCodigo(NodoCodificacion* nodo, char baseBuscada, vector<bool> codigoActual) {
    if (nodo == nullptr) {
        return {};
    }


    if (nodo->esHoja() && nodo->getBase() == baseBuscada) {
        return codigoActual;
    }

    codigoActual.push_back(false);
    vector<bool> codigoIzq = obtenerCodigo(nodo->getHijoIzq(), baseBuscada, codigoActual);
    if (!codigoIzq.empty()) {
        return codigoIzq;
    }
    codigoActual.pop_back();

    codigoActual.push_back(true);
    vector<bool> codigoDer = obtenerCodigo(nodo->getHijoDer(), baseBuscada, codigoActual);
    if (!codigoDer.empty()) {
        return codigoDer;
    }
    codigoActual.pop_back();

    return {};
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

char ArbolCodificacion::obtenerBaseDeDato(vector<bool> codigoBuscado)
{
    NodoCodificacion* nodoActual = this->raiz;
    for (bool bit : codigoBuscado) {
        if (nodoActual == nullptr) {
            return NULL;
        }
        if (bit == false) {
            nodoActual = nodoActual->getHijoIzq();
        } else {
            nodoActual = nodoActual->getHijoDer();
        }
    }
    if (nodoActual == nullptr || !nodoActual->esHoja()) {
        return NULL;
    }
    return nodoActual->getBase();
}

vector<Base> ArbolCodificacion::obtenerBasesMinimizadas()
{
    return this->bases;
}
