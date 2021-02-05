#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "TileGraph.h"
#include "Commons.h"

class Player : public GameObject
{
public:
	void LoadMedia(SDL_Renderer* renderer);
	void Start();
	void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void OnCollision(GameObject& other, float deltaTime);
	void Render(SDL_Renderer* renderer);

	std::string getTag();

	SDL_FRect getTransform();
	void setTransform(SDL_FRect transform);

	void setTileGraph(TileGraph* tileGraph);

private:
	SDL_FRect transform;
	const std::string tag = "Player";

	Sprite sprite;
	const std::string spritePath = "./Assets/pacman-art/pacman-right/1.png";

	TileGraph* tileGraph;

	MoveDirection nextMove = MoveDirection::NONE;
	MoveDirection tryMove = MoveDirection::NONE;

	const float speed = 160;
	float movementStack = 0; /*Used to lock movement to integer values*/

	unsigned score = 0;

	bool dead = false;

	void Move(float deltaTime);

	bool NextTileIsPassable();
};
