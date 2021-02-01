#pragma once
#include <fstream>
#include "Commons.h"
#include "App.h"
#include "Player.h"
#include "Wall.h"
#include "Point.h"

class LevelBuilder
{
public:
	bool BuildLevelFromFile(App& app, std::string filePath);
};

