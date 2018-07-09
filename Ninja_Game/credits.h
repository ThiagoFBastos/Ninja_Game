#ifndef CREDITS_H
#define CREDITS_H

// Componentes

#include "images.h"

TTF_Font* creditsFont;
IMAGE creditsBackground, creditsLogo;
TEXT creditsButton[2];

void LoadCreditsResources();
void Credits();
void FreeCreditsResources();

#endif
