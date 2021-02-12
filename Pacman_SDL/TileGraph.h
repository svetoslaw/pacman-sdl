#pragma once
#include "Commons.h"
#include "Tile.h"

struct PriorityNode
{
	float totalCost;
	float cost;
	std::deque<MoveDirection> path;
	Tile* node;
	
	/*bool operator<(const PriorityNode& other)
	{
		return this->totalCost < other.totalCost;
	}*/
	bool operator()(PriorityNode a, PriorityNode b)
	{
		return a.totalCost > b.totalCost;
	}
};

class TileGraph
{
public:
	Tile* GetTileAt(Vector2 position);

	TileGraph(int width, int height);
	std::deque<MoveDirection> FindPath(Tile* start, Tile* goal);
private:
	std::unique_ptr<Tile[]> tiles;
	int height; /*Number of tiles*/
	int width;

	int GetIndex(int x, int y);
	float Heuristic(Tile* current, Tile* goal);
	Tile* GetAdjacentTile(Tile* tile, MoveDirection direction);
};

