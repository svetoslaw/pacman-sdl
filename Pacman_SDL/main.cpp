#include "Commons.h"
#include "App.h"
#include "Player.h"
#include "Wall.h"
#include "Point.h"
#include "LevelBuilder.h"

int main(int argc, char* args[])
{
	srand(time(0));

	App app;
	if (!app.Init())
		printf("Failed to Initialize\n");
	else
	{
		//try to remove
		LevelBuilder lb;
		lb.BuildLevelFromFile(app, "./Assets/levels/level1.txt");
		app.Start();
	}

	app.Quit();
	return 0;
}