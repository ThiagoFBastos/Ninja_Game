#include "game.h"

#define SPEED 25
#define ACCELERATION 5

extern SDL_Renderer* render;
extern int game_state;

void LoadGameResources()
{
	background.texture = LoadTexture("");
	avatar.obj.texture = LoadTexture("");
	avatar.obj.spritePos = 0;
	avatar.speedY = 0;
	cam.x = cam.y = 0;
}

void Game()
{
  SDL_Event e;
  SDL_Keycode keyCode = SDLK_UNKNOWN;
	
  while(SDL_PollEvent(&e) != EOF)
  {
    if(e.type == SDL_KEYDOWN)
    {
		switch(e.key.keysym.sym)
		{
			case SDLK_RIGHT:
				
				avatar.x += SPEED;
				
				if(e.key.repeat)
					avatar.x += ACCELERATION;
				
				break;
				
			case SDLK_UP:
				
				// Condições para implementar
				
				if(Balance(avatar.obj.bounds))
					avatar.speedY = 40;
				
				break;
		}
    } 
	  
  }
	
	
	if(avatar.speedY <= 0 && Balance(avatar.obj.bounds))
	{
		avatar.speedY = 0;
	}
	else
	{
		avatar.rect.y += avatar.speedY / 3;
		avatar.speedY--;
	}
	
	SDL_RenderClear(render);
	Render_Sprite(&avatar.obj, cam);
	SDL_RenderCopy(render, background.texture, NULL, NULL);
	SDL_RenderPresent(render);
}

void FreeGameResources()
{
	SDL_DestroyTexture(avatar.obj.texture);
	avatar.obj.texture = NULL;
	
	SDL_DestroyTexture(background.texture);
	background.texture = NULL;
}
