#pragma once
#include "Commons.h"
#include "App.h"

class Sprite
{
public:
	~Sprite();
	
	bool LoadTexture(SDL_Renderer* renderer, std::string path);
	bool LoadTextureFromText(SDL_Renderer* renderer, TTF_Font* font, std::string text);
	void RenderTexture(SDL_Renderer* renderer, const SDL_FRect* destination);
	void RenderShape(SDL_Renderer* renderer, const SDL_FRect* rect, SDL_Color color);
	
private:
	//move spritePaths to this class
	//std::string texturePath;
	SDL_Texture* texture = NULL;
	//TTF_Font* font = NULL;
};

