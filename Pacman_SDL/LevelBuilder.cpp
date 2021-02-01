#include "LevelBuilder.h"

bool LevelBuilder::BuildLevelFromFile(App& app, std::string filePath)
{
    bool successFlag = true;

    std::ifstream fileStream;
    fileStream.open(filePath);
    if (!fileStream)
    {
        printf("Unable to open level file: %s", filePath.c_str());
        successFlag = false;
    }
    else
    {
        Player* player;
        Wall* wall;
        Point* point;

        SDL_FRect rect = { 0, 0, TILE_SIZE, TILE_SIZE };
        
        char c;
        while (fileStream.get(c))
        {
            printf("%c", c);
            switch (c)
            {
            case 'w':
                wall = new Wall();
                wall->setTransform(rect);
                app.AddGameObject(wall);
                rect.x += TILE_SIZE;
                break;
            case '.':
                point = new Point();
                point->setTransform(rect);
                app.AddGameObject(point);
                rect.x += TILE_SIZE;
                break;
            case 'p':
                player = new Player();
                player->setTransform(rect);
                app.AddGameObject(player);
                rect.x += TILE_SIZE;
                break;
            case '\n':
                rect.x = 0;
                rect.y += TILE_SIZE;
                break;
            default:
                break;
            }
        }
    }

    return successFlag;
}
