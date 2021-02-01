#include "Player.h"

void Player::LoadMedia(SDL_Renderer* renderer)
{
	sprite.LoadTexture(renderer, spritePath);
}

void Player::Render(SDL_Renderer* renderer)
{
	sprite.RenderTexture(renderer, &transform);
}

std::string Player::getTag()
{
	return tag;
}

void Player::Start()
{

}

void Player::HandleEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_UP: case SDLK_w:
		movementVelocity.y = -speed;
		movementVelocity.x = 0;
		break;

	case SDLK_DOWN: case SDLK_s:
		movementVelocity.y = speed;
		movementVelocity.x = 0;
		break;

	case SDLK_LEFT: case SDLK_a:
		movementVelocity.x = -speed;
		movementVelocity.y = 0;
		break;

	case SDLK_RIGHT: case SDLK_d:
		movementVelocity.x = speed;
		movementVelocity.y = 0;
		break;

	default:
		break;
	}
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);
	//printf("Score: %i\n", score);
}

bool Player::CheckForCollision(const SDL_FRect& other)
{
	if (other.x > transform.x + transform.w)
		return false;

	if (other.y > transform.y + transform.h)
		return false;

	if (other.x + other.w < transform.x)
		return false;

	if (other.y + other.h < transform.y)
		return false;

	return true;
}

void Player::OnCollision(GameObject& other, float deltaTime)
{
	if (other.getTag() == "Wall")
	{
		transform.x -= movementVelocity.x * deltaTime;
		transform.y -= movementVelocity.y * deltaTime;

		movementVelocity.x = 0;
		movementVelocity.y = 0;
	}

	if (other.getTag() == "Point")
	{
		score += 100;
	}

}

SDL_FRect Player::getTransform()
{
	return transform;
}

void Player::setTransform(SDL_FRect transform)
{
	this->transform = transform;
}

void Player::Move(float deltaTime)
{
	transform.x += movementVelocity.x * deltaTime;
	transform.y += movementVelocity.y * deltaTime;
}

bool Player::CheckForWall()
{
	return false;
}
