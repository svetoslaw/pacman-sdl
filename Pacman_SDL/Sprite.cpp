#include "Sprite.h"

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

bool Sprite::LoadTexture(SDL_Renderer* renderer, std::string path)
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture == NULL;
	}

	bool successFlag = true;
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		successFlag = false;
	}
	return successFlag;
}

bool Sprite::LoadTextureFromText(SDL_Renderer* renderer, TTF_Font* font, std::string text)
{
	bool successFlag = true;

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), { 255, 255, 255, 255 });
	if (surface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		if (texture != NULL)
		{
			SDL_DestroyTexture(texture);
			texture == NULL;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			successFlag = false;
		}

		SDL_FreeSurface(surface);
	}

	return successFlag;
}



void Sprite::RenderTexture(SDL_Renderer* renderer, const SDL_FRect* destination)
{
	SDL_RenderCopyF(renderer, texture, NULL, destination);
}

void Sprite::RenderShape(SDL_Renderer* renderer, const SDL_FRect* rect, SDL_Color color)
{
	Uint8 color_r;
	Uint8 color_g;
	Uint8 color_b;
	Uint8 color_a;
	SDL_GetRenderDrawColor(renderer, &color_r, &color_g, &color_b, &color_a);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(renderer, rect);

	SDL_SetRenderDrawColor(renderer, color_r, color_g, color_b, color_a);
}
