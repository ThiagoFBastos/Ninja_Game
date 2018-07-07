#include "menu.h"
#include "game_state.h"

#include <stdio.h>
#include <string.h>


extern SDL_Renderer* render;
extern int game_state;

void LoadMenuResources()
{
	background.texture = LoadTexture("");
    	
	font = TTF_OpenFont("m5x7.ttf",32);
	
	//Faltam as posições dos retangulos
	
	//Novo jogo label
	strcpy(button[0].text, "Novo jogo");
	button[0].color.r = 255; 
	button[0].color.g = 255;
	button[0].color.b = 255;
	button[0].color.a = 255;
	New_Text(font, &button[0]);
	
	//Opções label
	
	strcpy(button[1].text, "Opções");
	button[1].color.r = 255; 
	button[1].color.g = 255;
	button[1].color.b = 255;
	button[1].color.a = 255;
	New_Text(font, &button[1]);
	
	//Ranking label
	
	strcpy(button[2].text, "Ranking");
	button[2].color.r = 255; 
	button[2].color.g = 255;
	button[2].color.b = 255;
	button[2].color.a = 255;
	New_Text(font, &button[2]);
	
	//Creditos label
	strcpy(button[3].text, "Creditos");
	button[3].color.r = 255; 
	button[3].color.g = 255;
	button[3].color.b = 255;
	button[3].color.a = 255;
	New_Text(font, &button[3]);
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
				
			case SDL_MOUSEMOTION:
				
				for(int i = 0; i < 4; i++)
            	{

                	if(HasPoint(e.motion.x, e.motion.y, labels[i].bounds)
                	{
                		if(!labels[i].selected)
                		{
	                		labels[i].selected = SDL_TRUE;
							labels[i].color.r = 126;
							labels[i].color.g = 126;
							labels[i].color.b = 126;
							SDL_DestroyTexture(labels[i].texture);
							New_Text(render, font, &labels[i]);
						}
                	}
					else if(labels[i].selected)
					{
					   labels[i].selected = SDL_FALSE;
					   labels[i].color.r = 255;
					   labels[i].color.g = 255;
					   labels[i].color.b = 255;
					   SDL_DestroyTexture(labels[i].texture);
					   New_Text(render, font, &labels[i]);
					}

				 }   
					   
				  break;
					   
			case SDL_MOUSEBUTTONDOWN:
					   
				if(HasPoint(e.button.x, e.button.y, labels[0].bounds))
					game_state = RUN;
				else if(HasPoint(e.button.x, e.button.y, labels[1].bounds))
					game_state = OPTIONS;
				else if(HasPoint(e.button.x, e.button.y, labels[2].bounds))
					game_state = RANK_LIST;
				else if(HasPoint(e.button.x, e.button.y, labels[3].bounds))
					game_state = CREDITS;
            }
		}
	}
				   
	SDL_RenderClear(render);
					
	SDL_RenderCopy(render, background.texture, NULL, NULL);
					
    for(int i = 0; i < 4; i++)
        SDL_RenderCopy(render, button[i].texture, NULL, &button[i].bounds);

	SDL_RenderPresent(render);

	if(game_state != MENU)
		FreeMenuResources();
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
