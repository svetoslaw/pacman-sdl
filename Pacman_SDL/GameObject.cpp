#include "GameObject.h"

SDL_FRect GameObject::getTransform()
{
	return SDL_FRect{ 0, 0, 0, 0 };
}

void GameObject::setTransform(){}

std::string GameObject::getTag()
{
	return "";
}

void GameObject::LoadMedia(SDL_Renderer* renderer){}

void GameObject::Start(){}

void GameObject::Update(float deltaTime){}

void GameObject::Render(SDL_Renderer* renderer){}

bool GameObject::CheckForCollision(const SDL_FRect& other) {
	if (other.x >= getTransform().x + getTransform().w)
		return false;

	if (other.y >= getTransform().y + getTransform().h)
		return false;

	if (other.x + other.w <= getTransform().x)
		return false;

	if (other.y + other.h <= getTransform().y)
		return false;

	return true;
}

void GameObject::OnCollision(GameObject& other, float deltaTime){}

bool GameObject::ToDestroy(){ return toDestroy; }

void GameObject::Destroy()
{
	toDestroy = true;
}

GameObject::~GameObject()
{
}

void GameObject::HandleEvent(SDL_Event& event){}