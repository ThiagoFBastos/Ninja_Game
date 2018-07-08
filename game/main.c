#include <stdio.h>

#include "game_state.h"

#include "game.h"
#include "credits.h"
#include "menu.h"
#include "options.h"
#include "user.h"

#define FPS 1000/60

#define WIDTH 800
#define HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
int game_state = MENU;

int Load();

int main()
{

	if(Load())
	{
		LoadMenuResources();

		while(game_state != EXIT)
		{
			long timestamp = SDL_GetTicks();

			switch(game_state)
			{
				case MENU: 
					Menu();
					break;
								
				case CREDITS:
					Credits();
					break;
								
				case RUN:
					Game(); 
					break;
								
				case OPTIONS:
					Options();
					break;
								
				case RANK_LIST:
					RankList();
					break;
							
				case USER_ADD:
					UserAdd();
					break;
			}

			timestamp = FPS - SDL_GetTicks() + timestamp;

			if(timestamp > 0) 
				SDL_Delay(timestamp);
		}	
	}	

	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	fclose(stderr);

	return 0;
}

int Load()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
		fputs("SDL_Init\n", stderr);
		return 0;
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);

	if(!window)
	{
		fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
		return 0;
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!render)
	{
		fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
		return 0;
	}

	int imgInitFlags = IMG_INIT_PNG | IMG_INIT_JPG;
			
	if(IMG_Init(imgInitFlags) != imgInitFlags)
	{
		fputs("IMG_Init Failed\n", stderr);
		return 0;
	}

	if(TTF_Init() == -1)
	{
		fputs("TTF_Init Failed\n", stderr);
		return 0;
	}

	freopen("log/log_err.txt", "a", stderr);

	return 1;
}
