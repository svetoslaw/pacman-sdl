#include "Tile.h"

void Tile::setPosition(Vector2 position)
{
    this->position = position;
}

Vector2 Tile::getPosition()
{
    return position;
}

void Tile::setIsPassable(bool b)
{
    passable = b;
}

bool Tile::isPassable()
{
    return passable;
}

GameObject* Tile::getGameObject()
{
    return gameObject;
}

void Tile::setGameObject(GameObject* gameObject)
{
    this->gameObject = gameObject;
}
