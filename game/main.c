#include <stdio.h>
#include "images.h"

#define FPS 1000/60

#define WIDTH 800
#define HEIGHT 600

#define MENU 1
#define RUN 2
#define CREDITS 3
#define OPTIONS 4
#define RANKLIST 5
#define USERADD 6
#define EXIT 0

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
int game_state = GAME_STATE_MENU;

// retirar
void Menu();
void Options();
void Game();
void Credits();
void RankList();
void UserAdd();

int main()
{

	freopen("log/log_err.txt", "w", stderr);

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		fputs("SDL_Init\n", stderr);
	else
	{
		int timestamp;

		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		if(!window)
		{
			fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
			return 1;
		}


		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if(!render)
		{
			fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
			return 1;
		}

		while(game_state)
		{
			timestamp = SDL_GetTicks();

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
			}

			timestamp = FPS - SDL_GetTicks() + timestamp;

			if(timestamp > 0) 
				SDL_Delay(timestamp);
		}

		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	return 0;
}

void Menu()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
			game_state = EXIT;
	}

	SDL_RenderClear(render);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0xff);
	SDL_RenderPresent(render);
}

void Options()
{

}

void Game()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0);
}

void Credits()
{

}

void RankList()
{

}

void UserAdd()
{

}
