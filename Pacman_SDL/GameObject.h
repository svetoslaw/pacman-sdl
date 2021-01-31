#pragma once
#include "Commons.h"

class GameObject
{
public:
	virtual SDL_Rect getTransform();
	virtual void LoadMedia(SDL_Renderer* renderer);
	virtual void Start();
	virtual void HandleEvent(SDL_Event& event);
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
};
