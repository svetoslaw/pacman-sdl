#include "Pill.h"

void Pill::LoadMedia(SDL_Renderer* renderer)
{
	sprite.LoadTexture(renderer, spritePath);
}

void Pill::Render(SDL_Renderer* renderer)
{
	sprite.RenderTexture(renderer, &transform);
}

void Pill::Start()
{

}

void Pill::OnCollision(GameObject* other, float deltaTime)
{
	if (other->getTag() == "Player")
		this->Destroy();
}

SDL_FRect Pill::getTransform()
{
	return transform;
}

void Pill::setTransform(SDL_FRect transform)
{
	this->transform = transform;
}

std::string Pill::getTag()
{
	return tag;
}
