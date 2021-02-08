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

void Player::AddGhost(const std::shared_ptr<Ghost>& ghost)
{
	std::weak_ptr<Ghost> ghostWP = ghost;
	this->ghosts.push_back(ghost);
}

void Player::AddUI(const std::shared_ptr<UI>& ui)
{
	this->ui = ui;
}

void Player::SetNumberOfPoints(int number)
{
	numberOfPoints = number;
}

void Player::Move(float deltaTime)
{
	movementStack += speed * deltaTime;

	while (movementStack >= 1.f)
	{
		if (NextTileIsPassable2())
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
	if (numberOfPoints <= 0)
		Win();


	Move(deltaTime);
}

void Player::OnCollision(GameObject* other, float deltaTime)
{
	if (other->getTag() == "Wall")
	{
		/*Make sure to stop at wall*/
		/*Revert intersection*/
		if (nextMove == MoveDirection::RIGHT)
		{
			transform.x = other->getTransform().x - TILE_SIZE;
		}
		if (nextMove == MoveDirection::LEFT)
		{
			transform.x = other->getTransform().x + TILE_SIZE;
		}
		if (nextMove == MoveDirection::DOWN)
		{
			transform.y = other->getTransform().y - TILE_SIZE;
		}
		if (nextMove == MoveDirection::UP)
		{
			transform.y = other->getTransform().y + TILE_SIZE;
		}
	}

	if (other->getTag() == "Point")
	{
		score += 100;
		ui.lock()->SetScoreText(score);
		numberOfPoints--;
	}

	if (other->getTag() == "Ghost")
	{
		auto g = static_cast<Ghost*>(other);
		if (g->getState() == GhostState::CHASING)
		{
			ui.lock()->SetEndText("Defeat");
			Destroy();
		}
		if (g->getState() == GhostState::SCATTERING)
			score += 300;
	}

	if (other->getTag() == "Pill")
	{
		for (auto& ghost : ghosts)
			ghost.lock()->SetToScatterState();

		ui.lock()->ActivatePowerBar();
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

void Player::setTileGraph(const std::shared_ptr<TileGraph> &tileGraph)
{
	this->tileGraph = tileGraph;
}

bool Player::NextTileIsPassable2()
{
	Tile* tile1 = NULL;
	Tile* tile2 = NULL;

	auto tg = tileGraph.lock();

	switch (tryMove)
	{
	case MoveDirection::UP:
		tile1 = tg->GetTileAt(Vector2(transform.x, transform.y - 1));
		tile2 = tg->GetTileAt(Vector2(transform.x + transform.w-1, transform.y - 1));
		break;
	case MoveDirection::DOWN:
		tile1 = tg->GetTileAt(Vector2(transform.x, transform.y + transform.h));
		tile2 = tg->GetTileAt(Vector2(transform.x + transform.w-1, transform.y + transform.h));
		break;
	case MoveDirection::LEFT:
		tile1 = tg->GetTileAt(Vector2(transform.x - 1, transform.y));
		tile2 = tg->GetTileAt(Vector2(transform.x - 1, transform.y + transform.h-1));
		break;
	case MoveDirection::RIGHT:
		tile1 = tg->GetTileAt(Vector2(transform.x + transform.w, transform.y));
		tile2 = tg->GetTileAt(Vector2(transform.x + transform.w, transform.y + transform.h-1));
		break;
	case MoveDirection::NONE:
		break;
	default:
		break;
	}

	if (tile1 == NULL || tile2 == NULL)
		return false;
	else
		return (tile1->isPassable() && tile2->isPassable());
}

void Player::Win()
{
	for (auto& ghost : ghosts)
		ghost.lock()->Destroy();

	ui.lock()->SetEndText("Victory");
}
