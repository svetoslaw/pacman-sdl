#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Commons.h"


class Player : public GameObject
{
public:
	void LoadMedia(SDL_Renderer* renderer);
	void Start();
	void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

	bool CheckForCollision(const SDL_FRect& other);
	void OnCollision(GameObject& other, float deltaTime);

	SDL_FRect getTransform();
	void setTransform(SDL_FRect transform);

private:
	SDL_FRect transform;
	Sprite sprite;

	const std::string spritePath = "./Assets/pacman-art/pacman-right/1.png";
	const float speed = 300;
	Vector2 movementVelocity;

	void Move(float deltaTime);
	bool CheckForWall();
};
