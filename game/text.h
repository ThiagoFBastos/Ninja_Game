#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"

typedef struct
{
	SDL_Rect bounds;
	SDL_Texture* texture;
	char text[50];
	SDL_Color color;
	SDL_bool selected;
}Text;

void New_Text(TTF_Font*, Text*);

#endif
