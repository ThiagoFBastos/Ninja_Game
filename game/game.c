#include "game.h"

#define SPEED 25
#define ACCELERATION 5

extern SDL_Renderer* render;
extern int game_state;

void LoadGameResources()
{
	background.texture = LoadTexture("");
	avatar.texture = LoadTexture("");
	avatar.spritePos = avatar.speedY = cam.x = cam.y = 0;
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
				
				avatar.x += SPEED + ACCELERATION * (e.key.repeat != 0);
				
				break;
				
			case SDLK_UP:
				
				// Condições para implementar
				
				if(Balance(avatar.rect))
					avatar.speedY = 50;
				
				break;
		}
    } 
	  
  }
	
	// Condições para implementar
	if(!Balance(avatar.rect))
	{
		avatar.rect.y += avatar.speedY;
		avatar.speedY--;
	}
	
	SDL_RenderClear(render);
	Render_Sprite(&avatar, cam);
	SDL_RenderCopy(render, background.texture, NULL, NULL);
	SDL_RenderPresent(render);
}
