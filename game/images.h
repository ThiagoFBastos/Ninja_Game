#ifndef IMAGES_H
#define IMAGES_H

#define TILE_H 200 // trocar
#define TILE_W 300 // trocar


#define TILE_MIN 50 // tamanho do menor quadrado do tile map

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

extern SDL_Renderer* render;

typedef struct
{
	SDL_Rect rect, hitBox;
	SDL_Texture* texture;
	int spritePos; // posicao do sprite na imagem
	int speedX, speedY;
	
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


/* Verifica colisao entre retangulos
 * Intersects retorna 1 caso haja colisao senao retorna 0
*/

int Intersects(SDL_Rect, SDL_Rect);

/* Carrega o mapa no formato de tile maps 
 * Cada tile map e identificado por seu id que varia de 0 a n
 * O primeiro parametro e o endereco do arquivo de texto que contem o mapa
 * O segundo parametro e o endereco da imagem
*/

void LoadMap(const char*, const char*);

/* Renderiza o mapa em forma de tile maps
 * O primeiro parametro e a posicao da camera do jogo
*/

void RenderMap(SDL_Point);

/* Renderiza uma imagem
 * O primeiro parametro e a imagem com suas informacoes
 * O segundo parametro e a posicao da camera
*/

void Render_Image(Image*, SDL_Point);

/* Renderiza um sprite
 * O primeiro parametro e o sprite com suas informacoes
 * O segundo parametro e a posicao da camera
*/

void Render_Sprite(Sprite*, SDL_Point);

/* Carrega uma textura
 * O primeiro parametro e o endereco da imagem
 * A funcao retorna um ponteiro para o tipo SDL_Texture
*/

SDL_Texture* LoadTexture(const char*);

int Balance(SDL_Rect);

#endif
