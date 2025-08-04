#include <iostream>
#include <sstream>
#include <string>

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
                    if(argumento.empty()){
                        printf("Comandos disponibles: listar_secuencias, histograma, es_subsecuencia, enmascarar, guardar, salir, ayuda\n");
                    }
                    else{
                        if(argumento == "listar_secuencias"){
                            printf("Uso: listar_secuencias\n");
                            printf("Descripción: imprime la cantidad de secuencias y su información.\n");
                        }
                        else if(argumento == "histograma"){
                            printf("Uso: histograma <descripcion_secuencia>\n");
                            printf("Descripción: imprime la frecuencia de cada código en la secuencia, definida por cada salto de linea.\n");
                        }
                        else if(argumento == "es_subsecuencia"){
                            printf("Uso: es_subsecuencia <subsecuencia>\n");
                            printf("Descripción: Determina si una subsecuencia existe dentro de una secuencia ya cargada.\n");
                        }
                        else if(argumento == "enmascarar"){
                            printf("Uso: enmascarar <subsecuencia>\n");
                            printf("Descripción: Enmascara una subsecuencia dada por el usuario si existe.\n");
                        }
                        else if(argumento == "guardar"){
                            printf("Uso: guardar <nombre_archivo>\n");
                            printf("Descripción: guarda en el archivo las secuencias cargadas en memoria.\n");
                        }
                        else if(argumento == "salir"){
                            printf("Uso: salir\n");
                            printf("Descripción: salida del programa.\n");
                        }
                    }
                }
                else if (comando == "salir") {
                    break;
                }
                else{
                    printf("Comando no reconocido. Escribe 'ayuda' para ver las opciones de comandos.\n");
                    printf("Si necesitas ayuda con un comando especifico, escribe 'ayuda <comando>'\n");
                }
            } while (comando != "salir");
            
        }

        else if(comando == "ayuda"){
            if(argumento.empty()){
                printf("Comandos disponibles: cargar, salir, ayuda\n");
            }
            else{
                if(argumento == "cargar"){
                    printf("Uso: cargar <ruta_archivo>\n");
                    printf("Descripción: carga de archivo que contienen códigos genéticos.\n");
                }
                else if(argumento == "salir"){
                    printf("so: salir\n");
                    printf("Descripción: salida del programa.\n");
                }
                
            }
        }

        else if (comando == "salir") {
            break;
        }
        
        else{
            printf("Comando no reconocido. Escribe 'ayuda' para ver las opciones de comandos.\n");
            printf("Si necesitas ayuda con un comando especifico, escribe 'ayuda <comando>'\n");
        }

    }while(comando != "salir");

    return 0;
}