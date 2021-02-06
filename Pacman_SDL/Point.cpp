#include "Point.h"

SDL_FRect Point::getTransform()
{
    return transform;
}

void Point::setTransform(SDL_FRect transform)
{
	this->transform = transform;
}

void Point::LoadMedia(SDL_Renderer* renderer)
{
	sprite.LoadTexture(renderer, spritePath);
}

void Point::Render(SDL_Renderer* renderer)
{
	sprite.RenderTexture(renderer, &transform);
}

void Point::OnCollision(GameObject& other, float deltaTime)
{
	if (other.getTag() == "Player")
		this->Destroy();
}

std::string Point::getTag()
{
	return tag;
}
