#include "Map.h"
Mario &Map::getPlayer()
{
    // TODO: insert return statement here
    return player;
}

std::vector<Tile *> &Map::getInteractiveTiles()
{
    // TODO: insert return statement here
    return interactiveTiles;
}

float Map::getMapWidth() const
{
    return width;
}

Map::Map()

    : player()
{
    currBackgroundStarX = 0.0f;
    background= ResourceManager::getTexture("BACKGROUND_0");
}
Map::~Map()
{
    for(auto& tile : interactiveTiles)
    {
            delete tile;
            tile = nullptr;
    }
    interactiveTiles.clear();
}

void Map::LoadMap(int mapNumber)
{
    char* map = nullptr;
    std::string mapFileName = "resources/Map/map" +std::to_string(mapNumber) + ".txt";
    map=LoadFileText(mapFileName.c_str());
    char*orignalMap = map;
    std::vector<std::string> MapDraw;

    while(*map != '\0'){
        while(*map!='>')
            map++;
        map++;
        map++;
        while(*map!='<'){
            std::string currLine;
            while(*map!='\n'){
                currLine += *map;
                map++;
            }
            map++;
            MapDraw.push_back(currLine);
        }
        map++;
    }
    UnloadFileText(orignalMap);
    width = ((float)MapDraw[0].size()-2) * 32.0f;
    map = nullptr;
    for (int i = 0;i<MapDraw.size();i++)
    {
        for (int j = 0;j<MapDraw[i].size();j++)
        {
            char key = MapDraw[i][j];
            if(key=='/')
            {
                interactiveTiles.push_back(new Tile(Vector2{(float)(j-1)*32, (float)(i-1)*32}, mapNumber, '/'));
            }
            else
            if(key=='A')
            {
                nonInterativeTile.push_back(new Tile(Vector2{(float)(j-1)*32, (float)(i-1)*32}, mapNumber, key));
            }
            else if(key!=' ')
            {
                interactiveTiles.push_back(new Tile(Vector2{(float)(j-1)*32, (float)(i-1)*32}, mapNumber, key));
            }
        }
    }
}

void Map::Draw() 
{

    for (const auto& tile : interactiveTiles)
    {
        tile->Draw();
    }
    for (const auto& tile : nonInterativeTile)
    {
        tile->Draw();
    }

    player.Draw();
}
