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
	void SetToScatterState();

private:
	SDL_FRect transform;
	const std::string tag = "Ghost";


	Sprite* currentSprite;
	Sprite mainSprite;
	Sprite scatterSprite;
	const std::string mainSpritePath = "./Assets/pacman-art/ghosts/inky.png";
	const std::string scatterSpritePath = "./Assets/pacman-art/ghosts/blue_ghost.png";

	GhostState state = GhostState::CHASING;
	MoveDirection chosenDirection = MoveDirection::UP;

	std::vector<MoveDirection> possibleDirections;

	float spawnDelay = 2;
	float spawnDelay_p = 0;
	int spawnTileMoves = 2;

	const float speed = 144;
	float movementStack = 0;
	int travelSpaces = TILE_SIZE;

	const float scatterDuration = 5;
	float scatterDuration_p = 0;

	std::weak_ptr<TileGraph> tileGraph;

	void Move(float deltaTime);


	void AI_Random(float deltaTime);

	/*Selects a random adjacent Tile to move to*/
	/*Only choses to reverse it's direction if there is not othe possibility*/
	void AI_Random_ChooseDirection();
};

