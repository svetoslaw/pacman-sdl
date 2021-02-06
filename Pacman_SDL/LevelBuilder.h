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

class LevelBuilder
{
public:
	bool BuildLevelFromFile(App& app, std::string filePath);
private:

};

