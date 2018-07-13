#define ENEMY_RUN 1
#define ENEMY_SLASH 2
#define ENEMY_DEATH 3

void LoadGameResources()
{
    ...

    int EnQuant = ;
    //Quantidade de inimigos
    for(int i=0;i<EnQuant;i++);

    ENEMY[i].sprites[0].texture = LoadTEXTURE("assets/enemy_slash.png");
	ENEMY[i].sprites[0].w  = 168;
	ENEMY[i].sprites[0].h  = 26;
	ENEMY[i].sprites[0].clip.x = 0;
	ENEMY[i].sprites[0].clip.y = 0;
	ENEMY[i].sprites[0].clip.w = 42;
	ENEMY[i].sprites[0].clip.h = 26;

	ENEMY[i].sprites[1].texture = LoadTEXTURE("assets/enemy_run.png");
    ENEMY[i].sprites[1].w  = 108;
	ENEMY[i].sprites[1].h  = 26;
	ENEMY[i].sprites[1].clip.x = 0;
	ENEMY[i].sprites[1].clip.y = 0;
	ENEMY[i].sprites[1].clip.w = 36;
	ENEMY[i].sprites[1].clip.h = 26;

    ENEMY[i].sprites[2].texture = LoadTEXTURE("assets/enemy_death.png");
	ENEMY[i].sprites[2].w  = 140;
	ENEMY[i].sprites[2].h  = 26;
	ENEMY[i].sprites[2].clip.x = 0;
	ENEMY[i].sprites[2].clip.y = 0;
	ENEMY[i].sprites[2].clip.w = 35;
	ENEMY[i].sprites[2].clip.h = 26;

	//Colocar a coordenada de cada inimigo
	ENEMY[i].bounds.x = ...;
	ENEMY[i].bounds.y = ...;


    ENEMY.state = ENEMY.frame_time = 0;
	...
}


void Game(long int timestamp)
{
    //implementar no game loop
    int aux = 0;
    while(1)
    {
        while(aux != 32){
        for(int i=0;i<EnQuant;i++)
            {
                ENEMY[i].bounds.x++;
                ENEMY[i].dir.x = 1;
            }
            aux++;
        }
        while(aux != -32)
        {
            for(int i=0;i<EnQuant;i++)
            {
                ENEMY[i].bounds.x--;
                ENEMY[i].dir.x = -1;
            }
            aux--;
        }

    }
    //implementar SDL_Rect com o ataque do jogador ao apertar X
    for(int i=0;i<EnQuant;i++)
    {
        if((Intersects(PlayerAtt.bounds,Enemy[i].bounds) == 1)
        {
            ENEMY.state = 3;
            //Desabilitar a colisão ou deslocar o Rect do inimigo pra algum local da tela inacessível
        }
        if((Intersects(Player.bounds,Enemy[i].bounds) == 1)
        {
            ENEMY.state = 2;
            Player.life -=1

            //Se a vida do jogador chegar a 0, vou fazer uma tela que diz game over, e tb vou fazer outra que diz vc venceu, se ele chegar a um determinado X, significando q ele saiu do castelo

        }
}
