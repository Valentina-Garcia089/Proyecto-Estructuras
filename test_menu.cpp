#include <iostream>
#include <sstream>
#include <string>

#include "menu/menu_commands.h"
#include "Sistema/tad_sistema.h"



using namespace std;

int main () {
    string linea, comando, argumento;
    Sistema sistemita;
    
    do{
        linea = "";
        comando = "";
        argumento = "";
        cout << "\n$ ";
        getline(cin, linea);
        istringstream iss(linea); // Leer la linea palabra por palabra
        iss >> comando >> argumento;
        
        if (comando == "cargar" && !argumento.empty()) {
            if(archivoCorrecto(argumento)){
                cout << "Cargando el archivo " << argumento << "...\n";
                if(sistemita.cargaDeArchivo(argumento)){
                    cout << "Archivo cargado con exito\n";
                    // Solo si se logra cargar un archivo se ejecuta lo siguiente:
                    do{
                        linea = "";
                        comando = "";
                        argumento = "";
                        cout << "\n$ ";
                        getline(cin, linea);
                        istringstream iss(linea);
                        iss >> comando >> argumento;
                        if(comando == "listar_secuencias" && argumento.empty()) {
                            cout << "Listando secuencias...\n";
                            sistemita.listarSecuencias(sistemita.obtenerConjuntoSec());
                        }
                        else if(comando == "histograma" && !argumento.empty()){
                            cout << "Mostrando histograma\n";
                            sistemita.histograma(argumento);
                        }
                        else if(comando == "es_subsecuencia" && !argumento.empty()){
                            sistemita.contarSubsecuencias(argumento);
                            cout << "La subsecuencia " << argumento << " se repite n veces\n";
                        }
                        else if(comando == "enmascarar" && !argumento.empty()){
                            sistemita.enmascararSecuencia(argumento);
                            cout << "Se enmascaró la subsecuencia" << argumento << "\n";
                        }
                        else if(comando == "guardar" && !argumento.empty()){
                            sistemita.guardarSecuencias(argumento);
                            cout << "Las secuencias cargadas se guardaron en el archivo " << argumento << "\n";
                        } 
                        else if (comando == "codificar" && !argumento.empty()){
                            sistemita.codificarSecuencias(argumento);
                        }
                        else if (comando == "decodificar" && !argumento.empty()){
                            sistemita.decodificarSecuencias(argumento);
                        }
                        else if (comando == "ruta_mas_corta" && !argumento.empty()){
                            sistemita.rutaMasCorta(argumento);
                        }
                        else if (comando == "base_remota" && !argumento.empty()){
                            sistemita.baseRemota(argumento);
                        }
                        else if(comando== "ayuda"){
                            comandoAyuda(argumento, 2);
                        }
                        else if (comando == "salir") {
                            break;
                        }
                        else{
                            comandoNoReconocido();
                        }
                    } while (comando != "salir");
                }
            }
            else{
                cout << "El archivo '" << argumento << "' no cumple con el formato esperado\n" ;
            }
            
        }

        else if(comando == "ayuda"){
            comandoAyuda(argumento, 1);
        }
        else if (comando == "salir") {
            break;
        }
        else{
            comandoNoReconocido();
        }
    }while(comando != "salir");

    return 0;
}
