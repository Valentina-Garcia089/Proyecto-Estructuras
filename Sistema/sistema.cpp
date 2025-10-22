#include "tad_sistema.h"
#include "../SecuenciaGenetica/tad_secuencia_genetica.h"
#include "../arbolCodificacion/arbolCodificacion.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

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
    int tamañoRef = tam[0];
    // Llega hasta la penultima niña porque la linea final si podría tener un tamaño diferente
    for (int i = 1; i + 1 < tam.size(); ++i) {
        if (tam[i] != tamañoRef) 
            return -1;
    }

    // La última línea puede ser menor o igual al resto, PERO NO MAYOR
    if (tam.back() > tamañoRef) 
        return -1;

    //Si la secuencia está justificada, retorna la cantidad de caracteres por línea
    return tamañoRef;
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
        // Guardo en el vector nuevo un vector que contiene la base, la frecuencia y si es el caso las letras que representan a esta misma base 
        todosLosConteos.push_back(sec.getConteo());
    }

    vector<Base> nuevoConteo;

    // Tomar cada conteo (base, frecuencia y representación (NO USADO)) de cada secuencia genética y  
    for (vector<Base>& conteo : todosLosConteos) {
        for (Base& base : conteo) {
            bool encontrado = false;
            for (Base& nuevoBase : nuevoConteo) {
                if (nuevoBase.obtenerBase() == base.obtenerBase()) {
                    // Sumar frecuencias de las bases de cada Secuencia genética
                    nuevoBase = nuevoBase + base;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                nuevoConteo.push_back(base); // Mete todas las bases existentes de la secuencia al vector de bases
            }
        }
    }
    
    // Se crea un arbol de tipo ArbolCodificación al cual se le pasará el TOTAL de las bases con sus frecuencias
    ArbolCodificacion arbol(nuevoConteo);
    arbol.imprimirArbol(); // Se hace solo para verificar cómo queda el arbol

    vector<Base> bases = arbol.obtenerBasesMinimizadas();

    // Obtenemos el num de elementos en el vector "bases" y casteamos el valor a un tipo que ocupa solo un byte en memoria
    uint8_t tamañoRef = static_cast<uint8_t>(bases.size());

    //Los binarios se manejan byte a byte, por esto es necesario hacer la reinterpretación como un puntero a byte
    //E indica los bytes a escribir
    salida.write(reinterpret_cast<const char*>(&tamañoRef), sizeof(tamañoRef));

    //Por cada base con frecuencia minimizada, se escribirá en el archivo su base y su respectiva frecuencia
    for (Base& base : bases) {
        cout << base.obtenerBase() << " " << base.obtenerFrecuencia() << endl;
        char base_char = base.obtenerBase();
        uint8_t freq = static_cast<uint8_t>(base.obtenerFrecuencia());
        salida.write(reinterpret_cast<const char*>(&base_char), sizeof(base_char));
        salida.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }

    //Por cada secuencia genética en el archivo, se escribirá en el archivo binario el ancho de la justificación, el nombre de la secuencia con su tamaño y la secuencia (datos)
    for (SecuenciaGenetica& sec : conjuntoSecuencias) {
        cout << "Codificando secuencia: " << sec.getNombre() << endl;
        vector<char> datos = sec.getDatos(); //Corresponde a los datos de UNA secuencia genética
        vector<bool> codigoCompleto;

        uint16_t anchoJustificacion = static_cast<uint16_t>(sec.getAnchoJustificacion());
        salida.write(reinterpret_cast<const char*>(&anchoJustificacion), sizeof(anchoJustificacion));
        uint8_t tam_nombre = static_cast<uint8_t>(sec.getNombre().size());
        salida.write(reinterpret_cast<const char*>(&tam_nombre), sizeof(tam_nombre));
        salida.write(sec.getNombre().c_str(), sec.getNombre().size());

        //Con el arbol de codificación, por cada base dentro de UNA secuencia, se debe obtener su codigo
        for (char c : datos) {
            vector<bool> codigoBase = arbol.obtenerCodigoDeBase(c);
            codigoCompleto.insert(codigoCompleto.end(), codigoBase.begin(), codigoBase.end());
        }

        //Se guarda en un vector<bool> ya que está optimizado solo para usar 1 bit por valor
        //Con el delimitador sabremos cuando termina una secuencia
        vector<bool> codigoDelim = arbol.obtenerCodigoDeBase('L');
        codigoCompleto.insert(codigoCompleto.end(), codigoDelim.begin(), codigoDelim.end());

        // Agrupar bits en bytes
        // Calcular la cantidad de bytes necesarios
        size_t numBytes = (codigoCompleto.size() + 7) / 8;
        //Crear el vector ya iniciado con el tamaño para la cantidad de bytes necesarios
        vector<uint8_t> bytes(numBytes, 0);
        // |= es la operación OR, se usa para establecer bits individuales en el byte
        // [i / 8] Indica que byte debe almacenar al bit actual
        // (1 << (7 - (i % 8))) calcula la posición del bit dentro del byte
        for (size_t i = 0; i < codigoCompleto.size(); ++i) {
            // Solo entra si el bit actual es 1 (verdadero) porque el byte ya tiene 0s por defecto
            if (codigoCompleto[i]) {
                bytes[i / 8] |= (1 << (7 - (i % 8)));
            }
        }

        //Escribe los datos
        salida.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }
    salida.close();
}





void Sistema::decodificarSecuencias(string nombreArchivo){
    if (nombreArchivo.find(".fabin") == string::npos) {
        cout << "Tipo de archivo invalido, archivo .fabin necesario" << endl;
        return;
    }

    ifstream entrada(nombreArchivo, ios::in | ios::binary);
    if (!entrada.is_open()) {
        cout << "Error leyendo en " << nombreArchivo << ".\n";
        return;
    }

    // Leer cantidad de bases que estan en el archivo (Lee un byte por ser de tipo uint8_t)
    uint8_t tamañoRef_leido;
    entrada.read(reinterpret_cast<char*>(&tamañoRef_leido), sizeof(tamañoRef_leido));
    if (!entrada) {
        cout << "Archivo corrupto o incompleto (header).\n";
        entrada.close();
        return;
    }
    cout << "Tamaño de referencia: " << (int)tamañoRef_leido << endl;

    //Leer las bases necesarias para el arbol
    vector<Base> bases_leidas;
    for (int i = 0; i < tamañoRef_leido; i++) {
        char base_leida;
        uint8_t frecuencia_leida;
        entrada.read(reinterpret_cast<char*>(&base_leida), sizeof(base_leida));
        entrada.read(reinterpret_cast<char*>(&frecuencia_leida), sizeof(frecuencia_leida));
        if (!entrada) {
            cout << "Dato inesperado dentro del archivo.\n";
            entrada.close();
            return;
        }
        bases_leidas.push_back(Base(base_leida, frecuencia_leida, {}));
        cout << "Base leida: " << base_leida << " Frecuencia leida: " << (int)frecuencia_leida << endl;
    }

    // Construir árbol de decodificación
    ArbolCodificacion arboldecodificacion(bases_leidas);

    // Reemplazar todas las secuencias en memoria por las decodificadas
    conjuntoSecuencias.clear();

    bool seguir = true;
    bool finArchivo = false;

    //Empezar a leer las secuencias
    while (!finArchivo) {
        // Leer el ancho de justificacion
        uint16_t anchoJust;
        if (!entrada.read(reinterpret_cast<char*>(&anchoJust), sizeof(anchoJust))) break;

        // Leer el tamaño del nombre
        uint8_t tam_nombre;
        if (!entrada.read(reinterpret_cast<char*>(&tam_nombre), sizeof(tam_nombre))) break;

        // 
        string nombreSeq;
        if (tam_nombre > 0) {
            nombreSeq.resize(tam_nombre);
            entrada.read(&nombreSeq[0], tam_nombre);
            if (!entrada) {
                cout << "Error al leer el nombre de la secuencia" << endl;
                break;
            }
        }

        // Decodificar bits hasta encontrar el delimitador 'L' o EOF
        vector<char> datos_decodificados;
        vector<bool> codigoActual;
        bool secuenciaTerminada = false;

        // Leer los bytes
        while (!secuenciaTerminada) {
            uint8_t byte_leido;
            //Por si acaso de llega al EOF 
            if (!entrada.read(reinterpret_cast<char*>(&byte_leido), sizeof(byte_leido))) {
                // EOF alcanzado: cualquier bit pendiente es padding, descartarlo.
                // Indicar fin de archivo para salir también del bucle externo y evitar bloqueo.
                finArchivo = true;
                break;
            }

            //Se procesa cada byte de derecha a izq
            for (int i = 7; i >= 0; --i) {
                //Se mueve el bit para tomar el valor de cada uno 
                //y meterlo dentro del vector<bool>
                bool bit = (byte_leido >> i) & 1;
                codigoActual.push_back(bit);
                //Se intenta decodificar la secuencia de bits
                char posible = arboldecodificacion.obtenerBaseDeDato(codigoActual);
                if (posible != '\0') {
                    if (posible == 'L') {
                        //Se termina la secuenia
                        codigoActual.clear();
                        secuenciaTerminada = true;
                        break;
                    } else {
                        //Si no se termina, se agrega el dato al vector
                        datos_decodificados.push_back(posible);
                        codigoActual.clear();
                    }
                }
            }
        }

        // Crear y guardar la secuencias
        SecuenciaGenetica sec;
        sec.setNombre(nombreSeq);
        sec.setDatos(datos_decodificados);
        sec.setAnchoJustificacion(static_cast<int>(anchoJust));
        conjuntoSecuencias.push_back(sec);
        if (finArchivo) break;
    }

    entrada.close();

    // Re-contar las bases
    for (SecuenciaGenetica& s : conjuntoSecuencias) {
        s.contarBases();
    }

    cout << "Decodificación finalizada. Se cargaron " << conjuntoSecuencias.size() << " secuencias en memoria.\n";
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
    bool primero = true;


    for (SecuenciaGenetica& sec : conjuntoSecuencias) {
        int temp = 0;
        if (primero){
            salida << ">" << sec.getNombre() << "\n";
            primero = false;
        } else {
            salida << "\n>" << sec.getNombre() << "\n";
        }
        

        string datos(sec.getDatos().data(), sec.getDatos().size());

        
        for (char c : datos) {
            salida << c;
            if (temp == sec.getAnchoJustificacion() - 1) {
                salida << "\n";
                temp = 0;
                continue;
            }
            temp++;
        }

        contador++;
    }
    salida.close();

    if (contador == 1) {
        cout << "Se guardó " << contador << " secuencia en " << nombre_archivo << ".\n";
    } else {
        cout << "Se guardaron " << contador << " secuencias en " << nombre_archivo << ".\n";
    }
}