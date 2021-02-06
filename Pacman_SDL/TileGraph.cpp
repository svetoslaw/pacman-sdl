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