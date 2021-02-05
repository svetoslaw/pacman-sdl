#pragma once
#include "Commons.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TileGraph.h"

enum class GhostState
{
	SPAWNING,
	CHASING,
	SCATTERING,
	RETURNING
};

class Ghost : public GameObject
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

	GhostState getState();

private:
	SDL_FRect transform;
	const std::string tag = "Ghost";

	Sprite sprite;
	const std::string spritePath = "./Assets/pacman-art/ghosts/inky.png";

	GhostState state = GhostState::CHASING;
	MoveDirection chosenDirection = MoveDirection::UP;
	float spawnDelay = 2;
	float spawnDelay_p = 0;
	int spawnTileMoves = 2;
	const float speed = 160;
	float movementStack = 0;
	int travelSpaces = TILE_SIZE;
	std::vector<MoveDirection> possibleDirections;

	TileGraph* tileGraph;

	void Move(float deltaTime);

	void AI_Random(float deltaTime);
	void AI_Random_ChooseDirection();
};

