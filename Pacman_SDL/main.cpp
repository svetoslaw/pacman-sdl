#include "Commons.h"
#include "App.h"
#include "Player.h"
#include "Wall.h"


void BuildLevel(App &app)
{
	
}

int main(int argc, char* args[])
{
	App app;
	if (!app.Init())
		printf("Failed to Initialize\n");
	else
	{
		//BuildLevel(app);

		Player player;
		player.setTransform({ 300, 300, PPU, PPU });
		app.AddGameObject(&player);

		Wall wall1;
		wall1.setTransform({ 416, 416, PPU, PPU });
		app.AddGameObject(&wall1);

		Wall wall2;
		wall2.setTransform({ 416, 432, PPU, PPU });
		app.AddGameObject(&wall2);

		Wall wall3;
		wall3.setTransform({ 416, 448, PPU, PPU });
		app.AddGameObject(&wall3);

		app.Start();
	}

	app.Quit();
	return 0;
}