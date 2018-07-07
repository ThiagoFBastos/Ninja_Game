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
SDL_Surface* bg[4];
SDL_Surface* idle;
SDL_Surface* run;
SDL_Renderer* renderizador = 0;
SDL_Texture* tx[4];
SDL_Texture* playerT;
SDL_Rect PlayerRect;
SDL_Rect PlayerPos;
int FrameW,FrameH;
int TextureW,TextureH;


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
                    PlayerPos.y -= 10;

                    break;

                    case SDLK_DOWN:
                    PlayerPos.y += 10;
                    break;

                    case SDLK_RIGHT:
                    PlayerPos.x += 10;
                    playerT = SDL_CreateTextureFromSurface(renderizador,run);
                    FrameW = TextureW/3;
                    break;

                    case SDLK_LEFT:
                    PlayerPos.x -= 10;
                    break;

                    case SDLK_ESCAPE:
                    quit = 1;
                    break;
                }
            }
        }
        
     frametime++;
        
     if(FPS / frametime == 4)
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
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }

    janela = SDL_CreateWindow("jogo",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);

    IMG_Init(IMG_INIT_PNG);

    renderizador = SDL_CreateRenderer(janela,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void carregarmedia()
{
    bg[0] = IMG_Load("assets/bg/0.png");
    bg[1] = IMG_Load("assets/bg/1.png");
    bg[2] = IMG_Load("assets/bg/2.png");
    bg[3] = IMG_Load("assets/bg/3.png");
    idle = IMG_Load("assets/idle.png");
    run = IMG_Load("assets/run.png");


    for(int i = 0; i < 4; i++)
        tx[i] = SDL_CreateTextureFromSurface(renderizador,bg[i]);
    
    player.playerPos.x = player.playerPos.y = 0;
    player.playerPos.w = player.playerPos.h = 128;
    
    player.texture[0] = SDL_CreateTextureFromSurface(renderizador,idle);
    SDL_QueryTexture(player.texture[0],NULL,NULL, &player.textureWH[0].x, &player.textureHW[0].y);
    player.playerRect[0].x = player.playerRect[0].y = 0;
    player.playerRect[0].w = player.textureWH[0].x / 4;
    player.playerRect[0].h = player.textureWH[0].y;
        
    player.texture[1] = SDL_CreateTextureFromSurface(renderizador,run);
    SDL_QueryTexture(player.texture[1], NULL, NULL, &player.textureHW[1].x, &player.textureHW[1].y);
    player.playerRect[1].x = player.playerRect[1].y = 0;
    player.playerRect[1].w = player.textureWH[1].x / 3;
    player.playerRect[1].h = player.textureWH[1].y;
    
    SDL_FreeSurface(idle);
    SDL_FreeSurface(run);
}

void fechar()
{
    for(int i=0;i<4;i++)
    {
            SDL_FreeSurface(bg[i]);
            bg[i] = 0;
        }

      
     SDL_DestroyRenderer(renderizador);
    renderizador = 0;
    
    SDL_DestroyWindow(janela);
    janela = 0;

    IMG_Quit();
    SDL_Quit();
}

