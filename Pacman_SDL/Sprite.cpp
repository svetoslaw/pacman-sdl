#include "Sprite.h"

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

bool Sprite::LoadTexture(SDL_Renderer* renderer, std::string path)
{
	bool successFlag = true;
	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
	{
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		successFlag = false;
	}
	return successFlag;
}

void Sprite::RenderTexture(SDL_Renderer* renderer, const SDL_FRect* destination)
{
	SDL_RenderCopyF(renderer, texture, NULL, destination);
}
