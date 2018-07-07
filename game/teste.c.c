#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>


void iniciar();
void carregarmedia();
void fechar();

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
    const int FPS = 60;
    int frametime = 0;
    iniciar();
    carregarmedia();
    SDL_Event evento;

    SDL_QueryTexture(playerT,NULL,NULL,&TextureW,&TextureH);
    FrameH = TextureH;
    FrameW = TextureW/4;

    PlayerRect.x = PlayerRect.y = 0;
    PlayerRect.w = FrameW;
    PlayerRect.h = FrameH;

    PlayerPos.x = PlayerPos.y = 0;
    PlayerPos.w = PlayerPos.h = 128;

    //Game loop
    while(quit == 0)
    {
        SDL_SetRenderDrawColor(renderizador,111,133,255,255);
        SDL_RenderClear(renderizador);

        while(SDL_PollEvent(&evento) != 0)
        {
            if(evento.type == SDL_QUIT)
                quit = 1;

            if(evento.type == SDL_KEYDOWN)
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

            if(evento.type == SDL_KEYUP)
            {
                switch(evento.key.keysym.sym)
                {
                    case SDLK_UP:
                    break;

                    case SDLK_DOWN:
                    break;

                    case SDLK_RIGHT:
                    playerT = SDL_CreateTextureFromSurface(renderizador,idle);
                    FrameW = TextureW/4;
                    break;

                    case SDLK_LEFT:
                    break;
                }
            }
        }
     frametime++;
     if(FPS / frametime == 4)
     {
         frametime = 0;
         PlayerRect.x += FrameW;
         if(PlayerRect.x >= TextureW)
            PlayerRect.x = 0;
     }

    for(int i=0;i<4;i++)
    SDL_RenderCopy(renderizador,tx[i],NULL,NULL);
    SDL_RenderCopy(renderizador,playerT,&PlayerRect,&PlayerPos);
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


    for(int i=0;i<4;i++)
        tx[i] = SDL_CreateTextureFromSurface(renderizador,bg[i]);
    playerT = SDL_CreateTextureFromSurface(renderizador,idle);
}

void fechar()
{
    for(int i=0;i<4;i++)
        {
            SDL_FreeSurface(bg[i]);
            bg[i] = 0;
        }

    SDL_DestroyWindow(janela);
    janela = 0;

    SDL_DestroyRenderer(renderizador);
    renderizador = 0;

    SDL_Quit();
}

