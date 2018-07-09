#ifndef USER_H
#define USER_H

#include "images.h"

// Componentes globais

TTF_Font *userFont;
IMAGE userBackground;

typedef struct
{
	int points;
	char user_id[25];

}USER;

// Componentes RankList

TEXT rankButton[3];
TEXT* users_id;
TEXT* users_point;

int usersCount, rankPage;

void LoadRankListResources();
void RankList();
void FreeRankListResources();

// Componentes AddUser

void LoadAddUser();
void AddUser();
void FreeAddUser();

void add_user(char[], int);
int get_users(USER**);

#endif
