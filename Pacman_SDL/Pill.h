#pragma once
#include "Commons.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Ghost.h"

class Pill : public GameObject
{
public:
	void LoadMedia(SDL_Renderer* renderer);
	void Start();
	void OnCollision(GameObject* other, float deltaTime);
	void Render(SDL_Renderer* renderer);

	std::string getTag();

	SDL_FRect getTransform();
	void setTransform(SDL_FRect transform);

	void AddGhost(const std::shared_ptr<Ghost> &ghost);
private:
	SDL_FRect transform;
	const std::string tag = "Pill";

	Sprite sprite;
	const std::string spritePath = "./Assets/pacman-art/other/strawberry.png";

	std::vector<std::weak_ptr<Ghost>> ghosts;
};

