#include "App.h"

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
					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						successFlag = false;
					}
					else 
					{
						deltaTime = 0;
						lastTime = SDL_GetTicks();
						//Everything is OK
					}
				}
			}
		}
	}

	return successFlag;
}

void App::Start()
{
	/*Load all the assets of the gameObjects*/
	for (auto& gameObject : gameObjects)
		gameObject->LoadMedia(renderer);

	/*Execute Start() for all of the gameObjects*/
	for (auto& gameObject : gameObjects)
		gameObject->Start();

	MainLoop();
}

void App::Quit()
{
	//for (auto& gameObject : gameObjects)
	//	delete gameObject;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void App::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	gameObjects.push_back(gameObject);
}

std::vector<std::shared_ptr<GameObject>> App::getGameObjects()
{
	return gameObjects;
}

void App::setTileGraph(const std::shared_ptr<TileGraph> &tileGraph)
{
	this->tileGraph = tileGraph;
}

void App::MainLoop()
{
	bool quit = false;
	SDL_Event event;

	/*Main Loop*/
	while (!quit)
	{
		DestroyObjects();

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
			gameObject->Update(deltaTime);

		/*Collision Check*/
		CollisionCheck();

		Render();

		deltaTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks();

		//printf("size: %i\n", gameObjects.size());
	}
}

void App::DestroyObjects()
{
	auto it = gameObjects.begin();
	while (it != gameObjects.end())
	{
		if ((*it)->ToDestroy())
		{
			//delete *it;
			it = gameObjects.erase(it);
		}
		else
			it++;
	}
}

void App::CollisionCheck()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		for (size_t j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[i]->CheckForCollision(gameObjects[j]->getTransform()))
			{
				gameObjects[i]->OnCollision(gameObjects[j].get(), deltaTime);
				gameObjects[j]->OnCollision(gameObjects[i].get(), deltaTime);
			}
		}
	}
}

void App::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	/*Render all of the gameObjects*/
	for (auto& gameObject : gameObjects)
		gameObject->Render(renderer);

	SDL_RenderPresent(renderer);
}
