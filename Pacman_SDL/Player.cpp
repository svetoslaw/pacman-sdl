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
		tryMove = MoveDirection::UP;
		break;

	case SDLK_DOWN: case SDLK_s:
		tryMove = MoveDirection::DOWN;
		break;

	case SDLK_LEFT: case SDLK_a:
		tryMove = MoveDirection::LEFT;
		break;

	case SDLK_RIGHT: case SDLK_d:
		tryMove = MoveDirection::RIGHT;
		break;

	default:
		break;
	}
}

void Player::Move(float deltaTime)
{
	/*if (nextMove != prevMove || nextMove != MoveDirection::NONE)
	{
		movementStack = 0;
	}*/
	movementStack += speed * deltaTime;

	while (movementStack >= 1.f)
	{
		if (NextTileIsPassable())
			nextMove = tryMove;

		switch (nextMove)
		{
		case MoveDirection::UP:
			transform.y -= 1.f;
			break;
		case MoveDirection::DOWN:
			transform.y += 1.f;
			break;
		case MoveDirection::LEFT:
			transform.x -= 1.f;
			break;
		case MoveDirection::RIGHT:
			transform.x += 1.f;
			break;
		case MoveDirection::NONE:
			break;
		default:
			break;
		}

		movementStack -= 1.f;
	}
}

void Player::Update(float deltaTime)
{
	Move(deltaTime);

	//printf("Score: %i\n", score);
}

void Player::OnCollision(GameObject& other, float deltaTime)
{
	if (other.getTag() == "Wall")
	{
		/*Make sure to stop at wall*/
		/*Revert intersection*/
		if (nextMove == MoveDirection::RIGHT)
		{
			transform.x = other.getTransform().x - TILE_SIZE;
		}
		if (nextMove == MoveDirection::LEFT)
		{
			transform.x = other.getTransform().x + TILE_SIZE;
		}
		if (nextMove == MoveDirection::DOWN)
		{
			transform.y = other.getTransform().y - TILE_SIZE;
		}
		if (nextMove == MoveDirection::UP)
		{
			transform.y = other.getTransform().y + TILE_SIZE;
		}
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

void Player::setTileGraph(TileGraph* tileGraph)
{
	this->tileGraph = tileGraph;
}

bool Player::NextTileIsPassable()
{
	Tile* tile;
	int dx = 0;
	int dy = 0;

	switch (tryMove)
	{
	case MoveDirection::UP:
		dy = -1;
		break;
	case MoveDirection::DOWN:
		dy = TILE_SIZE +1;
		break;
	case MoveDirection::LEFT:
		dx = -1;
		break;
	case MoveDirection::RIGHT:
		dx = TILE_SIZE +1;
		break;
	case MoveDirection::NONE:
		break;
	default:
		break;
	}
	
	switch (nextMove)
	{
	case MoveDirection::UP:
		dy += TILE_SIZE - 1;
		break;
	case MoveDirection::DOWN:
		break;
	case MoveDirection::LEFT:
		dx += TILE_SIZE - 1;
		break;
	case MoveDirection::RIGHT:
		break;
	case MoveDirection::NONE:
		break;
	default:
		break;
	}
	
	tile = tileGraph->GetTileAt(Vector2(this->transform.x + dx, this->transform.y + dy));

	if (tile == NULL)
		return false;
	else
		return tile->isPassable();
}
