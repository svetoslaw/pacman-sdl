#include "TileGraph.h"

TileGraph::TileGraph(int width, int height)
{
	this->width = width;
	this->height = height;

	
	tiles = std::make_unique<Tile[]>(width * height);
	for (int y = 0; y < width; y++)
	{
		for (int x = 0; x < height; x++)
		{
			tiles[x + y * width].setPosition(Vector2(x * TILE_SIZE, y * TILE_SIZE));
		}
	}
}

Tile* TileGraph::GetTileAt(Vector2 position)
{
	int index = GetIndex(position.x / TILE_SIZE, position.y / TILE_SIZE);
	if (index < 0)
		return NULL;

	return &tiles[index];
}

int TileGraph::GetIndex(int x, int y)
{
	if (x >= width || y >= height)
		return -1;

	if (x < 0 || y < 0)
		return -1;

	return x + y * width;
}

std::deque<MoveDirection> TileGraph::FindPath(Tile* start, Tile* goal)
{
	std::priority_queue<PriorityNode, std::vector<PriorityNode>, PriorityNode> priorityQueue;
	std::deque<MoveDirection> path;
	std::set<Tile*> visited;
	Tile* neighbour;
	priorityQueue.push({ Heuristic(start, goal), 0, path, start });

	std::vector<MoveDirection> cardinalDirections = { MoveDirection::UP, MoveDirection::DOWN, MoveDirection::LEFT, MoveDirection::RIGHT };
	while (!priorityQueue.empty())
	{
		PriorityNode current = priorityQueue.top();
		priorityQueue.pop();

		if (current.node == goal)
			return current.path;
		if (visited.find(current.node) != visited.end())
			continue;

		visited.insert(current.node);

		for (auto direction : cardinalDirections)
		{
			neighbour = GetAdjacentTile(current.node, direction);
			if (neighbour->isPassable())
			{
				std::deque<MoveDirection> newPath = current.path;
				newPath.push_back(direction);
				priorityQueue.push({current.cost + Heuristic(neighbour, goal), current.cost + 1, newPath, neighbour});
			}
		}
	}

	return std::deque<MoveDirection>();
}

float TileGraph::Heuristic(Tile* current, Tile* goal)
{
	return abs(current->getPosition().x - goal->getPosition().x) + abs(current->getPosition().y - goal->getPosition().y);
}

Tile* TileGraph::GetAdjacentTile(Tile* tile, MoveDirection direction)
{
	int dx = 0;
	int dy = 0;
	switch (direction)
	{
	case MoveDirection::UP:
		dy = -1;
		break;
	case MoveDirection::DOWN:
		dy = TILE_SIZE;
		break;
	case MoveDirection::LEFT:
		dx = -1;
		break;
	case MoveDirection::RIGHT:
		dx = TILE_SIZE;
		break;
	case MoveDirection::NONE:
		break;
	default:
		break;
	}

	return GetTileAt(Vector2(tile->getPosition().x + dx, tile->getPosition().y + dy));
}
