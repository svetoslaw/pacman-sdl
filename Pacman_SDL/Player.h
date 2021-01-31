#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vector2.h"

class Player : public GameObject
{
public:
	void LoadMedia(SDL_Renderer* renderer);
	void Start();
	void HandleEvent(SDL_Event& event);
	void Update();
	void Render(SDL_Renderer* renderer);

	SDL_Rect getTransform();
	void setTransform(SDL_Rect transform);

private:
	SDL_Rect transform;
	Sprite sprite;

	const std::string spritePath = "./Assets/pacman-art/pacman-right/1.png";
	const int speed = 2;
	Vector2 movement;

	void Move(Vector2 movement);
};

