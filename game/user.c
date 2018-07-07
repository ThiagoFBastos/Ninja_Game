#include "user.h"
#include "game_state.h"

#include <stdio.h>
#include <string.h>

extern SDL_Renderer* render;
extern int game_state;

void LoadRankListResources()
{

}

void RankList()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != EOF)
	{
	
	}

	SDL_RenderClear(render);

	SDL_RenderPresent(render);
}

void FreeRankListResources()
{

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

void add_user(char user_id[], int points, int level)
{
	FILE *f = NULL;

	if((f = fopen("", "a+"))
	{
		USER user;

		while(fscanf(f, "%*d%*d%s", &user.user_id) != EOF)
		{
			if(strcmp(user.user_id, user_id) == 0) break;			
		}
	
		if(feof(f))
			fprintf(f, "%d %d %s\n", points, level, user_id);

		fclose(f);
	}	
}
