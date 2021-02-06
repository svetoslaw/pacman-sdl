#pragma once
#include "Commons.h"
#include "Tile.h"

class TileGraph
{
public:
	Tile* GetTileAt(Vector2 position);

	TileGraph(int width, int height);
private:
	std::unique_ptr<Tile[]> tiles;
	int height; /*Number of tiles*/
	int width;

	int GetIndex(int x, int y);
};

