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
	void OnCollision(GameObject* other, float deltaTime);
	void Render(SDL_Renderer* renderer);

	std::string getTag();

	SDL_FRect getTransform();
	void setTransform(SDL_FRect transform);

	void setTileGraph(const std::shared_ptr<TileGraph> &tileGraph);

	GhostState getState();
	void SetToChasingState();
	void SetToScatterState();
	void SetToReturningState();

private:
	SDL_FRect transform;
	const std::string tag = "Ghost";


	Sprite* currentSprite;

	Sprite mainSprite;
	const std::string mainSpritePath = "./Assets/pacman-art/ghosts/inky.png";

	Sprite scatterSprite;
	const std::string scatterSpritePath = "./Assets/pacman-art/ghosts/blue_ghost.png";

	Sprite returnSprite;
	const std::string returnSpritePath = "./Assets/pacman-art/ghosts/eyes.png";

	Vector2 spawnPosition;

	GhostState state = GhostState::CHASING;
	MoveDirection chosenDirection = MoveDirection::UP;

	std::vector<MoveDirection> possibleDirections;
	std::deque<MoveDirection> pathToSpawn;

	float spawnDelay = 3;
	float spawnDelay_p = 0;
	int spawnTileMoves = 2;

	float speed = 112;
	const float pillSpeedChange = 32;
	float movementStack = 0;
	int travelSpaces = TILE_SIZE;

	const float scatterDuration = 5;
	float scatterDuration_p = 0;

	std::weak_ptr<TileGraph> tileGraph;

	void Move(float deltaTime);
	void MoveToSpawn(float deltaTime);
	void MoveToSpawn2(float deltaTime);

	void AI_Random(float deltaTime);

	/*Selects a random adjacent Tile to move to*/
	/*Only choses to reverse it's direction if there is not othe possibility*/
	void AI_Random_ChooseDirection();
};

