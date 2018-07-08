#ifndef RANK_LIST_H
#define RANK_LIST_H

// Componentes

#include "images.h"
#include "text.h"
#include <SDL2/SDL_ttf.h>

TTF_Font* font;
IMAGE background;
TEXT button[7];

void LoadRankingResources();
void Ranking();
void FreeRankingResources();

#endif
