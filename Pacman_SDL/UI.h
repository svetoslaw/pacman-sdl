#pragma once
#include "Commons.h"
#include "GameObject.h"
#include "Sprite.h"

class UI : public GameObject
{
public:
	SDL_FRect getTransform();
	void LoadMedia(SDL_Renderer* renderer);
	//void Start();
	//void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer);

	void ActivatePowerBar();
	void SetScoreText(int score);
private:
	SDL_FRect transform;

	Sprite sprite;

	Sprite scoreSprite;
	TTF_Font* font;
	SDL_FRect scoreTransform = { 384, 32, 64, 32 };
	std::string scoreText = "Score: 0";
	bool updateScore = false;

	const SDL_FRect powerBar = { 384, 16, 64, 16 };
	SDL_FRect powerBar_p = { 384, 16, 0, 0 };
	SDL_Color powerBarColor = { 128, 128, 255, 255 };
	const float powerDuration = 5;
	float powerDurtaion_p;

	void ReducePowerBar(float deltaTime);
	void ReloadScore(SDL_Renderer* renderer);
};

