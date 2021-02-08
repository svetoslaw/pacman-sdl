#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "TileGraph.h"
#include "Ghost.h"
#include "Commons.h"
#include "UI.h"

class Player : public GameObject
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

	void AddGhost(const std::shared_ptr<Ghost> &ghost);
	void AddUI(const std::shared_ptr<UI>& ui);
	void SetNumberOfPoints(int number);
private:
	SDL_FRect transform;
	const std::string tag = "Player";

	Sprite sprite;
	const std::string spritePath = "./Assets/pacman-art/pacman-right/1.png";

	std::weak_ptr<TileGraph> tileGraph;

	MoveDirection nextMove = MoveDirection::NONE;
	MoveDirection tryMove = MoveDirection::NONE;

	float speed = 112;
	float movementStack = 0; /*Used to lock movement to integer values*/

	std::vector<std::weak_ptr<Ghost>> ghosts;
	std::weak_ptr<UI> ui;

	unsigned score = 0;

	//Better to controll the game state in a separate Class
	int numberOfPoints = 0;

	void Move(float deltaTime);

	//bool NextTileIsPassable();
	/*supperior*/
	bool NextTileIsPassable2();
	void Win();
};
