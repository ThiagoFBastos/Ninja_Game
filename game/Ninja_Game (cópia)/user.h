#ifndef USER_H
#define USER_H

#define MAX_USERS 1000

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

BUTTON nextPage, previousPage, userBack;
TEXT users_id[MAX_USERS];
TEXT users_point[MAX_USERS];

int usersCount, rankPage;

void LoadRankListResources();
void RankList();
void FreeRankListResources();

// Componentes AddUser

TEXTFIELD txtAddUser;

void LoadAddUser();
void AddUser();
void FreeAddUser();

void add_user(char[], int);
int get_users(USER[]);

#endif
