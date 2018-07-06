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
	
	//button[0]
	strcpy(button[0].text, "Novo jogo");
	button[0].selected = 0;
	button[0].color.r = button[0].g = button[0].b = button[0].a = 0xff;
	NewText(font, &button[0]);
	
	//button[1]
	
	strcpy(button[1].text, "Opções");
	button[1].selected = 0;
	button[1].color.r = button[1].g = button[1].b = button[1].a = 0xff;
	NewText(font, &button[1]);
}

void Menu()
{
    int x,y;
    const int nummenu = 4;
    const char* labels[nummenu] = {"Novo jogo","Opções","Ranking","Creditos"};
    SDL_surface* menus[nummenu];
    bool menuselect[nummenu] = {0,0,0,0};
    SDL_Color cores[2] = {{255,255,255,0},{126,126,126,0}};

    menus[0] = TTF_RenderText_Solid(font,labels[0],cores[0]);
    menus[1] = TTF_RenderText_Solid(font,labels[1],cores[0]);
    menus[2] = TTF_RenderText_Solid(font,labels[2],cores[0]);
    menus[3] = TTF_RenderText_Solid(font,labels[3],cores[0]);

    SDL_Rect position[nummenu] = {{""},{""},{""},{""}};

    SDL_Event e;

	while(SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT);
            /*chamar uma funçao de termino*/

        else if(e.type == SDL_MOUSEMOTION)
        {
            x=e.motion.x;
            y=e.motion.y;

            for(int i=0;i<nummenu;i++)
            {
                if(HasPoint(e.motion.x, e.motion.y, pos[i])
                {
                    if(menuselect[i])
                    {
						menuselect[i] = 0;
                        SDL_FreeSurface(menu[i]);
                        menu[i] = TTF_RenderText_Solid(font,labels[i],cores[0]);
                    }
                    else
                    {
                        menuselect[i] = 1;
                        SDL_FreeSurface(menu[i]);
                        menu[i] = TTF_RenderText_Solid(font,labels[i],cores[1]);
                    }
                }
            }
        }
		
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(HasPoint(e.button.x, e.button.y, pos[0])
                    Game();
            else if(HasPoint(e.button.x, e.button.y, pos[1])
                    Options();
            else if(HasPoint(e.button.x, e.button.y, pos[2])
                    RankList();
            else if(HasPoint(e.button.x, e.button.y, pos[3])
                    Credits();
        }
	}

	for(int i=0;i<nummenu;i++)
    {
        SDL_Texture *tx[i] = SDL_CreateTextureFromSurface(render,menus[i]);
    }

	SDL_RenderClear(render);
	SDL_RenderCopy(render, background.texture, NULL, NULL);
					
    for(int i = 0; i < nummenu; i++)
    {
        SDL_RenderCopy(render,tx[i],NULL,position[i]);
    }

	SDL_RenderPresent(render);
}
