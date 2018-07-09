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
	USER *users = NULL;

	rankPage = 0;

	userFont = TTF_OpenFont("m5x7.ttf", 32);

	if(!userFont)
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());

	strcpy(rankButton[0].text, "Back");
	rankButton[0].color.r = 0;
	rankButton[0].color.g = 0;
	rankButton[0].color.b = 0;
	rankButton[0].color.a = 0xff;
	LoadText(userFont, &rankButton[0]);
	SDL_QueryTexture(rankButton[0].texture, NULL, NULL, &rankButton[0].bounds.w, &rankButton[0].bounds.h);
	rankButton[0].bounds.x = 450;
	rankButton[0].bounds.y = 600 - rankButton[0].bounds.h;

	// Next button


	strcpy(rankButton[1].text, "Previous");


	rankButton[1].color.r = 0;
	rankButton[1].color.g = 0;
	rankButton[1].color.b = 0;
	rankButton[1].color.a = 255;

    LoadText(userFont, &rankButton[1]);
    SDL_QueryTexture(rankButton[1].texture, NULL, NULL, &rankButton[1].bounds.w, &rankButton[1].bounds.h);
	rankButton[1].bounds.x = 150;
	rankButton[1].bounds.y = 600 - rankButton[1].bounds.h;

	// Previous button

    strcpy(rankButton[2].text, "Next");

    rankButton[2].color.r = 0;
	rankButton[2].color.g = 0;
	rankButton[2].color.b = 0;
	rankButton[2].color.a = 255;

    LoadText(userFont, &rankButton[2]);
    SDL_QueryTexture(rankButton[2].texture, NULL, NULL, &rankButton[2].bounds.w, &rankButton[2].bounds.h);
	rankButton[2].bounds.x = 300;
	rankButton[2].bounds.y = 600 - rankButton[2].bounds.h;

	usersCount = get_users(&users);

	users_id = (TEXT*)malloc(usersCount * sizeof(TEXT));
	users_point = (TEXT*)malloc(usersCount * sizeof(TEXT));

	for(int j = 0; j < usersCount; j++)
	{

		strcpy(users_id[j].text, users[j].user_id);
		users_id[j].color.r = 0;
		users_id[j].color.g = 0;
		users_id[j].color.b = 0;
		users_id[j].color.a = 0xff;
		LoadText(userFont, &users_id[j]);

		toString(users[j].points, users_point[j].text);
		users_point[j].color.r = 0;
		users_point[j].color.g = 0;
		users_point[j].color.b = 0;
		users_point[j].color.a = 0xff;
		LoadText(userFont, &users_point[j]);

		SDL_QueryTexture(users_id[j].texture, NULL, NULL, &users_id[j].bounds.w, &users_id[j].bounds.h);
		SDL_QueryTexture(users_point[j].texture, NULL, NULL, &users_point[j].bounds.w, &users_point[j].bounds.h);

		users_id[j].bounds.x = 50;
		users_point[j].bounds.x = 300;

		users_id[j].bounds.y =  users_point[j].bounds.y = j % 10 * 50 + 60;
	}

	free(users);
}

void RankList()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(HasPoint(e.button.x, e.button.y, rankButton[0].bounds))
			{
				game_state = MENU;
				FreeRankListResources();
				LoadMenuResources();
				return;
			}
			else if(HasPoint(e.button.x, e.button.y, rankButton[1].bounds))
            {
                if(rankPage)
                    rankPage--;

            }
            else if(HasPoint(e.button.x, e.button.y, rankButton[2].bounds))
            {
               if(rankPage < usersCount / 10)
                    rankPage++;
            }
		}
	}

	SDL_RenderClear(render);

	for(int j = rankPage * 10, k = j + 10; j < k && j < usersCount; j++)
	{

		SDL_RenderCopy(render, users_id[j].texture, NULL, &users_id[j].bounds);
		SDL_RenderCopy(render, users_point[j].texture, NULL, &users_point[j].bounds);
	}

    for(int j = 0; j < 3; j++)
        SDL_RenderCopy(render, rankButton[j].texture, NULL, &rankButton[j].bounds);

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderPresent(render);
}

void FreeRankListResources()
{
	for(int j = 0; j < usersCount; j++)
	{
		SDL_DestroyTexture(users_id[j].texture);
		SDL_DestroyTexture(users_point[j].texture);

		users_id[j].texture = NULL;
		users_point[j].texture = NULL;
	}

	free(users_id);
	free(users_point);

	users_id = NULL;
	users_point = NULL;

    for(int j = 0; j < 3; j++)
    {
        SDL_DestroyTexture(rankButton[j].texture);
        rankButton[j].texture = NULL;
    }
}

void LoadAddUserResources()
{

}

void AddUser()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != EOF)
	{

	}

	SDL_RenderClear(render);

	SDL_RenderPresent(render);
}


void FreeAddUserResources()
{

}

void add_user(char user_id[], int points)
{
	FILE *rank = NULL;
	USER* users = NULL;

	int n = get_users(&users);

	USER* user = (USER*)bsearch(user_id, users, n, sizeof(USER), compare);

	if(user == NULL)
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
			int j;

			user->points = points;

			for(j = 0, --n; j < n; j++)
				fprintf(rank, "%d %s\n", users[j].points, users[j].user_id);

			fprintf(rank, "%d %s", users[j].points, users[j].user_id);
			fclose(rank);
		}
	}
}

int get_users(USER** users)
{
	FILE *rank = NULL;
	int i = 0;

	if((rank = fopen("rank", "r")))
	{

		*users = (USER*)malloc(sizeof(USER));

		USER* user = *users;

		while(fscanf(rank, "%d%s", &user[i].points, user[i].user_id) != EOF)
		{
			++i;
			*users = (USER*)realloc(*users, (i+1) * sizeof(USER));
			user = *users;
		}

		qsort(*users, i, sizeof(USER), compare);

		fclose(rank);
	}
	else
		fprintf(stderr, "rank couldn't open\n");

	return i;
}

