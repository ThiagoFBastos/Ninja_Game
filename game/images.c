#include "images.h"

int Intersects(Rect u, Rect v)
{
	if(u.x > v.x + v.w || u.x + u.w < v.x)
		return 0;

	else if(u.y > v.y + v.h || u.y + u.h < v.y)
		return 0;

	return 1;
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
				fscanf(f, "%d", &tilemap[k][j]);

		fclose(f);
	}
}

// Inacabado
void RenderMap(SDL_Point cam)
{
	int k, j, w;

	w = TILE_CAM_W + cam.x / TILE_MIN;

	for(k = 0; k < TILE_H; k++)
	{
		j = cam.x / TILE_MIN;

		while(j < w)
		{

			SDL_RenderCopy(render, TILEMAP.texture, &rect, &clip);
			j++;
		}
	}

}

void Render_ImageCam(Image* image, SDL_Point cam)
{
	SDL_Rect r = image->rect;

	r.x -= cam.x;
	r.y -= cam.y;

	SDL_RenderCopy(render, image->texture, &r, NULL);
}

void Render_Sprite(Sprite* sprite, SDL_Point cam)
{
	SDL_Rect r, clip;

	r = clip = sprite->rect;

	r.x -= cam.x;
	r.y -= cam.y;

	

	SDL_RenderCopy(render, image->texture, &r, &clip);
}
