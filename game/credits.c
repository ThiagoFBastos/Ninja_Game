#include "credits.h"
#include "game_state.h"
#include <string.h>
#include <stdio.h>

void LoadCreditsResources()
{
    background.texture = LoadTexture("");
    TTF_Font *font = TTF_OpenFont("m5x7.ttf",32);
    logo.texture = LoadTexture("");

    //Adicionar posições

    //Voltar label
    strcpy(button[0].text, "Voltar");
	button[0].color.r = button[0].g = button[0].b = button[0].a = 255;
	New_Text(font, &button[0]);

	//integrantes label
    strcpy(button[1].text, "Integrantes: ...");
	button[1].color.r = button[1].g = button[1].b = button[1].a = 255;
	New_Text(font, &button[1]);


}

void Credits()
{
       SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{

		switch(e.type)
		{
			case SDL_QUIT: break;

			case SDL_MOUSEMOTION:

            	 {
                	if(HasPoint(e.motion.x, e.motion.y, labels[0].bounds)
						labels[0].color.r = labels[0].color.g = labels[0].color.b = 126;
					else
					   labels[0].color.r = labels[0].color.g = labels[0].color.b = 255;
				  }

				  break;

			case SDL_MOUSEBUTTONDOWN:

					 if(HasPoint(e.button.x, e.button.y, labels[0].bounds)) game_state = MENU;
            }
		}
	}

	SDL_RenderClear(render);

	SDL_RenderCopy(render, background.texture, NULL, NULL);

    for(int i = 0; i < 2; i++)
        SDL_RenderCopy(render, button[i].texture, &button[i].bounds, NULL);

    SDL_RenderCopy(render,logo.texture,"",NULL);

	SDL_RenderPresent(render);

void FreeCreditsResources()
{
	SDL_DestroyTexture(background.texture);
	background.texture = NULL;

	SDL_DestroyTexture(logo.texture);
	logo.texture = NULL;

	for(int j = 0; j < 2; j++)
	{
		SDL_DestroyTexture(button[j].texture);
		button.texture = NULL;
	}

	TTF_CloseFont(font);
	font = NULL;
}
