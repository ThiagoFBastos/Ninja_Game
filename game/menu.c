#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>


extern SDL_Renderer* render;
extern int game_state;

void LoadMenuResources()
{
	background.texture = LoadTexture("");
    TTF_font* font = TTF_OpenFont("m5x7.ttf",32);
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
		if(e.type == SDL_QUIT)
            /*chamar uma funçao de termino*/

        if(e.type == SDL_MOUSEMOTION)
        {
            x=e.motion.x;
            y=e.motion.y;

            for(int i=0;i<nummenu;i++)
            {
                if(x>=pos[i].x && x<= pos[i].x + pos[i].w && y>= pos[i].y && y<=pos[i].y + pos[i].h)
                {
                    if(!menuselect[i])
                    {
                        menuselect[i] = 1;
                        SDL_FreeSurface(menu[i]);
                        menu[i] = TTF_RenderText_Solid(font,labels[i],cores[1]);
                    }
                    else if(menuselect[i])
                    {
                        menuselect[i] = 0;
                        SDL_FreeSurface(menu[i]);
                        menu[i] = TTF_RenderText_Solid(font,labels[i],cores[0]);
                    }
                }
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            x=e.button.x;
            y=e.button.y;
            if(x>=pos[0].x && x<= pos[0].x + pos[0].w && y>= pos[0].y && y<=pos[0].y + pos[0].h)
                    game();
            if(x>=pos[1].x && x<= pos[1].x + pos[1].w && y>= pos[1].y && y<=pos[1].y + pos[1].h)
                    options();
            if(x>=pos[2].x && x<= pos[2].x + pos[2].w && y>= pos[2].y && y<=pos[2].y + pos[2].h)
                    ranklist();
            if(x>=pos[3].x && x<= pos[3].x + pos[3].w && y>= pos[3].y && y<=pos[3].y + pos[3].h)
                    credits();
        }
	}

	for(int i=0;i<nummenu;i++)
    {
        SDL_Texture *tx[i] = SDL_CreateTextureFromSurface(render,menus[i]);
    }

	SDL_RenderClear(render);
	SDL_RenderCopy(render, background.texture, NULL, NULL);
    for(int i=0;i<nummenu;i++)
    {
        SDL_RenderCopy(render,tx[i],NULL,position[i]);
    }

	SDL_RenderPresent(render);
}
