#include "images.h"

int Intersects(SDL_Rect u, SDL_Rect v)
{
	if(u.x > v.x + v.w || u.x + u.w < v.x)
		return 0;

	else if(u.y > v.y + v.h || u.y + u.h < v.y)
		return 0;

	return 1;
}

int HasPoint(SDL_Point point, SDL_Rect rect)
{
	if((point.x >= rect.x && point.x <= rect.x + rect.w) && (point.y >= rect.y && point.y <= rect.y + rect.h))
		return 1;
	
	return 0;
}

SDL_Texture* LoadTexture(const char* filename)
{
	SDL_Surface *surface = IMG_Load(filename);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);

	SDL_FreeSurface(surface);

	return texture;
}

void LoadMap(const char* mapfile, const char* map_image)
{
	FILE *f = NULL;

	TILEMAP.texture = LoadTexture(map_image);

	if(!(f = fopen(mapfile, "r")))
		fprintf(stderr, "Falha ao abrir %s\n", mapfile);
	else
	{
		int k, j;

		for(k = 0; k < TILE_H; k++)
			for(j = 0; j < TILE_W; k++)
				fscanf(f, "%hd", &tilemap[k][j]);

		fclose(f);
	}
}

// Inacabado
void RenderMap(SDL_Point cam)
{
	int k, j, w;
	SDL_Rect rect = {TILE_MIN, TILE_MIN, 0, 0};
	SDL_Rect clip = {TILE_MIN, TILE_MIN, 0, 0};

	w = TILE_CAM_W + cam.x / TILE_MIN;

	for(k = 0; k < TILE_H; k++)
	{
		j = cam.x / TILE_MIN;

		rect.y = k * TILE_MIN;

		while(j < w)
		{

			if(TILEMAP.tilemap[k][j] > 0)
			{
				clip.x = TILEMAP.tilemap[k][j] % TILE_W;
				clip.y = TILEMAP.tilemap[k][j] / TILE_H;

				SDL_RenderCopy(render, TILEMAP.texture, &TILEMAP.rect, &clip);
			}

			rect.x += TILE_MIN;
			j++;
		}
	}

}

void Render_Image(Image* image, SDL_Point cam)
{
	SDL_Rect r = image->rect;

	r.x -= cam.x;
	r.y -= cam.y;

	SDL_RenderCopy(render, image->texture, NULL, &r);
}

void Render_Sprite(Sprite* sprite, SDL_Point cam)
{
	SDL_Rect r, clip;

	r = clip = sprite->bounds;

	r.x -= cam.x;
	r.y -= cam.y;

	SDL_RenderCopy(render, image->texture, &clip, &r);
}

int Balance(SDL_Rect rect)
{
	if(TILEMAP.tilemap[rect.y / TILE_MIN + 3][rect.x / TILE_MIN])
		return 0;
	
	return 1;
}
