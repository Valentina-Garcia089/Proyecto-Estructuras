#include <iostream>
#include <sstream>

#include "menu_commands.hxx"


// Ayudas para cada momento en el que el usuario se encuentre en el menú
void comandoAyuda(std::string argumento, int momento) {
    if(argumento == "salir"){
        printf("Uso: salir\n");
        printf("Descripción: salida del programa.\n");
    }

    else if(momento == 1) {
        if(argumento.empty()){
            printf("Comandos disponibles: cargar, salir, ayuda\n");
        }
        else{
            if(argumento == "cargar"){
                printf("Uso: cargar <ruta_archivo>\n");
                printf("Descripción: carga de archivo que contienen códigos genéticos.\n");
            }
            else {
                comandoNoReconocido();
            }
        }
    }

    else if(momento == 2){
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
            else{
                comandoNoReconocido();
            }
        }
    }
}


// Mensajes para cuando el usuario ingresa un comando no reconocido
void comandoNoReconocido(){
    printf("Comando no reconocido. Escribe 'ayuda' para ver las opciones de comandos.\n");
    printf("Si necesitas ayuda con un comando especifico, escribe 'ayuda <comando>'\n");
}