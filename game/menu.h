#ifndef MENU_H
#define MENU_H

#include "images.h"
#include "text.h"

// Componentes

IMAGE background;
Text labels[4];

// Carrega todos os componentes necessarios para o funcionamento do menu
void LoadMenuResources();

// Trata os eventos relacionados ao menu e renderiza os componentes presentes no mesmo 
void Menu();

#endif
