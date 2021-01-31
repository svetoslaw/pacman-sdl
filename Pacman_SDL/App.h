#pragma once
#include "Commons.h"
#include "GameObject.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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

	SDL_Window* window;
};

