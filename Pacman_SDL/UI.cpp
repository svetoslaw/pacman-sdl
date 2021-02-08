#include "UI.h"

SDL_FRect UI::getTransform()
{
	return transform;
}

void UI::LoadMedia(SDL_Renderer* renderer)
{
	font = TTF_OpenFont("./Assets/OpenSans-Regular.ttf", fontSize);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		scoreSprite.LoadTextureFromText(renderer, font, scoreText);
		//endTextSprite.LoadTextureFromText(renderer, font, endText);
	}
}

void UI::Update(float deltaTime)
{
	if (powerDurtaion_p > 0)
		ReducePowerBar(deltaTime);
}

void UI::Render(SDL_Renderer* renderer)
{
	sprite.RenderShape(renderer, &powerBar_p, powerBarColor);

	if (updateScore)
	{
		ReloadScore(renderer);
		updateScore = false;
	}

	if (updateEndText)
	{
		ReloadEndText(renderer);
		updateEndText = false;
	}

	scoreSprite.RenderTexture(renderer, &scoreTransform);
	endTextSprite.RenderTexture(renderer, &endTextTransform);
}

void UI::ActivatePowerBar()
{
	powerBar_p = powerBar;
	powerDurtaion_p = powerDuration;
}

void UI::SetScoreText(int score)
{
	scoreText = "Score: " + std::to_string(score);
	updateScore = true;
}

void UI::SetEndText(std::string text)
{
	endText = text;
	updateEndText = true;
}

void UI::ReducePowerBar(float deltaTime)
{
	powerDurtaion_p -= deltaTime;

	powerBar_p.w -= (powerBar.w * deltaTime) / powerDuration;
}

void UI::ReloadScore(SDL_Renderer* renderer)
{
	scoreSprite.LoadTextureFromText(renderer, font, scoreText);
}

void UI::ReloadEndText(SDL_Renderer* renderer)
{
	endTextSprite.LoadTextureFromText(renderer, font, endText);
}
