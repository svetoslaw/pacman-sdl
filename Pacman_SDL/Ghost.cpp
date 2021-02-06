#include "Ghost.h"

void Ghost::LoadMedia(SDL_Renderer* renderer)
{
	mainSprite.LoadTexture(renderer, mainSpritePath);
	scatterSprite.LoadTexture(renderer, scatterSpritePath);
}

void Ghost::Render(SDL_Renderer* renderer)
{
	currentSprite->RenderTexture(renderer, &transform);
}

void Ghost::Start()
{
	currentSprite = &mainSprite;
}

std::string Ghost::getTag()
{
	return tag;
}

SDL_FRect Ghost::getTransform()
{
	return transform;
}

void Ghost::setTransform(SDL_FRect transform)
{
	this->transform = transform;
}

void Ghost::setTileGraph(const std::shared_ptr<TileGraph> &tileGraph)
{
	this->tileGraph = tileGraph;
}

GhostState Ghost::getState()
{
	return state;
}

void Ghost::SetToScatterState()
{
	scatterDuration_p = 0;
	if (state != GhostState::SCATTERING)
	{
		state = GhostState::SCATTERING;
		switch (chosenDirection)
		{
		case MoveDirection::UP:
			chosenDirection = MoveDirection::DOWN;
			break;
		case MoveDirection::DOWN:
			chosenDirection = MoveDirection::UP;
			break;
		case MoveDirection::LEFT:
			chosenDirection = MoveDirection::RIGHT;
			break;
		case MoveDirection::RIGHT:
			chosenDirection = MoveDirection::LEFT;
			break;
		case MoveDirection::NONE:
			break;
		default:
			break;
		}

		travelSpaces = TILE_SIZE - travelSpaces;

		currentSprite = &scatterSprite;
	}
}

void Ghost::HandleEvent(SDL_Event& event)
{

}

void Ghost::Update(float deltaTime)
{
	AI_Random(deltaTime);
}

void Ghost::OnCollision(GameObject* other, float deltaTime)
{
	if (other->getTag() == "Player")
	{
		if (state == GhostState::SCATTERING)
			Destroy();
	}
}

void Ghost::Move(float deltaTime)
{
	movementStack += speed * deltaTime;

	while (travelSpaces > 0 && movementStack >= 1)
	{
		switch (chosenDirection)
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

		travelSpaces -= 1;
		movementStack -= 1.f;
	}
}

void Ghost::AI_Random(float deltaTime)
{
	switch (state)
	{
	case GhostState::SPAWNING:
		if (spawnDelay_p < spawnDelay)
			spawnDelay_p += deltaTime;
		else
		{
			chosenDirection = MoveDirection::UP;
			Move(deltaTime);

			if (travelSpaces == 0)
			{
				spawnTileMoves--;
				travelSpaces = TILE_SIZE;
				if (spawnTileMoves == 0)
					state = GhostState::CHASING;
			}
		}
		break;
	case GhostState::CHASING:
		if (travelSpaces == 0)
		{
			AI_Random_ChooseDirection();
			travelSpaces += TILE_SIZE;
		}
		Move(deltaTime);

		break;
	case GhostState::SCATTERING:
		scatterDuration_p += deltaTime;
		if (scatterDuration_p >= scatterDuration)
		{
			state = GhostState::CHASING;
			currentSprite = &mainSprite;
		}

		if (travelSpaces == 0)
		{
			AI_Random_ChooseDirection();
			travelSpaces += TILE_SIZE;
		}
		Move(deltaTime);
		break;
	case GhostState::RETURNING:
		break;
	default:
		break;
	}
}

void Ghost::AI_Random_ChooseDirection()
{
	Tile* tile;

	tile = tileGraph.lock()->GetTileAt(Vector2(transform.x, transform.y - 1));
	if (chosenDirection != MoveDirection::DOWN && tile->isPassable())
		possibleDirections.push_back(MoveDirection::UP);

	tile = tileGraph.lock()->GetTileAt(Vector2(transform.x, transform.y + TILE_SIZE));
	if (chosenDirection != MoveDirection::UP && tile->isPassable())
		possibleDirections.push_back(MoveDirection::DOWN);

	tile = tileGraph.lock()->GetTileAt(Vector2(transform.x - 1, transform.y));
	if (chosenDirection != MoveDirection::RIGHT && tile->isPassable())
		possibleDirections.push_back(MoveDirection::LEFT);

	tile = tileGraph.lock()->GetTileAt(Vector2(transform.x + TILE_SIZE, transform.y));
	if (chosenDirection != MoveDirection::LEFT && tile->isPassable())
		possibleDirections.push_back(MoveDirection::RIGHT);

	if (possibleDirections.size() == 0)
	{
		switch (chosenDirection)
		{
		case MoveDirection::UP:
			chosenDirection = MoveDirection::DOWN;
			break;
		case MoveDirection::DOWN:
			chosenDirection = MoveDirection::UP;
			break;
		case MoveDirection::LEFT:
			chosenDirection = MoveDirection::RIGHT;
			break;
		case MoveDirection::RIGHT:
			chosenDirection = MoveDirection::LEFT;
			break;
		case MoveDirection::NONE:
			break;
		default:
			break;
		}
	}
	else
	{
		int selectedDirectionIndex = rand() % possibleDirections.size();
		chosenDirection = possibleDirections[selectedDirectionIndex];
	}
	
	possibleDirections.clear();
}
