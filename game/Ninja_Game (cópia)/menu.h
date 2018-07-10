#ifndef MENU_H
#define MENU_H

#include "images.h"
#include <SDL2/SDL_mixer.h>

// Componentes

IMAGE menuBackground;
TEXT menuLabels[4];
TTF_Font* menuFont;
Mix_Chunk* menuButtonClick;
Mix_Music* introduction;

// Carrega todos os componentes necessarios para o funcionamento do menu
void LoadMenuResources();

// Trata os eventos relacionados ao menu e renderiza os componentes presentes no mesmo
void Menu();

//Libera toda a memoria alocada durante a exibiçao do menu
void FreeMenuResources();

#endif
