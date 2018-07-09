#include <stdio.h>
#include <time.h>

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

int Load();
char* now();

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
		fprintf(stderr, "%s SDL_Init failed\n", now());
		return 0;
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if(!window)
	{
		fprintf(stderr, "%s SDL_CreateWindow: %s\n", now(), SDL_GetError());
		return 0;
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!render)
	{
		fprintf(stderr, "%s SDL_CreateRenderer: %s\n", now(), SDL_GetError());
		return 0;
	}

	int imgInitFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if(IMG_Init(imgInitFlags) != imgInitFlags)
	{
		fprintf(stderr, "%s IMG_Init Failed\n", now());
		return 0;
	}

	if(TTF_Init() == -1)
	{
		fprintf(stderr, "%s TTF_Init Failed\n", now());
		return 0;
	}

	freopen("log/log_err.txt", "a", stderr);

	return 1;
}

char* now()
{
	time_t t;
	struct tm* n;

	time(&t);

	n = localtime(&t);

	return asctime(n);
}
