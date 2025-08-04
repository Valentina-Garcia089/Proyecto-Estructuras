#include <iostream>

using namespace std;

void main () {
    string comando, argumento;

    do{
        cout << "$ ";
        cin >> comando >> argumento;
        
        if(comando == "cargar"){
            printf("\nCargando el archivo %s...", argumento);
        }

        else if(comando == "ayuda"){
            if(argumento.empty()){
                printf("\nComandos disponibles: cargar, salir, ayuda");
            }
            else{
                if(argumento == "cargar"){
                    printf("\nUso: cargar <ruta_archivo>");
                    printf("\nDescripción: carga de archivo que contienen códigos genéticos.");
                }
                else if(argumento == "salir"){
                    printf("\nUso: salir");
                    printf("\nDescripción: salida del programa.");
                }
                
            }
        }
        
        else{
            printf("\nComando no reconocido. Escribe 'ayuda' para ver las opciones de comandos.");
            printf("\nSi necesitas ayuda con un comando especifico, escribe 'ayuda <comando>'");
        }

    }while(comando != "salir");
}