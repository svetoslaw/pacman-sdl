#include "Game.h"

void Game::Start()
{
	if (!Init())
		printf("Failed to initialize!\n");
	else
	{
		Loop();
	}
}
