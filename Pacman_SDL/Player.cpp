#include "Player.h"

//const std::string Player::spritePath = "./Assets/pacman-art/pacman-right/1.png";

void Player::LoadMedia(SDL_Renderer* renderer)
{
	sprite.LoadTexture(renderer, spritePath);
}

void Player::Start()
{

}

void Player::HandleEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_UP:
		movement.y = -speed;
		movement.x = 0;
		break;

	case SDLK_DOWN:
		movement.y = speed;
		movement.x = 0;
		break;

	case SDLK_LEFT:
		movement.x = -speed;
		movement.y = 0;
		break;

	case SDLK_RIGHT:
		movement.x = speed;
		movement.y = 0;
		break;

	default:
		break;
	}
}

void Player::Update()
{
	Move(movement);
}

void Player::Render(SDL_Renderer* renderer)
{
	sprite.RenderTexture(renderer, &transform);
}

SDL_Rect Player::getTransform()
{
	return transform;
}

void Player::setTransform(SDL_Rect transform)
{
	this->transform = transform;
}

void Player::Move(Vector2 movement)
{
	transform.x += movement.x;
	transform.y += movement.y;
}