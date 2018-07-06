#include "menu.h"
#include "game_state.h"

#include <stdio.h>
#include <string.h>


extern SDL_Renderer* render;
extern int game_state;

void LoadMenuResources()
{
	background.texture = LoadTexture("");
    TTF_font* font = TTF_OpenFont("m5x7.ttf",32);
	
	//Faltam as posições dos retangulos
	
	//Novo jogo label
	strcpy(button[0].text, "Novo jogo");
	button[0].color.r = button[0].g = button[0].b = button[0].a = 255;
	New_Text(font, &button[0]);
	
	//Opções label
	
	strcpy(button[1].text, "Opções");
	button[1].color.r = button[1].g = button[1].b = button[1].a = 255;
	New_Text(font, &button[1]);
	
	//Ranking label
	
	strcpy(button[2].text, "Ranking");
	button[2].color.r = button[2].g = button[2].b = button[2].a = 255;
	New_Text(font, &button[2]);
	
	//Creditos label
	strcpy(button[3].text, "Creditos");
	button[3].color.r = button[3].g = button[3].b = button[3].a = 255;
	New_Text(font, &button[3]);
}

void Menu()
{
    SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		
		switch(e.type)
		{
			case SDL_QUIT: break;
				
			case SDL_MOUSEMOTION:
				
				 for(int i = 0; i < 4; i++)
            	 {
                	if(HasPoint(e.motion.x, e.motion.y, labels[i].bounds)
						labels[i].color.r = labels[i].color.g = labels[i].color.b = 126;
					else
					   labels[i].color.r = labels[i].color.g = labels[i].color.b = 255;
				  }   
					   
				  break;
					   
			case SDL_MOUSEBUTTONDOWN:
					   
					 if(HasPoint(e.button.x, e.button.y, labels[0].bounds)) game_state = RUN;
					 else if(HasPoint(e.button.x, e.button.y, labels[1].bounds)) game_state = OPTIONS;
					 else if(HasPoint(e.button.x, e.button.y, labels[2].bounds)) game_state = RANK_LIST;
					 else if(HasPoint(e.button.x, e.button.y, labels[3].bounds)) game_state = CREDITS;
            }
		}
	}
				   
	SDL_RenderClear(render);
					
	SDL_RenderCopy(render, background.texture, NULL, NULL);
					
    for(int i = 0; i < 4; i++)
        SDL_RenderCopy(render, button[i].texture, &button[i].bounds, NULL);

	SDL_RenderPresent(render);
}

void FreeMenuResources()
{
	SDL_DestroyTexture(background.texture);
	background.texture = NULL;
	
	for(int j = 0; j < 4; j++)
	{
		SDL_DestroyTexture(button[j].texture);
		button.texture = NULL;
	}
	
	TTF_CloseFont(font);
	font = NULL;
}
