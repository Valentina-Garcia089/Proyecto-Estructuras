#include "tad_sistema.h"
#include "tad_secuencia_genetica.h"
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
        printf("No fue posible abrir el archivo\n");
        return false;
    }
    
    while(getline(archivo, linea)) {// Se leerá linea por linea
        if((linea[0] == '>') || archivo.peek() == EOF) { // Si al iniciar una linea, se encuentra este caracter en la posición 0:
            if(!codigo.empty()){

                if (archivo.peek() == EOF) {
                    codigo += linea; // Añade la última línea leída si es parte del código
                }

                cout << codigo << "\n";

                // Verifica que la secuencia solo contenga caracteres válidos
                if (verificarSecuencias(codigo) == false) {
                    cout << "El archivo contiene caracteres no validos. Archivo no cargado.\n";
                    conjuntoSecuencias.clear();
                    return false;
                }

                //Verifica que las lineas código cumplan con la justificación (anchura)
                anchoJustificacion = verificaJustificacion(codigo);
                if (anchoJustificacion == -1) {
                    cout << "El archivo contiene secuencias no justificadas. Archivo no cargado.\n";
                    conjuntoSecuencias.clear();
                    return false;
                }

                // Guardado de caracteres en el vector de chars
                for (char c : codigo) {
                    if (c != '\n')
                        datos.push_back(c);
                }
                
                // Guardado de la secuencia en el objeto 
                sec.setDatos(datos);
                sec.setAnchoJustificacion(anchoJustificacion);
                conjuntoSecuencias.push_back(sec);

                // Reinicio de variables para la próxima secuencia
                codigo = "";
                datos.clear();
            }
            sec.setNombre(linea.substr(1)); // Guardará el nombre después del caracter
        }
        else{
            codigo += linea + "\n"; // No se hace push_back porque esto espera un char, no un string completo
        }
    }

    return true;
}



void Sistema::listarSecuencias(vector<SecuenciaGenetica> secuencias){
    vector <SecuenciaGenetica>::iterator it;
    it = secuencias.begin();
    vector <char>::iterator it_char;
    string dato = "";

    //Iteración del vector con iteradores
    for (; it != secuencias.end(); it++){
        cout << it->getNombre() << "\n";
        
        string datos(it->getDatos().data(), it->getDatos().size());
        cout << datos << "\n";
        
    }
}


void Sistema::histograma(string nombreSecuencia){
    for(SecuenciaGenetica& recorre : conjuntoSecuencias){
        if(recorre.getNombre() == nombreSecuencia || recorre.getNombre() == nombreSecuencia + "\r"){
            cout << recorre.getNombre();
            recorre.contarBases();

            cout << "\n";
            for(Base& muestraFrec : recorre.getConteo()){
                cout << "\n" << muestraFrec.obtenerBase() << ": " << muestraFrec.obtenerFrecuencia() << " repeticiones.\n";
            }
        }
    }
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
                                  'B', 'D', 'H', 'V', 'N', 'X', '-', '\n'};

    string caracteresValidos(bases_validas.begin(), bases_validas.end());

    //Verifica que cada carácter en la secuencia sea un carácter válido
    for (char c : secuencia) {
        if (caracteresValidos.find(c) == string::npos){
            return false; // Carácter no válido encontrado
        }
    }

    return true; // Todos los caracteres son válidos
}

int Sistema::verificaJustificacion(string secuencia)
{
    vector<size_t> tam;
    size_t inicio = 0;
    size_t pos = 0;

    // Búsqueda de líneas en la secuencia
    while ((pos = secuencia.find('\n', inicio)) != string::npos) {
        //Va añadiendo los tamaños de las líneas encontradas
        tam.push_back(pos - inicio);

        //Cambia el inicio para la siguiente busqueda
        inicio = pos + 1;
    }

    // Si hay texto después del último '\n', cuenta esa línea, necesario dado que la última línea puede no termina en '\n'
    if (inicio < secuencia.size()) {
        tam.push_back(secuencia.size() - inicio);
    }

    // Si no hay líneas, retorna -1 (Osea fallo en justificación)
    if (tam.empty()) 
        return -1;

    //Compara todos los tamaños de las líneas 
    size_t tam_ref = tam[0];
    for (size_t i = 1; i + 1 < tam.size(); ++i) {
        if (tam[i] != tam_ref) 
            return -1;
    }

    // La última línea puede ser menor o igual al resto
    if (tam.back() > tam_ref) 
        return -1;

    //Si la secuencia está justificada, retorna la cantidad de caracteres por línea
    return tam_ref;
}

vector <SecuenciaGenetica> Sistema:: obtenerConjuntoSec(){
    return conjuntoSecuencias;
}