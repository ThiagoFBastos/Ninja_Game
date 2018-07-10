#include "options.h"
#include "game_state.h"

#include <stdio.h>
#include <string.h>

extern SDL_Renderer* render;
extern int game_state;

extern void LoadMenuResources();

void LoadOptionsResources()
{
	optionsFont = TTF_OpenFont("m5x7.ttf", 32);
	//optionsBackground.texture = LoadTEXTURE("assets/ninja_logo.png");

	if(!optionsFont)
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
	
	strcpy(optionsButton[0].text, "Mute");
	optionsButton[0].color.r = 0;
	optionsButton[0].color.g = 0;
	optionsButton[0].color.b = 0;
	optionsButton[0].color.a = 0xff;
	LoadTEXT(optionsFont, &optionsButton[0]);
	SDL_QueryTexture(optionsButton[0].texture, NULL, NULL, &optionsButton[0].bounds.w, &optionsButton[0].bounds.h);
	optionsButton[0].bounds.x = 400 - optionsButton[0].bounds.w / 2;
	optionsButton[0].bounds.y = 50;

	strcpy(optionsButton[1].text, "Back");
	optionsButton[1].color.r = 0;
	optionsButton[1].color.g = 0;
	optionsButton[1].color.b = 0;
	optionsButton[1].color.a = 0xff;
	LoadTEXT(optionsFont, &optionsButton[1]);
	SDL_QueryTexture(optionsButton[1].texture, NULL, NULL, &optionsButton[1].bounds.w, &optionsButton[1].bounds.h);
	optionsButton[1].bounds.x = 400 - optionsButton[1].bounds.w / 2;
	optionsButton[1].bounds.y = 600 - optionsButton[1].bounds.h;

}

void Options()
{
	SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_MOUSEMOTION)
		{
			for(int i = 0; i < 2; i++)
            {

                if(HasPoint(e.motion.x, e.motion.y, optionsButton[i].bounds))
                {
                	if(optionsButton[i].selected) continue;
             
	                optionsButton[i].selected = SDL_TRUE;
					optionsButton[i].color.r = 126;
					optionsButton[i].color.g = 126;
					optionsButton[i].color.b = 126;
					SDL_DestroyTexture(optionsButton[i].texture);
					LoadTEXT(optionsFont, &optionsButton[i]);
						
                }
				else if(optionsButton[i].selected)
				{
					optionsButton[i].selected = SDL_FALSE;
					optionsButton[i].color.r = 0;
					optionsButton[i].color.g = 0;
					optionsButton[i].color.b = 0;
					SDL_DestroyTexture(optionsButton[i].texture);
					LoadTEXT(optionsFont, &optionsButton[i]);
				}

			}   	   
		}

		else if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			if(HasPoint(e.motion.x, e.motion.y, optionsButton[0].bounds))
			{
				strcpy(optionsButton[0].text, "Sound");
				
			}
			else if(HasPoint(e.motion.x, e.motion.y, optionsButton[1].bounds))
			{
				game_state = MENU;
				FreeOptionsResources();
				LoadMenuResources();

				return;
			}
		}
	}

	SDL_RenderClear(render);

	for(int j = 0; j < 2; j++)
		SDL_RenderCopy(render, optionsButton[j].texture, NULL, &optionsButton[j].bounds);

	//SDL_RenderCopy(render, optionsBackground.texture, NULL, NULL);
	SDL_RenderPresent(render);
}

void FreeOptionsResources()
{
	TTF_CloseFont(optionsFont);
	optionsFont = NULL;

	//SDL_DestroyTexture(optionsBackground.texture);
	optionsBackground.texture = NULL;

	for(int j = 0; j < 2; j++)
	{
		SDL_DestroyTexture(optionsButton[j].texture);
		optionsButton[j].texture = NULL;
	}
}
