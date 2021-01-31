#include "Commons.h"
#include "App.h"
#include <Player.h>

int main(int argc, char* args[])
{
	App app;
	if (!app.Init())
		printf("Failed to Initialize\n");
	else
	{
		Player player;
		player.setTransform({ 300, 300, 16, 16 });
		app.AddGameObject(&player);
		app.Start();
	}

	app.Quit();
	return 0;
}