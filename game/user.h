#ifndef USER_H
#define USER_H

#include "images.h"
#include "text.h"
#include <SDL2/SDL_ttf.h>

// Componentes globais

TTF_Font *userFont;
IMAGE background;

typedef struct 
{
	int points, level;
	char user_id[16];

}USER;

// Componentes RankList

TEXT rankButtons[7];

void RankList();

// Componentes AddUser

void AddUser();

void add_user(char[], int, int);
void edit_user(char[], int, int);
USER* get_users();

#endif
