#pragma once
#include "Commons.h"
#include "App.h"

class Sprite
{
public:
	/*
	Sprite();
	Sprite(std::string path);
	Sprite(std::string path, SDL_Rect transform);

	void setPath(std::string path);
	std::string getPath();
	void setTexture(SDL_Texture* texture);
	*/

	~Sprite();

	//SDL_Texture* getTexture();
	
	bool LoadTexture(SDL_Renderer* renderer, std::string path);
	void RenderTexture(SDL_Renderer* renderer, const SDL_FRect* destination);
	
private:
	//move spritePaths to this class
	//std::string texturePath;
	SDL_Texture* texture = NULL;
};

