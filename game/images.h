#ifndef IMAGES_H
#define IMAGES_H

#define TILE_H 200 // trocar
#define TILE_W 300 // trocar

#define TILE_MIN 50


#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

extern SDL_Renderer* render;

typedef struct
{
	SDL_Rect rect, hitBox;
	SDL_Texture* texture;
	int spritePos;

}SPRITE;

typedef struct
{
	SDL_Rect rect;
	SDL_Texture *texture;

}IMAGE;

struct 
{
	int tilemap[TILE_H][TILE_W];
	SDL_Texture *texture;

}TILEMAP;

int Intersects(SDL_Rect, SDL_Rect);
void LoadMap(const char*, const char*);
void RenderMap(SDL_Point);
void Render_Image(Image*, SDL_Point);
void Render_Sprite(Sprite*, SDL_Point);

SDL_Texture* LoadTexture(const char*);

#endif