#ifndef GAME_H
#define GAME_H

extern int game_state;

// Componentes

SPRITE avatar;
IMAGE background;

void LoadResources(const char*);
void Game();

#endif