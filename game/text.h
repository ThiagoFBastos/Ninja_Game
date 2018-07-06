#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL_ttf.h"

typedef struct
{
	SDL_Rect bounds;
	SDL_Texture* texture;
	char text[50];
	SDL_bool selected;
	SDL_Color color;
}Text;

void New_Text(TTF_Font*, Text*);
void Render_Text(Text);
void Destroy_Text(Text*);

#endif
