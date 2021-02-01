#include "Commons.h"
#include "App.h"
#include "Player.h"
#include "Wall.h"
#include "Point.h"
#include "LevelBuilder.h"

int main(int argc, char* args[])
{
	App app;
	if (!app.Init())
		printf("Failed to Initialize\n");
	else
	{
		LevelBuilder lb;
		lb.BuildLevelFromFile(app, "./Assets/levels/level1.txt");

		
		/*
		Wall wall;
		wall.setTransform({ 32, 32, 16, 16 });
		app.AddGameObject(&wall);

		Player player;
		player.setTransform({ 64, 64, 16, 16 });
		app.AddGameObject(&player);
		*/

		app.Start();
	}

	app.Quit();
	return 0;
}