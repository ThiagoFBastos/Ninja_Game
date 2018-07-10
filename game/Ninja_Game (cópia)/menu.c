#include "menu.h"
#include "game_state.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern SDL_Renderer* render;
extern int game_state;

extern void LoadCreditsResources();

//extern void LoadGameResources();
extern void LoadOptionsResources();
//extern void LoadAddUserResources();
extern void LoadRankListResources();

void LoadMenuResources()
{
	menuBackground.texture = LoadTEXTURE("assets/bg/3.png");

	menuFont = TTF_OpenFont("m5x7.ttf",32);

	if(!menuFont)
    {
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
		exit(1);
    }

	//Faltam as posições dos retangulos

	//Novo jogo label
	strcpy(menuLabels[0].text, "New Game");
	menuLabels[0].color.r = 0;
	menuLabels[0].color.g = 0;
	menuLabels[0].color.b = 0;
	menuLabels[0].color.a = 255;

	menuLabels[0].selectedColor.r = 128;
	menuLabels[0].selectedColor.g = 128;
	menuLabels[0].selectedColor.b = 128;
	menuLabels[0].selectedColor.a = 255;

	LoadTEXT(menuFont, &menuLabels[0]);
	menuLabels[0].bounds.x = 50;
	menuLabels[0].bounds.y = 50;
	SDL_QueryTexture(menuLabels[0].texture, NULL, NULL, &menuLabels[0].bounds.w, &menuLabels[0].bounds.h);
	//Opções label

	strcpy(menuLabels[1].text, "Options");

	menuLabels[1].color.r = 0;
	menuLabels[1].color.g = 0;
	menuLabels[1].color.b = 0;
	menuLabels[1].color.a = 255;

	menuLabels[1].selectedColor.r = 128;
	menuLabels[1].selectedColor.g = 128;
	menuLabels[1].selectedColor.b = 128;
	menuLabels[1].selectedColor.a = 255;

	LoadTEXT(menuFont, &menuLabels[1]);
	SDL_QueryTexture(menuLabels[1].texture, NULL, NULL, &menuLabels[1].bounds.w, &menuLabels[1].bounds.h);
	menuLabels[1].bounds.x = 50;
	menuLabels[1].bounds.y = 100;

	//Ranking label

	strcpy(menuLabels[2].text, "Ranking");

	menuLabels[2].color.r = 0;
	menuLabels[2].color.g = 0;
	menuLabels[2].color.b = 0;
	menuLabels[2].color.a = 255;

	menuLabels[2].selectedColor.r = 128;
	menuLabels[2].selectedColor.g = 128;
	menuLabels[2].selectedColor.b = 128;
	menuLabels[2].selectedColor.a = 255;

	LoadTEXT(menuFont, &menuLabels[2]);
	SDL_QueryTexture(menuLabels[2].texture, NULL, NULL, &menuLabels[2].bounds.w, &menuLabels[2].bounds.h);
	menuLabels[2].bounds.x = 50;
	menuLabels[2].bounds.y = 150;

	//Creditos label
	strcpy(menuLabels[3].text, "Credits");

	menuLabels[3].color.r = 0;
	menuLabels[3].color.g = 0;
	menuLabels[3].color.b = 0;
	menuLabels[3].color.a = 255;

	menuLabels[3].selectedColor.r = 128;
	menuLabels[3].selectedColor.g = 128;
	menuLabels[3].selectedColor.b = 128;
	menuLabels[3].selectedColor.a = 255;

	LoadTEXT(menuFont, &menuLabels[3]);
	SDL_QueryTexture(menuLabels[3].texture, NULL, NULL, &menuLabels[3].bounds.w, &menuLabels[3].bounds.h);
	menuLabels[3].bounds.x = 50;
	menuLabels[3].bounds.y = 200;

    introduction = Mix_LoadMUS("assets/sound/20.wav");

    if(!introduction)
    {
        fprintf(stderr, "Mix_LoadMus: %s\n", Mix_GetError());
        exit(1);
    }

    menuButtonClick = Mix_LoadWAV("assets/sound/button_click.wav");


    Mix_PlayMusic(introduction, -1);
}

void Menu()
{
    SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{

		switch(e.type)
		{

            case SDL_QUIT:
                game_state = EXIT;
                break;

			case SDL_KEYDOWN:
				if(e.key.keysym.sym == SDLK_ESCAPE)
					game_state = EXIT;
				break;

			case SDL_MOUSEMOTION:

				for(int i = 0; i < 4; i++)
            	{
                	if(HasPoint(e.motion.x, e.motion.y, menuLabels[i].bounds))
                	{
                		if(!menuLabels[i].selected)
                		{
	                		menuLabels[i].selected = SDL_TRUE;
							SDL_DestroyTexture(menuLabels[i].texture);
							LoadTEXT(menuFont, &menuLabels[i]);
						}
                	}
					else if(menuLabels[i].selected)
					{
					   menuLabels[i].selected = SDL_FALSE;
					   SDL_DestroyTexture(menuLabels[i].texture);
					   LoadTEXT(menuFont, &menuLabels[i]);
					}

				 }

				  break;

			case SDL_MOUSEBUTTONDOWN:

				if(HasPoint(e.button.x, e.button.y, menuLabels[0].bounds)) game_state = RUN;
				else if(HasPoint(e.button.x, e.button.y, menuLabels[1].bounds)) game_state = OPTIONS;
				else if(HasPoint(e.button.x, e.button.y, menuLabels[2].bounds)) game_state = RANK_LIST;
				else if(HasPoint(e.button.x, e.button.y, menuLabels[3].bounds)) game_state = CREDITS;
		}
	}

	SDL_RenderClear(render);

	SDL_RenderCopy(render, menuBackground.texture, NULL, NULL);

    for(int i = 0; i < 4; i++)
        SDL_RenderCopy(render, menuLabels[i].texture, NULL, &menuLabels[i].bounds);

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderPresent(render);

	if(game_state != MENU)
	{
        if(game_state == EXIT) return;

	    Mix_PlayChannel(-1, menuButtonClick, 0);
	    SDL_Delay(100);
	    FreeMenuResources();

        switch(game_state)
        {
            case RUN: break;

            case CREDITS:
                LoadCreditsResources();
                break;

            case OPTIONS:
                LoadOptionsResources();
                break;

            case RANK_LIST:
                LoadRankListResources();
        }
	}
}

void FreeMenuResources()
{
	SDL_DestroyTexture(menuBackground.texture);
	menuBackground.texture = NULL;

    Mix_HaltMusic();
    Mix_FreeMusic(introduction);
    introduction = NULL;

    Mix_FreeChunk(menuButtonClick);
    menuButtonClick = NULL;

	for(int j = 0; j < 4; j++)
	{
		SDL_DestroyTexture(menuLabels[j].texture);
		menuLabels[j].texture = NULL;
	}

	TTF_CloseFont(menuFont);
	menuFont = NULL;
}
