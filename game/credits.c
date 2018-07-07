#include "credits.h"
#include "game_state.h"

#include <string.h>
#include <stdio.h>

/* Button != label ???*/

void LoadCreditsResources()
{
    background.texture = LoadTexture("");
    font = TTF_OpenFont("m5x7.ttf",32);
    logo.texture = LoadTexture("");

    //Adicionar posições

    //Voltar label
    strcpy(button[0].text, "Voltar");
	button[0].color.r = button[0].g = button[0].b = button[0].a = 255;
	button[0].selected = 0;
	New_Text(font, &button[0]);

	//integrantes label
    strcpy(button[1].text, "Integrantes: ...");
	button[1].color.r = button[1].g = button[1].b = button[1].a = 255;
	button[1].selected = 0;
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
					 
					for(int i = 0; i < 2; i++)
					{
						if(HasPoint(e.motion.x, e.motion.y, button[i].bounds)
						{
							if(!labels[i].selected)
							{
								button[i].selected = SDL_TRUE;
								button[i].color.r = 126;
								button[i].color.g = 126;
								button[i].color.b = 126;
								SDL_DestroyTexture(labels[i].texture);
								New_Text(render, font, &button[i]);
							}
						}
						else if(button[i].selected)
						{
						   button[i].selected = SDL_FALSE;
						   button[i].color.r = 255;
						   button[i].color.g = 255;
						   button[i].color.b = 255;
						   SDL_DestroyTexture(button[i].texture);
						   New_Text(render, font, &button[i]);
						}
				  	}

				  break;

			case SDL_MOUSEBUTTONDOWN:

					 if(HasPoint(e.button.x, e.button.y, button[0].bounds)) game_state = MENU;
            }
		}
	}

	SDL_RenderClear(render);

	SDL_RenderCopy(render, background.texture, NULL, NULL);

    for(int i = 0; i < 2; i++)
        SDL_RenderCopy(render, button[i].texture, NULL, &button[i].bounds);

    SDL_RenderCopy(render,logo.texture, NULL, logo.bounds);

	SDL_RenderPresent(render);
}
						   
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
