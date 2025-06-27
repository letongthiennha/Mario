#include "Map.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
void Map::LoadFromJsonFile(const std::string& mapFileName)
{
	
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

Map::Map(int mapNumber)
{
    currBackgroundStarX = 0.0f;
    background= ResourceManager::getInstance().getTexture("BACKGROUND_"+std::to_string(mapNumber));
    LoadMap(mapNumber);
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
    std::string mapFileName = "resources/Map/Map" +std::to_string(mapNumber) + ".json";
    std::ifstream file(mapFileName);
	if (!file) {
		std::cerr << "Could not open json file " << mapFileName << std::endl;
		return;
	}
	nlohmann::json mapJson;
	file >> mapJson;

	int width = mapJson["width"];
	int height = mapJson["height"];
	this->width = (float) width * 32.0f;
	int tilewidth = mapJson["tilewidth"];
	std::vector<int> data = mapJson["layers"][0]["data"];

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int tileId = data[y * width + x];
			if (tileId == 0)
                continue;
            else if(tileId==1)
				nonInterativeTile.push_back(new Tile(Vector2{(float) x * 32,(float) y * 32 },mapNumber,tileId-1));
            else interactiveTiles.push_back(new Tile(Vector2{(float) x * 32,(float) y * 32 },mapNumber,tileId-1));
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

}
