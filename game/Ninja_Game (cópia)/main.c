#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include "game_state.h"

#include "menu.h"
#include "credits.h"
#include "user.h"
#include "options.h"

#define FPS 60

#define WIDTH 800
#define HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
int game_state = MENU;
// SDL_bool sound = SDL_TRUE;

int LoadProgram();

int main()
{

	if(LoadProgram())
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
					//Game();
					break;
				case OPTIONS:
					Options();
					break;
				case RANK_LIST:
					RankList();
					break;
				case USER_ADD:
					//UserAdd();
					break;
			}

			timestamp = 1000 / FPS - SDL_GetTicks() + timestamp;

			if(timestamp > 0)
				SDL_Delay(timestamp);
		}
	}

	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

int LoadProgram()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
		return 0;
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

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
		fprintf(stderr, "IMG_Init: %s\n", IMG_GetError());
		return 0;
	}

	if(TTF_Init() == -1)
	{
		fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
		return 0;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
        return 0;
    }

	return 1;
}
