#ifndef MENU_H
#define MENU_H

#include "images.h"

// Componentes

IMAGE background;
IMAGE buttons[1]; // trocar

// Carrega todos os componentes necessarios para o funcionamento do menu
void LoadMenuResources();

// Trata os eventos relacionados ao menu e renderiza os componentes presentes no mesmo 
void Menu();

#endif
