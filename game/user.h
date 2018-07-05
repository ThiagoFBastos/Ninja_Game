#ifndef USER_H
#define USER_H

typedef struct 
{
	int points, level;
	char user_id[16];

}USER;

void RankList();
void AddUser();

void add_user(char[], int, int);
void edit_user(char[], int, int);
USER* get_users();

#endif