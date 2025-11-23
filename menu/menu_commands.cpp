#include <iostream>
#include <sstream>

#include "menu_commands.h"
#include <string>

using namespace std;

// Ayudas para cada momento en el que el usuario se encuentre en el menú
void comandoAyuda(string argumento, int momento) {
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
            printf("Comandos disponibles: listar_secuencias, histograma, es_subsecuencia, enmascarar, codificar, decodificar, guardar , ruta_mas_corta, base_remota, salir, ayuda\n");
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
            else if (argumento == "codificar"){
                printf("Uso: codificar <nombre_archivo>\n");
                printf("Descripción: codifica y guarda las secuencias cargadas en memoria en un archivo binario.\n");
            }
            else if (argumento == "decodificar"){
                printf("Uso: decodificar <nombre_archivo>\n");
                printf("Descripción: decodifica un archivo binario y carga las secuencias en memoria.\n");
            } 
            else if (argumento == "ruta_mas_corta"){
                printf("Uso: ruta_mas_corta <descripcion_secuencia> <origen> <destino>\n");
                printf("Descripción: obtiene la ruta más corta entre dos bases en la secuencia.\n");
                printf("El origen y destino deben ser las posiciones (fila,columna) de las bases en la secuencia.\n");
                printf("Ejemplo: ruta_mas_corta 0 0 2 3\n");
            }
            else if (argumento == "base_remota"){
                printf("Uso: base_remota <descripcion_secuencia> <origen>\n");
                printf("Descripción: obtiene la base más lejana desde una base origen en la secuencia.\n");
                printf("El origen debe ser la posición (fila,columna) de la base en la secuencia.\n");
                printf("Ejemplo: base_remota 0 0\n");
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



// La función 
bool archivoCorrecto(string argumento){
    // Devuelve la posición de la cadena a buscar
    // Si no la encuentr devuelve string::npos que es un número muy grande
    if(argumento.find(".fa") != string::npos || argumento.find(".fasta") != string::npos){
        return true;
    }
    return false;
}