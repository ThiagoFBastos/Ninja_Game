#ifndef OPTIONS_H
#define OPTIONS_H

#include "images.h"

// Componentes
IMAGE optionsBackground;
TTF_Font* optionsFont;
TEXT optionsButton[2];

void LoadOptionsResources();
void Options();
void FreeOptionsResources();

#endif
