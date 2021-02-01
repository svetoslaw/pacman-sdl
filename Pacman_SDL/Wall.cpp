#include "Wall.h"

void Wall::LoadMedia(SDL_Renderer* renderer)
{
	sprite.LoadTexture(renderer, spritePath);
}

void Wall::Render(SDL_Renderer* renderer)
{
	sprite.RenderTexture(renderer, &transform);
}

SDL_FRect Wall::getTransform()
{
	return transform;
}

void Wall::setTransform(SDL_FRect transform)
{
	this->transform = transform;
}

std::string Wall::getTag()
{
	return tag;
}
