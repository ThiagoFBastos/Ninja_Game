#ifndef IMAGES_H
#define IMAGES_H

#define TILE_H 200 // trocar
#define TILE_W 300 // trocar


#define TILE_MIN 50 // tamanho do menor quadrado do tile map

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct
{
	SDL_Rect bounds, clip, hitBox;
	SDL_Texture* texture;
	int spritePos; // posicao do sprite na imagem

}SPRITE;

typedef struct
{
	SDL_Rect bounds;
	SDL_Texture *texture;
}IMAGE;

typedef struct
{
	SDL_Rect bounds;
	SDL_Texture *texture;
	char text[50];
	SDL_Color color, selectedColor;
	SDL_bool selected;
}TEXT;

typedef struct
{
	int textPos;
	SDL_bool focus;
	SDL_Color bgColor;
	SDL_Rect bounds;
	TEXT field;
	
}TEXTFIELD;

typedef struct 
{
	TEXT field;
	SDL_Color bgColor;
	SDL_Rect bounds;

}BUTTON;

struct 
{
	unsigned short tilemap[TILE_H][TILE_W];
	SDL_Texture *texture;

}TILEMAP;

/* Verifica colisao entre retangulos
 * Intersects retorna 1 caso haja colisao senao retorna 0
*/

int Intersects(SDL_Rect, SDL_Rect);

/* Verifica se um ponto esta em um retangulo
 * retorna 1 caso esteja senao retorna 0
*/

int HasPoint(int, int, SDL_Rect);

/* Carrega o mapa no formato de tile maps 
 * Cada tile map e identificado por seu id que varia de 0 a n
 * O primeiro parametro e o endereco do arquivo de texto que contem o mapa
 * O segundo parametro e o endereco da imagem
*/

void LoadTILEMAP(const char*, const char*);

/* Renderiza o mapa em forma de tile maps
 * O primeiro parametro e a posicao da camera do jogo
*/

void RenderTILEMAP(SDL_Point);

/* Renderiza uma imagem
 * O primeiro parametro e a imagem com suas informacoes
 * O segundo parametro e a posicao da camera
*/

void RenderIMAGE(IMAGE, SDL_Point);

/* Renderiza um sprite
 * O primeiro parametro e o sprite com suas informacoes
 * O segundo parametro e a posicao da camera
*/

void RenderSPRITE(SPRITE, SDL_Point);

/* Carrega uma textura
 * O primeiro parametro e o endereco da imagem
 * A funcao retorna um ponteiro para o tipo SDL_Texture
*/

SDL_Texture* LoadTEXTURE(const char*);

/* Verifica se um objeto retangular esta sobre um tile com caracteristica solida
  * Retorna 1 se o objeto esta em equilibrio estatico senao retorna 0
*/
	
int Balance(SDL_Rect);


// Carrega a textura de um texto

void LoadTEXT(TTF_Font*, TEXT*);


void RenderBUTTON(BUTTON);
void RenderTEXTFIELD(TEXTFIELD);


#endif
