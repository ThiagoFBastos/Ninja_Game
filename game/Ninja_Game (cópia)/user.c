#include "user.h"
#include "game_state.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern SDL_Renderer* render;
extern int game_state;

extern void LoadMenuResources();

int compare(const void* e, const void* d)
{
	USER *a, *b;

	a = (USER*)e;
	b = (USER*)d;

	if(a->points != b->points)
		return b->points - a->points;

	return strcmp(a->user_id, b->user_id);
}

void toString(int val, char* dest)
{
	int j = 0, k = 0;

	while(val > 0)
	{
		dest[j++] = 48 + val % 10;
		val /= 10;
	}

	dest[j--] = '\0';

	while(k < j)
	{
		char temp = dest[k];
		dest[k] = dest[j];
		dest[j] = temp;
		k++;
		j--;
	}
}

void LoadRankListResources()
{
	USER users[MAX_USERS];
	int j;

	rankPage = 0;

	userFont = TTF_OpenFont("m5x7.ttf", 32);

	if(!userFont)
	{
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
		exit(1);
	}

	// Back button

	strcpy(userBack.field.text, "Back");

	userBack.field.color.r = 0;
	userBack.field.color.g = 0;
	userBack.field.color.b = 0;
	userBack.field.color.a = 255;

	userBack.bgColor.r = 128;
	userBack.bgColor.g = 128;
	userBack.bgColor.b = 128;
	userBack.bgColor.a = 255;

	userBack.bounds.x = 500;
	userBack.bounds.y = 525;
	userBack.bounds.w = 100;
	userBack.bounds.h = 50;

	LoadTEXT(userFont, &userBack.field);
	SDL_QueryTexture(userBack.field.texture, NULL, NULL, &userBack.field.bounds.w, &userBack.field.bounds.h);
	userBack.field.bounds.x = 550 - userBack.field.bounds.w / 2;
	userBack.field.bounds.y = 550 - userBack.field.bounds.h / 2;

	// Next button

	strcpy(previousPage.field.text, "Previous");

	previousPage.field.color.r = 0;
	previousPage.field.color.g = 0;
	previousPage.field.color.b = 0;
	previousPage.field.color.a = 255;

	previousPage.bgColor.r = 128;
	previousPage.bgColor.g = 128;
	previousPage.bgColor.b = 128;
	previousPage.bgColor.a = 255;

	previousPage.bounds.x = 200;
	previousPage.bounds.y = 525;
	previousPage.bounds.w = 100;
	previousPage.bounds.h = 50;


    LoadTEXT(userFont, &previousPage.field);
    SDL_QueryTexture(previousPage.field.texture, NULL, NULL, &previousPage.field.bounds.w, &previousPage.field.bounds.h);
	previousPage.field.bounds.x = 250 - previousPage.field.bounds.w / 2;
	previousPage.field.bounds.y = 550 - previousPage.field.bounds.h / 2;

	// Previous button

    strcpy(nextPage.field.text, "Next");

    nextPage.field.color.r = 0;
	nextPage.field.color.g = 0;
	nextPage.field.color.b = 0;
	nextPage.field.color.a = 255;

	nextPage.bgColor.r = 128;
	nextPage.bgColor.g = 128;
	nextPage.bgColor.b = 128;
	nextPage.bgColor.a = 255;

	nextPage.bounds.x = 350;
	nextPage.bounds.y = 525;
	nextPage.bounds.w = 100;
	nextPage.bounds.h = 50;


    LoadTEXT(userFont, &nextPage.field);
    SDL_QueryTexture(nextPage.field.texture, NULL, NULL, &nextPage.field.bounds.w, &nextPage.field.bounds.h);
	nextPage.field.bounds.x = 400 - nextPage.field.bounds.w / 2;
	nextPage.field.bounds.y = 550 - nextPage.field.bounds.h / 2;

	usersCount = get_users(users);
	qsort(users, usersCount, sizeof(USER), compare);

	for(j = 0; j < usersCount; j++)
	{
		strcpy(users_id[j].text, users[j].user_id);
		users_id[j].color.r = 0;
		users_id[j].color.g = 0;
		users_id[j].color.b = 0;
		users_id[j].color.a = 255;
		LoadTEXT(userFont, &users_id[j]);

		toString(users[j].points, users_point[j].text);
		users_point[j].color.r = 0;
		users_point[j].color.g = 0;
		users_point[j].color.b = 0;
		users_point[j].color.a = 255;
		LoadTEXT(userFont, &users_point[j]);

		SDL_QueryTexture(users_id[j].texture, NULL, NULL, &users_id[j].bounds.w, &users_id[j].bounds.h);
		SDL_QueryTexture(users_point[j].texture, NULL, NULL, &users_point[j].bounds.w, &users_point[j].bounds.h);

		users_id[j].bounds.x = 50;
		users_point[j].bounds.x = 300;

		users_id[j].bounds.y =  users_point[j].bounds.y = j % 10 * 50 + 20;
	}
}

void RankList()
{
	SDL_Event e;
	int j, n;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(HasPoint(e.button.x, e.button.y, userBack.bounds))
			{
				game_state = MENU;
				FreeRankListResources();
				LoadMenuResources();

				return;
			}
			else if(HasPoint(e.button.x, e.button.y, previousPage.bounds))
            {
                if(rankPage)
                    rankPage--;
            }
            else if(HasPoint(e.button.x, e.button.y, nextPage.bounds))
            {
               if(rankPage < usersCount / 10)
                    rankPage++;
            }
		}
	}

	SDL_RenderClear(render);

	j = 10 * rankPage;
	n = j + 10;

	if(n > usersCount) n = usersCount;

	while(j < n)
	{
		SDL_RenderCopy(render, users_id[j].texture, NULL, &users_id[j].bounds);
		SDL_RenderCopy(render, users_point[j].texture, NULL, &users_point[j].bounds);
		j++;
	}

   	RenderBUTTON(userBack);
	RenderBUTTON(previousPage);
	RenderBUTTON(nextPage);

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderPresent(render);
}

void FreeRankListResources()
{
	int j;

	for(j = 0; j < usersCount; j++)
	{
		SDL_DestroyTexture(users_id[j].texture);
		SDL_DestroyTexture(users_point[j].texture);
		users_id[j].texture = NULL;
		users_point[j].texture = NULL;
	}

    SDL_DestroyTexture(userBack.field.texture);
	SDL_DestroyTexture(nextPage.field.texture);
	SDL_DestroyTexture(previousPage.field.texture);

	userBack.field.texture = NULL;
	nextPage.field.texture = NULL;
	previousPage.field.texture = NULL;
}

void LoadAddUserResources()
{
	userFont = TTF_OpenFont("m5x7.ttf", 32);

	if(!userFont)
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());

	strcpy(txtAddUser.field.text, "Enter user id...");

	// Foreground color

	txtAddUser.field.color.r = 255;
	txtAddUser.field.color.g = 255;
	txtAddUser.field.color.b = 255;
	txtAddUser.field.color.a = 255;

	// Background color

	txtAddUser.bgColor.r = 0;
	txtAddUser.bgColor.g = 0;
	txtAddUser.bgColor.b = 0;
	txtAddUser.bgColor.a = 255;

	txtAddUser.focus = SDL_FALSE;
	txtAddUser.textPos = 0;

	LoadTEXT(userFont, &txtAddUser.field);
	SDL_QueryTexture(txtAddUser.field.texture, NULL, NULL, &txtAddUser.field.bounds.w, &txtAddUser.field.bounds.h);
	txtAddUser.field.bounds.x = 400 - txtAddUser.field.bounds.w / 2;
	txtAddUser.field.bounds.y = 300 - txtAddUser.field.bounds.h / 2;

	txtAddUser.bounds.w = 300;
	txtAddUser.bounds.h = 50;
	txtAddUser.bounds.x = 250;
	txtAddUser.bounds.y = 275;

}

void AddUser()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != EOF)
	{
		if(e.type == SDL_KEYDOWN)
		{
			int code = (int)e.key.keysym.sym;

			if(e.key.keysym.sym == SDLK_BACKSPACE)
			{
				if(txtAddUser.textPos)
					txtAddUser.textPos--;
			}
			else if(code >= 'a' && code <= 'z' && code >= '0' && code <= '9')
				txtAddUser.field.text[txtAddUser.textPos++] = (char)code;


			txtAddUser.field.text[txtAddUser.textPos] = '\0';
			SDL_DestroyTexture(txtAddUser.field.texture);
			LoadTEXT(userFont, &txtAddUser.field);
		}
		else if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			txtAddUser.focus = HasPoint(e.button.x, e.button.y, txtAddUser.bounds);
		}
	}

	SDL_RenderClear(render);

	// txtAddUser TEXTFIELD

	SDL_SetRenderDrawColor(render, txtAddUser.bgColor.r, txtAddUser.bgColor.g, txtAddUser.bgColor.b, txtAddUser.bgColor.a);
	SDL_RenderFillRect(render, &txtAddUser.bounds);
	SDL_RenderCopy(render, txtAddUser.field.texture, NULL, &txtAddUser.field.bounds);

	SDL_RenderPresent(render);
}


void FreeAddUserResources()
{
	TTF_CloseFont(userFont);
	userFont = NULL;
}

void add_user(char user_id[], int points)
{
	FILE *rank = NULL;
	USER users[MAX_USERS];
	int j = 0, n;

	n = get_users(users);

	while(j < n && strcmp(users[j].user_id, user_id)) j++;

	if(j == n)
	{

		if((rank = fopen("rank", "a")))
		{
			fprintf(rank, "%d %s", points, user_id);
			fclose(rank);
		}
	}
	else
	{
		if((rank = fopen("rank", "w")))
		{

			users[j].points = points;

			for(j = 0, --n; j < n; j++)
				fprintf(rank, "%d %s\n", users[j].points, users[j].user_id);

			fprintf(rank, "%d %s", users[j].points, users[j].user_id);

			fclose(rank);
		}
	}
}

int get_users(USER users[])
{
	FILE *rank = NULL;
	int i = 0;

	if((rank = fopen("rank", "r")))
	{
		while(i < MAX_USERS)
		{
			fscanf(rank, "%d%s", &users[i].points, users[i].user_id);

			if(feof(rank))
				break;

			i++;
		}

		fclose(rank);
	}
	else
		fprintf(stderr, "rank couldn't open\n");

	return i;
}

