#include "GameObject.h"

SDL_Rect GameObject::getTransform()
{
	return SDL_Rect{ 0, 0, 0, 0 };
}

void GameObject::LoadMedia(SDL_Renderer* renderer)
{
}

void GameObject::Start(){}

void GameObject::Update(){}

void GameObject::Render(SDL_Renderer* renderer){}

void GameObject::HandleEvent(SDL_Event& event){}
