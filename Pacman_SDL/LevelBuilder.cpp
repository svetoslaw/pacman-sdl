#include "LevelBuilder.h"

bool LevelBuilder::BuildLevelFromFile(App& app, std::string filePath)
{
    bool successFlag = true;

    fileStream.open(filePath);
    if (!fileStream)
    {
        printf("Unable to open level file: %s", filePath.c_str());
        successFlag = false;
    }
    else
    {
        /*Don't use hardcoded value*/
        tileGraph = std::make_shared<TileGraph>(23 * TILE_SIZE, 23 * TILE_SIZE);

        CountGameObjectsNeeded();

        CreateGameObjects();

        SetupLevel(app);
    }

    fileStream.close();
    return successFlag;
}

void LevelBuilder::CountGameObjectsNeeded()
{
    char c;

    while (fileStream.get(c))
    {
        switch (c)
        {
        case 'w':
            wallsCount++;
            break;
        case '.':
            pointsCount++;
            break;
        case 'c':
            playersCount++;
            break;
        case 'g':
            ghostsCount++;
            break;
        case 'p':
            pillsCount++;
            break;
        default:
            break;
        }
    }

    fileStream.clear();
    fileStream.seekg(0);
}

void LevelBuilder::CreateGameObjects()
{
    ui = std::make_shared<UI>();

    for (int i = 0; i < playersCount; i++)
        players.push_back(std::make_shared<Player>());

    for (int i = 0; i < wallsCount; i++)
        walls.push_back(std::make_shared<Wall>());
    
    for (int i = 0; i < pointsCount; i++)
        points.push_back(std::make_shared<Point>());

    for (int i = 0; i < ghostsCount; i++)
        ghosts.push_back(std::make_shared<Ghost>());

    for (int i = 0; i < pillsCount; i++)
        pills.push_back(std::make_shared<Pill>());
}

void LevelBuilder::SetupLevel(App& app)
{
    char c;

    int currentPlayer = 0;
    int currentWall = 0;
    int currentPoint = 0;
    int currentGhost = 0;
    int currentPill = 0;

    app.AddGameObject(ui);

    while (fileStream.get(c))
    {
        switch (c)
        {
        case 'w':
            walls[currentWall]->setTransform(rect);
            app.AddGameObject(walls[currentWall]);
            currentWall++;

            tileGraph->GetTileAt(Vector2(rect.x, rect.y))->setIsPassable(false);

            rect.x += TILE_SIZE;
            break;
        case '.':
            points[currentPoint]->setTransform(rect);
            app.AddGameObject(points[currentPoint]);
            currentPoint++;

            rect.x += TILE_SIZE;
            break;
        case 'c':
            players[currentPlayer]->setTransform(rect);
            players[currentPlayer]->setTileGraph(tileGraph);
            for (int i = 0; i < ghostsCount; i++)
                players[currentPlayer]->AddGhost(ghosts[i]);
            players[currentPlayer]->AddUI(ui);
            players[currentPlayer]->SetNumberOfPoints(pointsCount);
            app.AddGameObject(players[currentPlayer]);
            currentPlayer++;

            rect.x += TILE_SIZE;
            break;
        case 'g':
            ghosts[currentGhost]->setTransform(rect);
            ghosts[currentGhost]->setTileGraph(tileGraph);
            app.AddGameObject(ghosts[currentGhost]);
            currentGhost++;

            rect.x += TILE_SIZE;
            break;
        case 'p':
            pills[currentPill]->setTransform(rect);
            app.AddGameObject(pills[currentPill]);
            currentPill++;

            rect.x += TILE_SIZE;
            break;
        case ' ':
            rect.x += TILE_SIZE;
            break;
            
        case '\n':
            rect.x = 0;
            rect.y += TILE_SIZE;
            break;
        default:
            rect.x += TILE_SIZE;
            break;
        }
    }
}

void LevelBuilder::BuildUI(App &app)
{

}
