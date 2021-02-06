#pragma once
#include "Commons.h"
#include "GameObject.h"
#include "TileGraph.h"

//temp solution

class App
{
public:

	bool Init();
	void Start();
	void Quit();

	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	std::vector<std::shared_ptr<GameObject>> getGameObjects();
	//SDL_Texture* LoadTexture(std::string path);

	void setTileGraph(const std::shared_ptr<TileGraph> &tileGraph);

	//Try NOT to pass the renderer around
	SDL_Renderer* renderer;

private:
	std::vector<std::shared_ptr<GameObject>> gameObjects; //adapt to use a list instead
	std::shared_ptr<TileGraph> tileGraph;

	float deltaTime; /*Delta Time since last frame in seconds*/
	float lastTime;
	SDL_Window* window;

	void MainLoop();
	void DestroyObjects();
	void CollisionCheck();
	void Render();
};
