#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#define FPS 60

void iniciar();
void carregarmedia();
void fechar();

typedef struct
{
    SDL_Texture *texture[2];
    SDL_Rect playerPos;
    SDL_Rect playerRect[2]; //Posição de um frame em relação à imagem
    SDL_Point textureHW[2]; //Dimensão das texturas
    
}SPRITE;

SPRITE player;

SDL_Window* janela = 0;
SDL_Renderer* renderizador = 0;
SDL_Texture* tx[4];

int quit = 0;

int main (int argc, char **argv)
{
    int frametime = 0;
    int playerId = 0;
    
    iniciar();
    carregarmedia();
    
    //Game loop
    while(quit == 0)
    {
        SDL_Event evento;
        
        playerId = 0;
        
        SDL_SetRenderDrawColor(renderizador,111,133,255,255);
        SDL_RenderClear(renderizador);

        while(SDL_PollEvent(&evento) != 0)
        {
            if(evento.type == SDL_QUIT)
                quit = 1;

            else if(evento.type == SDL_KEYDOWN)
            {
                switch(evento.key.keysym.sym)
                {
                    case SDLK_UP:
                        player.playerPos.y -= 10;
                    break;
                        
                    case SDLK_DOWN:
                        player.playerPos.y += 10;
                    break;

                    case SDLK_RIGHT:
                        frametime = 0;
                        player.playerRect[playerId].x = 0;
                        player.playerPos.x += 10;
                        playerId = 1;
                    break;

                    case SDLK_LEFT:
                        player.playerPos.x -= 10;
                    break;

                    case SDLK_ESCAPE:
                        quit = 1;
                    break;
                }
            }
        }
        
     frametime++;
        
     if(FPS / frametime ==  player.textureHW[playerId] / player.playerRect[playerId].w)
     {
         frametime = 0;
         
         player.playerRect[playerId].x += player.playerRect[playerId].w;
         
         if(player.playerRect[playerId].x >= player.playerRect[playerId].w)
            player.playerRect[playerId].x = 0;
     }

    for(int i = 0;i < 4; i++)
        SDL_RenderCopy(renderizador,tx[i],NULL,NULL);
        
    for(int j = 0; j < 2; j++)
        SDL_RenderCopy(renderizador, player.texture[j], &player.playerRect[j], &player.playerPos[j]);
        
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
    
    for(int i = 0; i < 4; i++)
    {
        tx[i] = SDL_CreateTextureFromSurface(renderizador,bg[i]);
        SDL_FreeSurface(bg[i]);
    }
    
    player.playerPos.x = player.playerPos.y = 0;
    player.playerPos.w = player.playerPos.h = 128;
    
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
    
    SDL_FreeSurface(idle);
    SDL_FreeSurface(run);
}

void fechar()
{
    for(int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(tx[i]);
        tx[i] = NULL;
    }

    for(int i = 0; i < 2; i++)
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

