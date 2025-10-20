#include "tad_sistema.h"
#include "../SecuenciaGenetica/tad_secuencia_genetica.h"
#include "../arbolCodificacion/arbolCodificacion.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool Sistema::cargaDeArchivo(string archivito){
    ifstream archivo(archivito);
    string linea;
    string codigo = "";
    SecuenciaGenetica sec;
    vector<char> datos = {};
    int anchoJustificacion = 0;

    if(!archivo.is_open()){
        cout << archivito << " "; 
        printf("no se encuentra o no puede leerse\n");
        return false;
    }
    
    while(getline(archivo, linea)) { // Se leerá linea por linea
        if(linea[0] == '>') {
            // Si hay código pendiente, lo procesamos antes de cambiar de nombre
            if(!codigo.empty()) {
                if (verificarSecuencias(codigo) == false) {
                    cout << "El archivo contiene caracteres no validos. Archivo no cargado.\n";
                    conjuntoSecuencias.clear();
                    return false;
                }
                anchoJustificacion = verificaJustificacion(codigo);
                if (anchoJustificacion == -1) {
                    cout << "El archivo contiene secuencias no justificadas. Archivo no cargado.\n";
                    conjuntoSecuencias.clear();
                    return false;
                }
                for (char c : codigo) {
                    if (c != '\n')
                        datos.push_back(c);
                }
                sec.setDatos(datos);
                sec.setAnchoJustificacion(anchoJustificacion);
                conjuntoSecuencias.push_back(sec);
                codigo = "";
                datos.clear();
            }
            if (linea.substr(1).empty()) {
                cout << "Nombre de secuencia invalido. Archivo no cargado.\n";
                conjuntoSecuencias.clear();
                return false;
            }
            for (vector<SecuenciaGenetica>::iterator s = conjuntoSecuencias.begin(); s != conjuntoSecuencias.end(); ++s) {
                if (s->getNombre().compare(linea.substr(1).c_str()) == 0) {
                    cout << "Nombres de secuencias duplicados. Archivo no cargado.\n";
                    conjuntoSecuencias.clear();
                    return false;
                }
            }
            sec.setNombre(linea.substr(1)); // (Devuelve una subcadena de linea desde la posición 1)
        } else {
            codigo += linea + "\n";
        }
    }
    // Procesa la última secuencia 
    if(!codigo.empty()) {
        if (verificarSecuencias(codigo) == false) {
            cout << "El archivo contiene caracteres no validos. Archivo no cargado.\n";
            conjuntoSecuencias.clear();
            return false;
        }
        anchoJustificacion = verificaJustificacion(codigo);
        if (anchoJustificacion == -1) {
            cout << "El archivo contiene secuencias no justificadas. Archivo no cargado.\n";
            conjuntoSecuencias.clear();
            return false;
        }
        for (char c : codigo) {
            if (c != '\n')
                datos.push_back(c);
        }
        sec.setDatos(datos);
        sec.setAnchoJustificacion(anchoJustificacion);
        conjuntoSecuencias.push_back(sec);
    }

    if (conjuntoSecuencias.empty()) {
        cout << archivito << " no contiene ninguna secuencia.\n";
        return false;
    }

    cout << conjuntoSecuencias.size() << " secuencias cargadas correctamente de " << archivito << '\n';
    
    for (SecuenciaGenetica& s : conjuntoSecuencias) {
        s.contarBases();
    }
    return true;
}





void Sistema::listarSecuencias(vector<SecuenciaGenetica> secuencias){
    vector<bool> bases = {false, false, false, false, false}; // A, C, G, T, U
    vector <Base> conteo;

    if (secuencias.empty()) {
        cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    for (SecuenciaGenetica& sec : secuencias) {
        bases = {false, false, false, false, false}; // nueva linea para arreglar contar bases.
        conteo = sec.getConteo();
        for (char e: sec.getDatos()){
            for (Base& base : conteo) {
                // Si la base preestablecida es igual a la base leida de la secuencia genetica, entonces:
                if (base.obtenerBase() == e) {
                    if (sec.contieneChar(base.getRepresenta(), 'A')) {
                        bases[0] = true;
                        break;
                    }
                    if (sec.contieneChar(base.getRepresenta(), 'C')) {
                        bases[1] = true;
                        break;
                    }
                    if (sec.contieneChar(base.getRepresenta(), 'G')) {
                        bases[2] = true;
                        break;
                    }
                    if (sec.contieneChar(base.getRepresenta(), 'T')) {
                        bases[3] = true;
                        break;
                    }
                    if (sec.contieneChar(base.getRepresenta(), 'U')) {
                        bases[4] = true;
                        break;
                    }
                }
            }
        }

        int count = 0;

        for (bool b : bases) {
            if (b == true) {
                count++;
            }
        }

        bool encontrado = false;
        vector<char> tipoBases = {'A', 'C', 'G', 'T', 'U'};

        // Recorre la secuencia y verificar si cada caracter está en tipoBases
        for (char e : sec.getDatos()) {
            encontrado = false;
            for (int i = 0; i < tipoBases.size(); ++i) {
                if (e == tipoBases[i]) {
                    encontrado = true;
                    break;
                }
            }
        }

        // data(): devuelve un puntero a la primera posición del vector
        // Copia .size() elementos desde la primera posición del vector
        string nombreDatos(sec.getDatos().data(), sec.getDatos().size());

        if (encontrado) {
            cout << "Secuencia " << sec.getNombre() << '\n' << nombreDatos << "\ntiene almenos " << count << " bases." << endl;
        } else {
            cout << "Secuencia " << sec.getNombre() << '\n' << nombreDatos << "\ncontiene " << count << " bases." << endl;
        }
    }
}





void Sistema::histograma(string nombreSecuencia){
    for(SecuenciaGenetica& recorre : conjuntoSecuencias){
        if(recorre.getNombre() == nombreSecuencia || recorre.getNombre() == nombreSecuencia + "\r"){
            cout << recorre.getNombre();

            cout << "\n";
            for(Base& muestraFrec : recorre.getConteo()){
                cout << "\n" << muestraFrec.obtenerBase() << ": " << muestraFrec.obtenerFrecuencia() << " repeticiones.";
            }
            return;
        }
    }
    cout << "Secuencia invalida\n";
}





void Sistema::contarSubsecuencias(string subsecuencia)
{
    vector<SecuenciaGenetica>::iterator it = conjuntoSecuencias.begin();
    int total = 0;

    for (; it != conjuntoSecuencias.end(); it++){
        total += it->esSubsecuencia(subsecuencia);
    }

    printf("Total de ocurrencias de las secuencias es :%d\n", total);
}




bool Sistema::verificarSecuencias(string secuencia)
{
    //Podría ser un string
    vector<char> bases_validas = {'A', 'C', 'G', 'T', 'U', 'R', 'Y', 'K', 'M', 'S', 'W', 
                                  'B', 'D', 'H', 'V', 'N', 'X', '-', '\n', '\r'};

    // Declaración de variable tipo string que hace que tenga cada char de "bases_validas"
    string caracteresValidos(bases_validas.begin(), bases_validas.end());

    //Verifica que cada carácter en la secuencia sea un carácter válido
    for (char c : secuencia) {
        if (caracteresValidos.find(c) == string::npos){
            cout << "Caracter invalido: " << c << "\n";
            return false; // Carácter no válido encontrado
        }
    }

    return true; // Todos los caracteres son válidos
}





int Sistema::verificaJustificacion(string secuencia)
{
    vector<int> tam;
    int inicio = 0;
    int pos = 0;

    // Búsqueda de líneas en la secuencia empezando desde la posición (inicio)
    while ((pos = secuencia.find('\n', inicio)) != string::npos) {
        //Va añadiendo los tamaños de las líneas encontradas
        // pos es la posición donde encontró '\n' e "inicio" es donde empieza la linea
        tam.push_back(pos - inicio);

        //Cambia el inicio para la siguiente busqueda despues del '\n' ("siguiente linea")
        inicio = pos + 1;
    }

    // Si hay texto después del último '\n', cuenta esa línea, necesario dado que la última línea puede no termina en '\n'

    // Si inicio todavía es menor al tamaño total significa que queda texto sin procesar
    if (inicio < secuencia.size()) {
        tam.push_back(secuencia.size() - inicio);
    }

    // Si no hay líneas, retorna -1 (O sea fallo en justificación)
    if (tam.empty()) 
        return -1;

    //Compara todos los tamaños de las líneas 
    int tam_ref = tam[0];
    // Llega hasta la penultima niña porque la linea final si podría tener un tamaño diferente
    for (int i = 1; i + 1 < tam.size(); ++i) {
        if (tam[i] != tam_ref) 
            return -1;
    }

    // La última línea puede ser menor o igual al resto, PERO NO MAYOR
    if (tam.back() > tam_ref) 
        return -1;

    //Si la secuencia está justificada, retorna la cantidad de caracteres por línea
    return tam_ref;
}


void Sistema::enmascararSecuencia(string subsecuencia) {
    int total = 0;
    for (SecuenciaGenetica& sec : conjuntoSecuencias) {
        vector<char> datos = sec.getDatos();
        int tam = subsecuencia.size();
        int cont = 0;

        for (int t = 0; t <= datos.size() - tam; t++) {
            if (sec.esIgual(string(datos.begin() + t, datos.begin() + t + tam), subsecuencia)) {
                cont++;
                for (int j = 0; j < tam; j++) {
                    datos[t + j] = 'X';
                }
            }
        }

        if (cont > 0) {
            sec.setDatos(datos);
        }
        total += cont;
    }
    if (total > 0) {
            cout << total << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria.";
    } else {
            cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada.";
    }
}

//TODO: Cambiar a codificar/comprimir
void Sistema::codificarSecuencias(string nombreArchivo)
{   
    if (nombreArchivo.find(".fabin") == string::npos) {
        nombreArchivo += ".fabin";
    }

    // Abrir en modo binario
    ofstream salida(nombreArchivo, ios::out | ios::trunc | ios::binary);
    if (!salida.is_open()) {
        cout << "Error guardando en " << nombreArchivo << ".\n";
        return;
    }

    vector<vector<Base>> todosLosConteos;
    for (SecuenciaGenetica& sec : conjuntoSecuencias) {
        todosLosConteos.push_back(sec.getConteo());
    }

    vector<Base> nuevoConteo;

    for (vector<Base>& conteo : todosLosConteos) {
        for (Base& base : conteo) {
            bool encontrado = false;
            for (Base& nuevoBase : nuevoConteo) {
                if (nuevoBase.obtenerBase() == base.obtenerBase()) {
                    nuevoBase = nuevoBase + base;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                nuevoConteo.push_back(base);
            }
        }
    }
    
    ArbolCodificacion arbol(nuevoConteo);
    arbol.imprimirArbol();

    vector<Base> bases = arbol.obtenerBasesMinimizadas();

    u_int8_t tam_ref = static_cast<u_int8_t>(bases.size());

    // Guardar la cantidad de bases dentro del archivo (escribir el valor, no una dirección inválida)
    salida.write(reinterpret_cast<const char*>(&tam_ref), sizeof(tam_ref));

    for (Base& base : bases) {
        cout << base.obtenerBase() << " " << base.obtenerFrecuencia() << endl;
        char base_char = base.obtenerBase();
        u_int8_t freq = static_cast<u_int8_t>(base.obtenerFrecuencia());
        salida.write(reinterpret_cast<const char*>(&base_char), sizeof(base_char));
        salida.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }

    for (SecuenciaGenetica& sec : conjuntoSecuencias) {
        cout << "Codificando secuencia: " << sec.getNombre() << endl;
        vector<char> datos = sec.getDatos();
        vector<bool> codigoCompleto;

        u_int8_t anchoJustificacion = static_cast<u_int8_t>(sec.getAnchoJustificacion());
        salida.write(reinterpret_cast<const char*>(&anchoJustificacion), sizeof(anchoJustificacion));
        u_int8_t tam_nombre = static_cast<u_int8_t>(sec.getNombre().size());
        salida.write(reinterpret_cast<const char*>(&tam_nombre), sizeof(tam_nombre));
        salida.write(sec.getNombre().c_str(), sec.getNombre().size());

        for (char c : datos) {
            vector<bool> codigoBase = arbol.obtenerCodigoDeBase(c);
            codigoCompleto.insert(codigoCompleto.end(), codigoBase.begin(), codigoBase.end());
        }

        vector<bool> codigoDelim = arbol.obtenerCodigoDeBase('L');
        codigoCompleto.insert(codigoCompleto.end(), codigoDelim.begin(), codigoDelim.end());

        // Agrupar bits en bytes
        size_t num_bytes = (codigoCompleto.size() + 7) / 8;
        vector<u_int8_t> bytes(num_bytes, 0);
        for (size_t i = 0; i < codigoCompleto.size(); ++i) {
            if (codigoCompleto[i]) {
                bytes[i / 8] |= (1 << (7 - (i % 8)));
            }
        }
        salida.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }

    salida.close();
}

void Sistema::decodificarSecuencias(string nombreArchivo){
    ifstream entrada(nombreArchivo, ios::in | ios::binary);
    if (!entrada.is_open()) {
        cout << "Error leyendo en " << nombreArchivo << ".\n";
        return;
    }

    u_int8_t tam_ref_leido;
    entrada.read(reinterpret_cast<char*>(&tam_ref_leido), sizeof(tam_ref_leido));
    cout << "Tamaño de referencia: " << (int)tam_ref_leido << endl;

    vector<Base> bases_leidas;

    for (int i = 0; i < tam_ref_leido; i++) {
        char base_leida;
        u_int8_t frecuencia_leida;
        entrada.read(reinterpret_cast<char*>(&base_leida), sizeof(base_leida));
        entrada.read(reinterpret_cast<char*>(&frecuencia_leida), sizeof(frecuencia_leida));
        bases_leidas.push_back(Base(base_leida, frecuencia_leida, {}));
        cout << "Base leida: " << base_leida << " Frecuencia leida: " << (int)frecuencia_leida << endl;
    }
    entrada.close();

    ArbolCodificacion arboldecodificacion(bases_leidas);

    while(!entrada.eof()){
        vector<bool> codigoLeido;
        char byte_leido;
        entrada.read(&byte_leido, sizeof(byte_leido));
        for (int i = 7; i >= 0; i--) {
            bool bit = (byte_leido >> i) & 1;
            codigoLeido.push_back(bit);
        }
    }



    arboldecodificacion.imprimirArbol();
}

void Sistema::arbolCodificacion(string nombreSecuencia){
    for(SecuenciaGenetica& recorre : conjuntoSecuencias){
        if(recorre.getNombre() == nombreSecuencia || recorre.getNombre() == nombreSecuencia + "\r"){
            for (Base& base : recorre.getConteo() ) {
                cout << base.obtenerBase() << ": " << base.obtenerFrecuencia() << " repeticiones.\n";
            }
            ArbolCodificacion arbol(recorre.getConteo());
            cout << "Árbol de codificación para la secuencia " << recorre.getNombre() << ":\n";
            arbol.imprimirArbol();
            return;
        }
    }
    cout << "Secuencia invalida\n";
}


vector <SecuenciaGenetica> Sistema:: obtenerConjuntoSec(){
    return conjuntoSecuencias;
}

void Sistema::guardarSecuencias(string nombre_archivo) {

    ofstream salida(nombre_archivo + ".fa", ios::out | ios::trunc);
    if (!salida.is_open()) {
        cout << "Error guardando en " << nombre_archivo << ".\n";
        return;
    }

    int contador = 0;

    for (SecuenciaGenetica& sec : conjuntoSecuencias) {
        salida << ">" << sec.getNombre() << "\n";

        string datos(sec.getDatos().data(), sec.getDatos().size());

        int temp = 0;
        for (char c : datos) {
            salida << c;
            if (temp == sec.getAnchoJustificacion() - 1) {
                salida << "\n";
                temp = 0;
                continue;
            }
            temp++;
        }
        salida << "\n";
        contador++;
    }
    
    salida.close();

    if (contador == 1) {
        cout << "Se guardó " << contador << " secuencia en " << nombre_archivo << ".\n";
    } else {
        cout << "Se guardaron " << contador << " secuencias en " << nombre_archivo << ".\n";
    }
}