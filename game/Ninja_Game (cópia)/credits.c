#include "game_state.h"
#include "credits.h"

#include <string.h>
#include <stdio.h>

extern SDL_Renderer* render;
extern int game_state;

extern void LoadMenuResources();

void LoadCreditsResources()
{
    creditsBackground.texture = LoadTEXTURE("assets/bg/3.png");
	creditsLogo.texture = LoadTEXTURE("assets/ninja_logo.png");
    creditsFont = TTF_OpenFont("m5x7.ttf",32);

	if(!creditsFont)
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());

	//Logo

	creditsLogo.bounds.w = creditsLogo.bounds.h = 100;
	creditsLogo.bounds.x = 350;
	creditsLogo.bounds.y = 200;

    //Voltar
    strcpy(creditsButton[0].text, "Back");
	creditsButton[0].color.r = 0;
	creditsButton[0].color.g = 0;
	creditsButton[0].color.b = 0;
	creditsButton[0].color.a = 0xff;
	creditsButton[0].selected = 0;
	LoadTEXT(creditsFont, &creditsButton[0]);
	SDL_QueryTexture(creditsButton[0].texture, NULL, NULL, &creditsButton[0].bounds.w, &creditsButton[0].bounds.h);
	creditsButton[0].bounds.x = 400 - creditsButton[0].bounds.w / 2;
	creditsButton[0].bounds.y = 100;

	//integrantes label
    strcpy(creditsButton[1].text, "Developers: ...");
	creditsButton[1].color.r = 0;
	creditsButton[1].color.g = 0;
	creditsButton[1].color.b = 0;
	creditsButton[1].color.a = 0xff;
	creditsButton[1].selected = 0;
	LoadTEXT(creditsFont, &creditsButton[1]);
	SDL_QueryTexture(creditsButton[1].texture, NULL, NULL, &creditsButton[1].bounds.w, &creditsButton[1].bounds.h);
	creditsButton[1].bounds.x = 400 - creditsButton[1].bounds.w / 2;
	creditsButton[1].bounds.y = 400;
}

void Credits()
{
    SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{

		switch(e.type)
		{
			case SDL_MOUSEMOTION:
					 
				for(int i = 0; i < 2; i++)
				{
					if(HasPoint(e.motion.x, e.motion.y, creditsButton[i].bounds))
					{
						if(!creditsButton[i].selected)
						{
							creditsButton[i].selected = SDL_TRUE;
							creditsButton[i].color.r = 126;
							creditsButton[i].color.g = 126;
							creditsButton[i].color.b = 126;
							SDL_DestroyTexture(creditsButton[i].texture);
							LoadTEXT(creditsFont, &creditsButton[i]);
						}
					}
					else if(creditsButton[i].selected)
					{
						creditsButton[i].selected = SDL_FALSE;
						creditsButton[i].color.r = 0;
						creditsButton[i].color.g = 0;
						creditsButton[i].color.b = 0;
						SDL_DestroyTexture(creditsButton[i].texture);
						LoadTEXT(creditsFont, &creditsButton[i]);
					}
				}

				break;

			case SDL_MOUSEBUTTONDOWN:

				if(HasPoint(e.button.x, e.button.y, creditsButton[0].bounds)) 
				{
					game_state = MENU;
					FreeCreditsResources();
					LoadMenuResources();
					return;
				}
		}
	}

	SDL_RenderClear(render);

	SDL_RenderCopy(render, creditsBackground.texture, NULL, NULL);

    for(int i = 0; i < 2; i++)
        SDL_RenderCopy(render, creditsButton[i].texture, NULL, &creditsButton[i].bounds);

    SDL_RenderCopy(render,creditsLogo.texture, NULL, &creditsLogo.bounds);

	SDL_RenderPresent(render);
}
						   
void FreeCreditsResources()
{
	SDL_DestroyTexture(creditsBackground.texture);
	creditsBackground.texture = NULL;

	SDL_DestroyTexture(creditsLogo.texture);
	creditsLogo.texture = NULL;

	for(int j = 0; j < 2; j++)
	{
		SDL_DestroyTexture(creditsButton[j].texture);
		creditsButton[j].texture = NULL;
	}

	TTF_CloseFont(creditsFont);
	creditsFont = NULL;
}
