#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"

typedef struct
{
	SDL_Rect rect;
	SDL_Texture* texture;
	char text[50];
	char selected;
	SDL_Color color;
}Text;

void NewText(TTF_Font*, Text*);

#endif
