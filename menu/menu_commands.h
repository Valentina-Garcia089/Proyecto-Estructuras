//Declaración para el menú de comandos
#ifndef MENU_COMMANDS_H
#define MENU_COMMANDS_H

#include <iostream>
#include <string>

using namespace std;

void comandoAyuda(string argumento, int momento);
void comandoNoReconocido();
bool archivoCorrecto(string argumento);

#endif