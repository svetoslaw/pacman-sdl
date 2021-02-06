#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include <string>
#include <random>
#include <time.h>
#include <memory>
#include "Vector2.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SIZE 16

enum class MoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};