#include "Ghost.h"

void Ghost::LoadMedia(SDL_Renderer* renderer)
{
	mainSprite.LoadTexture(renderer, mainSpritePath);
	scatterSprite.LoadTexture(renderer, scatterSpritePath);
	returnSprite.LoadTexture(renderer, returnSpritePath);
}

void Ghost::Render(SDL_Renderer* renderer)
{
	currentSprite->RenderTexture(renderer, &transform);
}

void Ghost::Start()
{
	currentSprite = &mainSprite;
	spawnPosition = Vector2(transform.x, transform.y);
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

void Ghost::SetToChasingState()
{
	state = GhostState::CHASING;
	currentSprite = &mainSprite;
	movementStack = 0;

	speed += pillSpeedChange;
}

void Ghost::SetToScatterState()
{
	scatterDuration_p = 0;
	if (state == GhostState::CHASING)
	{
		movementStack = 0;

		speed -= pillSpeedChange;
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

void Ghost::SetToReturningState()
{
	state = GhostState::RETURNING;
	movementStack = 0;

	currentSprite = &returnSprite;

	auto tg = tileGraph.lock();
	Tile* currentTile = tg->GetTileAt(Vector2(transform.x, transform.y));
	pathToSpawn = tg->FindPath(currentTile, tg->GetTileAt(spawnPosition));

	if (travelSpaces != 0) //hack to set the ideal centered position of the ghost to the tile
	{
		transform.x = currentTile->getPosition().x;
		transform.y = currentTile->getPosition().y;

		travelSpaces = 0;
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
			SetToReturningState();
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

void Ghost::MoveToSpawn(float deltaTime)
{
	movementStack += (speed * deltaTime) * 0.75;
	while (movementStack >= 1)
	{
		if (transform.x > spawnPosition.x)
			transform.x -= 1;
		else if (transform.x < spawnPosition.x)
			transform.x += 1;

		if (transform.y > spawnPosition.y)
			transform.y -= 1;
		else if (transform.y < spawnPosition.y)
			transform.y += 1;

		movementStack -= 1;
	}
}

void Ghost::MoveToSpawn2(float deltaTime)
{
	if (pathToSpawn.empty())
		SetToChasingState();
	if (travelSpaces == 0)
	{
		chosenDirection = pathToSpawn.front();
		pathToSpawn.pop_front();
		travelSpaces = TILE_SIZE;
	}

	Move(deltaTime);
}

void Ghost::AI_Random(float deltaTime)
{
	switch (state)
	{
	
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
			SetToChasingState();

		if (travelSpaces == 0)
		{
			AI_Random_ChooseDirection();
			travelSpaces += TILE_SIZE;
		}
		Move(deltaTime);
		break;
	case GhostState::RETURNING:
		MoveToSpawn2(deltaTime);
		break;
	/*Not used currently*/
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
					SetToChasingState();
			}
		}
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