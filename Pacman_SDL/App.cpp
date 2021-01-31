#include "App.h"
#include <Player.h>

bool App::Init()
{
	bool successFlag = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		successFlag = false;
	}
	else
	{
		window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			successFlag = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				successFlag = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					successFlag = false;
				}
				else 
				{
					//Everything is OK
				}
			}
		}
	}

	return successFlag;
}

void App::Start()
{
	bool quit = false;
	SDL_Event event;

	/*Load all the assets of the gameObjects*/
	for (auto& gameObject : gameObjects)
		gameObject->LoadMedia(renderer);

	/*Execute Start() for all of the gameObjects*/
	for (auto& gameObject : gameObjects)
		gameObject->Start();

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			/*Handle the event for each gameObject*/
			for (auto& gameObject : gameObjects)
				gameObject->HandleEvent(event);
		}

		/*Call Update() for all of the gameObjects*/
		for (auto& gameObject : gameObjects)
			gameObject->Update();

		SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
		SDL_RenderClear(renderer);

		/*Render all of the gameObjects*/
		for (auto& gameObject : gameObjects)
			gameObject->Render(renderer);

		SDL_RenderPresent(renderer);
	}
}

void App::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void App::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

