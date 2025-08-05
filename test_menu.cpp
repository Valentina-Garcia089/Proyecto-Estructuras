#include <iostream>
#include <sstream>
#include <string>

#include "menu_commands.h"


using namespace std;

int main () {
    string linea, comando, argumento;
    
    do{
        linea = "";
        comando = "";
        argumento = "";
        cout << "\n$ ";
        getline(cin, linea);
        istringstream iss(linea); // Leer la linea palabra por palabra
        iss >> comando >> argumento;
        
        if (comando == "cargar" && !argumento.empty()) {
            cout << "Cargando el archivo " << argumento << "...\n";
            do{
                // Solo si se logra cargar un archivo se ejecuta lo siguiente:
                linea = "";
                comando = "";
                argumento = "";
                cout << "\n$ ";
                getline(cin, linea);
                istringstream iss(linea);
                iss >> comando >> argumento;
                if(comando == "listar_secuencias" && argumento.empty()) {
                    cout << "Listando secuencias...\n";
                }
                else if(comando == "histograma" && !argumento.empty()){
                    cout << "Mostrando histograma\n";
                }
                else if(comando == "es_subsecuencia" && !argumento.empty()){
                    cout << "La subsecuencia " << argumento << " se repite n veces\n";
                }
                else if(comando == "enmascarar" && !argumento.empty()){
                    cout << "Se enmascaró la subsecuencia" << argumento << "\n";
                }
                else if(comando == "guardar" && !argumento.empty()){
                    cout << "Las secuencias cargadas se guardaron en el archivo " << argumento << "\n";
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
