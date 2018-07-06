#ifndef GAME_H
#define GAME_H

// Componentes

typedef struct
{
	SPRITE obj;
	int speedY;
} Avatar;

SDL_Point cam;
Avatar avatar;
IMAGE background;

void LoadGameResources();
void Game();
void FreeGameResources();

#endif
