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

bool Point::CheckForCollision(const SDL_FRect& other)
{
	if (other.x > transform.x + transform.w)
		return false;

	if (other.y > transform.y + transform.h)
		return false;

	if (other.x + other.w < transform.x)
		return false;

	if (other.y + other.h < transform.y)
		return false;

	return true;
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
