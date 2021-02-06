#pragma once
#include "Commons.h"
#include "GameObject.h"
#include "Sprite.h"

class Point : public GameObject
{
public:
	void LoadMedia(SDL_Renderer* renderer);
	void OnCollision(GameObject* other, float deltaTime);
	void Render(SDL_Renderer* renderer);
	
	std::string getTag();

	SDL_FRect getTransform();
	void setTransform(SDL_FRect transform);

private:
	SDL_FRect transform;
	const std::string tag = "Point";

	Sprite sprite;
	const std::string spritePath = "./Assets/pacman-art/other/dot.png";
};

