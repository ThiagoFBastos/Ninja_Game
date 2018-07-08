#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define FPS 60

void iniciar();
void carregarmedia();
void fechar();

typedef struct
{
    SDL_Texture *texture[4];
    SDL_Rect playerPos;
    SDL_Rect playerRect[4]; //Posição de um frame em relação à imagem
    SDL_Point textureHW[4]; //Dimensão das texturas
    SDL_Rect attack;

    int lives = 3;

	int speedY, speedX;

}SPRITE;

SPRITE player;
SPRITE enemy;

SDL_Window* janela = NULL;
SDL_Renderer* renderizador = NULL;
SDL_Texture* tx[4];

int quit = 0;

int main (int argc, char **argv)
{
    int frametime = 0;
    int playerId = 0;
	int timestamp;
	player.attack.w = 32;
	player.attack.h = 16;

    iniciar();
    carregarmedia();

    //Game loop
    while(quit == 0)
    {
        SDL_Event evento;

		timestamp = SDL_GetTicks();

        while(SDL_PollEvent(&evento) != 0)
        {
            if(evento.type == SDL_QUIT)
                quit = 1;

            else if(evento.type == SDL_KEYDOWN)
            {
                switch(evento.key.keysym.sym)
                {
                    case SDLK_UP:

                        if(player.speedY == 0)
						{
							frametime = 0;
                        	playerId = 1;
							player.speedY = 30;
						}

                    break;

                    case SDLK_DOWN:
                        player.playerPos.y += 10;
                    break;

                    case SDLK_RIGHT:

						if(player.speedX == 0)
						{
							frametime = 0;
                        	playerId = 1;
							player.speedX = 20;
						}

                    break;

                    case SDLK_LEFT:

                        if(player.speedX == 0)
						{
							frametime = 0;
                        	playerId = 1;
							player.speedX = -20;
						}

                    break;

                    case SDLK_ESCAPE:
                        quit = 1;
                    break;

                    case SDLK_x:
                        player.speedX = 0;
                        playerid = 2;
                        player.attack.x = player.playerPos.x + 16;
                        player.attack.y = player.playerPos.y + 16;

                        if(Intersects(player.attack,enemy.playerPos) = 1)
                        {
                            /*inimigo perde vida*/
                        }

                        player.attack.x = player.attack.y = 0;


                }
            }
        }

		if(!(player.speedY <= 0  && player.playerPos.y >= 472))
		{
			player.playerPos.y -= player.speedY/3;
			player.speedY --;
		}
		else
			player.speedY = 0;

		if(player.speedX)
		{
			player.playerPos.x += player.speedX;

			if(player.speedX < 0) player.speedX ++;
			else player.speedX --;
		}
		else
			playerId = 0;

		 frametime++;

		 if(FPS / frametime ==  player.textureHW[playerId].x / player.playerRect[playerId].w)
		 {
		     frametime = 0;

		     player.playerRect[playerId].x += player.playerRect[playerId].w;

		     if(player.playerRect[playerId].x >= player.textureHW[playerId].x)
		        player.playerRect[playerId].x = 0;
		 }

		 if(intersects(player.playerPos,enemy.playerPos) == 1)
            playerId = 3;
         /* Termina a animação de morte e recomeça a fase*/

		timestamp = 1000/FPS - SDL_GetTicks() + timestamp;

		if(timestamp > 0)
			SDL_Delay(timestamp);

        SDL_RenderClear(renderizador);

		for(int i = 0;i < 4; i++)
		    SDL_RenderCopy(renderizador,tx[i],NULL,NULL);


		SDL_RenderCopy(renderizador, player.texture[playerId], &player.playerRect[playerId], &player.playerPos);

		SDL_RenderPresent(renderizador);
    }

    fechar();
    return 0;
}

void iniciar()
{

    if(SDL_Init(SDL_INIT_VIDEO < 0))
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );


    janela = SDL_CreateWindow("jogo",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);

    IMG_Init(IMG_INIT_PNG);

    renderizador = SDL_CreateRenderer(janela,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void carregarmedia()
{
    SDL_Surface* bg[4];

    bg[0] = IMG_Load("assets/bg/0.png");
    bg[1] = IMG_Load("assets/bg/1.png");
    bg[2] = IMG_Load("assets/bg/2.png");
    bg[3] = IMG_Load("assets/bg/3.png");

    SDL_Surface* idle = IMG_Load("assets/idle.png");
    SDL_Surface* run = IMG_Load("assets/run.png");
    SDL_Surface* slash = IMG_Load("assets/slash.png");

    for(int i = 0; i < 4; i++)
    {
        tx[i] = SDL_CreateTextureFromSurface(renderizador,bg[i]);
        SDL_FreeSurface(bg[i]);
    }

    player.playerPos.x = 0;
	player.playerPos.y = 472;
    player.playerPos.w = player.playerPos.h = 64;
	player.speedX = player.speedY = 0;

    player.texture[0] = SDL_CreateTextureFromSurface(renderizador,idle);
    SDL_QueryTexture(player.texture[0],NULL,NULL, &player.textureHW[0].x, &player.textureHW[0].y);
    player.playerRect[0].x = player.playerRect[0].y = 0;
    player.playerRect[0].w = player.textureHW[0].x / 4;
    player.playerRect[0].h = player.textureHW[0].y;

    player.texture[1] = SDL_CreateTextureFromSurface(renderizador,run);
    SDL_QueryTexture(player.texture[1], NULL, NULL, &player.textureHW[1].x, &player.textureHW[1].y);
    player.playerRect[1].x = player.playerRect[1].y = 0;
    player.playerRect[1].w = player.textureHW[1].x / 3;
    player.playerRect[1].h = player.textureHW[1].y;

    player.texture[2] = SDL_CreateTextureFromSurface(renderizador,slash);
    SDL_QueryTexture(player.texture[2], NULL, NULL, &player.textureHW[2].x, &player.textureHW[2].y);
    player.playerRect[2].x = player.playerRect[2].y = 0;
    player.playerRect[2].w = player.textureHW[2].x / 4;
    player.playerRect[2].h = player.textureHW[2].y;

    player.texture[3] = SDL_CreateTextureFromSurface(renderizador,death);
    SDL_QueryTexture(player.texture[3], NULL, NULL, &player.textureHW[3].x, &player.textureHW[3].y);
    player.playerRect[3].x = player.playerRect[3].y = 0;
    player.playerRect[3].w = player.textureHW[3].x / 4;
    player.playerRect[3].h = player.textureHW[3].y;



    SDL_FreeSurface(idle);
    SDL_FreeSurface(run);
    SDL_FreeSurface(slash);
    SDL_FreeSurface(death);
}

void fechar()
{
    for(int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(tx[i]);
        tx[i] = NULL;
    }

    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(player.texture[i]);
        player.texture[i] = NULL;
    }

    SDL_DestroyRenderer(renderizador);
    renderizador = NULL;

    SDL_DestroyWindow(janela);
    janela = NULL;

    IMG_Quit();
    SDL_Quit();
}
