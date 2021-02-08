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
	void SetEndText(std::string text);
private:
	SDL_FRect transform;

	Sprite sprite;

	const SDL_FRect powerBar = { 384, 16, 64, 16 };
	SDL_FRect powerBar_p = { 384, 16, 0, 0 };
	SDL_Color powerBarColor = { 128, 128, 255, 255 };
	const float powerDuration = 5;
	float powerDurtaion_p;

	TTF_Font* font;
	const int fontSize = 64;

	Sprite scoreSprite;
	SDL_FRect scoreTransform = { 384, 32, 80, 48 };
	std::string scoreText = "Score: 0";
	bool updateScore = false;

	Sprite endTextSprite;
	SDL_FRect endTextTransform = { 384, 128, 80, 48 };
	std::string endText = "";
	bool updateEndText = false;

	void ReducePowerBar(float deltaTime);
	void ReloadScore(SDL_Renderer* renderer);
	void ReloadEndText(SDL_Renderer* renderer);
};

