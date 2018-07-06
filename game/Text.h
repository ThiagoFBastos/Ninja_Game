#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"

typedef struct
{
	SDL_Texture* texture;
	char text[50];
	char selected;
}Text;

void NewText(TTF_Font*, Text*);

#endif
