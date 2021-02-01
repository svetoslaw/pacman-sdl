#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Commons.h"

class Wall : public GameObject
{
public:
	void LoadMedia(SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);

	SDL_FRect getTransform();
	void setTransform(SDL_FRect transform);

	std::string getTag();
private:
	SDL_FRect transform;
	Sprite sprite;
	const std::string spritePath = "./Assets/pacman-art/other/apple.png";

};

