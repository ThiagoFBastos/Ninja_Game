#include "text.h"


void New_Text(SDL_Renderer* render, TTF_Font* font, Text* text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text->text, text->color);
	text->texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}