#pragma once
#include <fstream>
#include "Commons.h"
#include "App.h"
#include "TileGraph.h"
#include "Player.h"
#include "Wall.h"
#include "Point.h"
#include "Ghost.h"
#include "Pill.h"
#include "UI.h"

class LevelBuilder
{
public:
	bool BuildLevelFromFile(App &app, std::string filePath);
private:
    std::ifstream fileStream;

    SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };

    std::shared_ptr<UI> ui;

    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Wall>> walls;
    std::vector<std::shared_ptr<Point>> points;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    std::vector<std::shared_ptr<Pill>> pills;

    int playersCount = 0;
    int wallsCount = 0;
    int pointsCount = 0;
    int ghostsCount = 0;
    int pillsCount = 0;

    std::shared_ptr<TileGraph> tileGraph;

    void CountGameObjectsNeeded();
    void CreateGameObjects();
    void SetupLevel(App &app);

    void BuildUI(App &app);
};

