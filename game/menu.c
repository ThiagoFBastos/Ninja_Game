#include "menu.h"

extern SDL_Renderer* render;
extern int game_state;

void LoadMenuResources()
{
	background.texture = LoadTexture("");
}

void Menu()
{
	SDL_Event e;
	
	while(SDL_PollEvent(&e) != 0)
	{
		/* implemente */
	}
	
	SDL_RenderClear(render);
	SDL_RenderCopy(render, background.texture, NULL, NULL);
	/*
		for(int j = 0; j < 1; j++)
		
	*/
	SDL_RenderPresent(render);
}
