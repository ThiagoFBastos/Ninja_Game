#include "images.h"

extern SDL_Renderer* render;

int Intersects(SDL_Rect u, SDL_Rect v)
{
	return !(u.x > v.x + v.w || u.x + u.w < v.x || u.y > v.y + v.h || u.y + u.h < v.y);
}

int HasPoint(int x, int y, SDL_Rect rect)
{
	return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

SDL_Texture* LoadTEXTURE(const char* filename)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	surface = IMG_Load(filename);

	if(surface == NULL)
		fprintf(stderr, "IMG_Load: %s\n", IMG_GetError());
	else
	{
		texture = SDL_CreateTextureFromSurface(render, surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

void LoadTILEMAP(const char* mapfile, const char* map_image)
{
	FILE *f = NULL;

	TILEMAP.texture = LoadTEXTURE(map_image);

	if((f = fopen(mapfile, "r")))
	{
		int k, j;

		for(k = 0; k < TILE_H; k++)
			for(j = 0; j < TILE_W; k++)
				fscanf(f, "%hd", &TILEMAP.tilemap[k][j]);

		fclose(f);
	}
	else
		fprintf(stderr, "Falha ao abrir %s\n", mapfile);
}

// Inacabado
void RenderTILEMAP(SDL_Point cam)
{

	int k, j, w;
	SDL_Rect rect = {0, 0, 32, 32};
	SDL_Rect clip = {0, 0, 32, 32};

	w = 1 + cam.x / 32;

	for(k = 0; k < TILE_H; k++)
	{
		j = cam.x / 32;

		rect.y = 32 * k;
		rect.x = 0;

		for(j = cam.x / 32; j < w; j++)
		{

			if(TILEMAP.tilemap[k][j] > 0)
			{
			    int x, y;

			    x = TILEMAP.tilemap[k][j] % 16;
			    y = TILEMAP.tilemap[k][j] / 16;

				clip.x = 32 * x;
				clip.y = 32 * y;

				SDL_RenderCopy(render, TILEMAP.texture, &clip, &rect);
			}

			rect.x += 32;
		}
	}
}

void RenderIMAGE(IMAGE image, SDL_Point cam)
{
	image.bounds.x = image.bounds.x - cam.x;
	image.bounds.y = image.bounds.y - cam.y;
	SDL_RenderCopy(render, image.texture, NULL, &image.bounds);
}

void RenderSPRITE(SPRITE sprite, SDL_Point cam)
{
	sprite.bounds.x = sprite.bounds.x - cam.x;
	sprite.bounds.y = sprite.bounds.y - cam.y;
	SDL_RenderCopy(render, sprite.texture, &sprite.clip, &sprite.bounds);
}

int Balance(SDL_Rect rect)
{
	if(TILEMAP.tilemap[rect.y / TILE_MIN + 3][rect.x / TILE_MIN])
		return 0;

	return 1;
}

void LoadTEXT(TTF_Font* font, TEXT* text)
{
	SDL_Surface *surface = NULL;

	if(text->selected)
		surface = TTF_RenderText_Solid(font, text->text, text->selectedColor);
	else
		surface = TTF_RenderText_Solid(font, text->text, text->color);

	if(surface == NULL)
		fprintf(stderr, "TTF_RenderText_Solid: %s\n", TTF_GetError());
	else
	{
		text->texture = SDL_CreateTextureFromSurface(render, surface);
		SDL_FreeSurface(surface);
	}
}


void RenderBUTTON(BUTTON button)
{
	SDL_SetRenderDrawColor(render, button.bgColor.r, button.bgColor.g, button.bgColor.b, button.bgColor.a);
	SDL_RenderFillRect(render, &button.bounds);
	SDL_RenderCopy(render, button.field.texture, NULL, &button.field.bounds);
}

void RenderTEXTFIELD(TEXTFIELD textField)
{
	SDL_SetRenderDrawColor(render, textField.bgColor.r, textField.bgColor.g, textField.bgColor.b, textField.bgColor.a);
	SDL_RenderFillRect(render, &textField.bounds);
	SDL_RenderCopy(render, textField.field.texture, NULL, &textField.field.bounds);
}
