#pragma once
#include "Commons.h"
#include "GameObject.h"

class Tile
{
public:
	void setPosition(Vector2 position);
	Vector2 getPosition();

	void setIsPassable(bool b);
	bool isPassable();

	GameObject* getGameObject();
	void setGameObject(GameObject* gameObject);

private:
	/*top left corner*/
	Vector2 position; 

	bool passable = true;
	
	/*The GameObject occupying the Tile*/
	GameObject* gameObject;
};

