#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


extern SDL_Renderer* render;
extern int game_state;

void LoadMenuResources()
{
	background.texture = LoadTexture("");
    TTF_font* font = TTF_OpenFont("m5x7.ttf",32);
	
	//Novo jogo label
	strcpy(button[0].text, "Novo jogo");
	button[0].selected = 0;
	button[0].color.r = button[0].g = button[0].b = button[0].a = 255;
	New_Text(font, &button[0]);
	
	//Opções label
	
	strcpy(button[1].text, "Opções");
	button[1].selected = 0;
	button[1].color.r = button[1].g = button[1].b = button[1].a = 255;
	New_Text(font, &button[1]);
	
	//Ranking label
	
	strcpy(button[2].text, "Ranking");
	button[2].selected = 0;
	button[2].color.r = button[2].g = button[2].b = button[2].a = 255;
	New_Text(font, &button[2]);
	
	//Creditos label
	strcpy(button[3].text, "Ranking");
	button[3].selected = 0;
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
					{
						labels[i].selected = 1;
						labels[i].color.r = labels[i].color.g = labels[i].color.b = 126;
					}
					else
					{
					   labels[i].selected = 0;
					   labels[i].color.r = labels[i].color.g = labels[i].color.b = 255;
					}
				  }   
				  break;
					   
			case SDL_MOUSEBUTTONDOWN:
					   
					 if(HasPoint(e.button.x, e.button.y, labels[0].bounds)) game_state = RUN;
					 else if(HasPoint(e.button.x, e.button.y, labels[1].bounds));
					 else if(HasPoint(e.button.x, e.button.y, labels[2].bounds));
					 else if(HasPoint(e.button.x, e.button.y, labels[3].bounds));
            }
		}
	}
				   
	SDL_RenderClear(render);
					
	SDL_RenderCopy(render, background.texture, NULL, NULL);
					
    for(int i = 0; i < 4; i++)
        SDL_RenderCopy(render, button[i].texture, &button[i].bounds, NULL);

	SDL_RenderPresent(render);
}
