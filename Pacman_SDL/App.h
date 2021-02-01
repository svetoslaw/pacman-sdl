#pragma once
#include "Commons.h"
#include "GameObject.h"


//temp solution

class App
{
public:

	bool Init();
	void Start();
	void Quit();

	void AddGameObject(GameObject* gameObject);
	//SDL_Texture* LoadTexture(std::string path);

	//Try NOT to pass the renderer around
	SDL_Renderer* renderer;

private:
	std::vector<GameObject*> gameObjects;
	float deltaTime; /*Delta Time since last frame in seconds*/
	float lastTime;
	SDL_Window* window;

	void MainLoop();
};

