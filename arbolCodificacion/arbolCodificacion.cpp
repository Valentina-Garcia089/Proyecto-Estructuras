#include <iostream>
#include "arbolCodificacion.h"
#include "../SecuenciaGenetica/tad_base.h"
#include <algorithm>

using namespace std;

// Objeto que se puede usar como si fuera una función
struct Comparador {
    bool operator()(NodoCodificacion* a, NodoCodificacion* b) {
        // Devuelve true si "a" tiene una frecuencia mayor a la de "b"
        // Al devolver true, indica que b tiene más prioridad porque "a" es mayor (MIN-HEAP)
        return a->getFrecuencia() > b->getFrecuencia();
    }
};





ArbolCodificacion::ArbolCodificacion(vector<Base> cantidades){
    // <Tipo de dato que guarda la cola, contenedor donde se guardan los datos, estructura que define cómo comparar> 
    priority_queue<NodoCodificacion*, vector<NodoCodificacion*>, Comparador> cola; // frecuencias originales
    priority_queue<NodoCodificacion*, vector<NodoCodificacion*>, Comparador> minHeap; // frecuencias minimizadas

    for (Base& base : cantidades) {
        // Bases con frecuencia > 0 = bases que aparecen en las secuencias genéticas del archivo 
        if (base.obtenerFrecuencia() > 0) {
            NodoCodificacion* nuevoNodo = new NodoCodificacion(base.obtenerBase(), base.obtenerFrecuencia());
            cola.push(nuevoNodo);
        }
    }

    cola.push(new NodoCodificacion('L', 0)); // Nodo de delimitador (Separar secuencias sin usar un entero) - Queda como primer elemento

    int contador = 1;

    //Uso para mantener el rango en 8 bits (cada byte va de 0 a 255 en entero)
    // Minimizar las frecuencias de las bases para que quepan en un solo byte
    while (!cola.empty()) {
        NodoCodificacion* nodoActual = cola.top(); // El menor
        nodoActual->setFrecuencia(contador);
        minHeap.push(nodoActual);

        // No se mete el delimitador ya que no hace parte de las bases de una secuencia genetica
        if (nodoActual->getBase() != 'L'){
            bases.push_back(Base(nodoActual->getBase(),nodoActual->getFrecuencia(),{}));   
        }
        cola.pop(); // Una vez ingresada la base con la frecuencia minimizada en el vector de bases, puede eliminarse de la cola 
        contador+=2;
    }

    while (minHeap.size() > 1) {
        NodoCodificacion* izquierdo = minHeap.top();
        minHeap.pop();
        NodoCodificacion* derecho = minHeap.top();
        minHeap.pop();

        // Los nodos internos no contienen el caracter, solo la suma de las frecuencias
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





// EJ -> A: 0011
vector<bool> ArbolCodificacion::obtenerCodigoDeBase(char baseBuscada) {
    return obtenerCodigo(this->raiz, baseBuscada, {});
}





vector<bool> ArbolCodificacion::obtenerCodigo(NodoCodificacion* nodo, char baseBuscada, vector<bool> codigoActual){
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




//Función generada por IA para imprimir una representación visual del árbol
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





//Función generada por IA para imprimir una representación visual del árbol
void ArbolCodificacion::imprimirArbol() {
    if (this->raiz == nullptr) {
        cout << "El árbol está vacío.\n";
        return;
    }
    imprimirNodo(this->raiz);
}





char ArbolCodificacion::obtenerBaseDeDato(vector<bool> codigoBuscado){
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





vector<Base> ArbolCodificacion::obtenerBasesMinimizadas(){
    return this->bases;
}
