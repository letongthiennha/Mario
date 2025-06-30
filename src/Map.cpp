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

std::vector<Item*>& Map::getItems() {
    return items;
}

float Map::getMapWidth() const
{
    return width;
}

Map::Map()

    
{
    currBackgroundStarX = 0.0f;
    background= ResourceManager::getInstance().getTexture("BACKGROUND_0");
}
Map::~Map()
{
    for(auto& tile : interactiveTiles)
    {
            delete tile;
            tile = nullptr;
    }
    interactiveTiles.clear();
    for (auto& item : items) {
        delete item;
        item = nullptr;
    }
    items.clear();
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

    for (const auto& layer : mapJson["layers"]) {
        if (layer["type"] == "objectgroup" && layer["name"] == "Coin") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                // Create a Coin at (x, y)
                items.emplace_back(new Coin({ x, y }, { 32, 32 }, WHITE, 0.1f, 4, IDLE));
            }
        }
        if (layer["type"] == "objectgroup" && layer["name"] == "Mushroom") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                // You can customize direction or other params as needed
                items.emplace_back(new Mushroom({ x, y }, { 32, 32 }, WHITE, 0.1f, 4, DIRECTION_RIGHT));
            }
        }
        if (layer["type"] == "objectgroup" && layer["name"] == "UpMushroom") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                // You can customize direction or other params as needed
                items.emplace_back(new UpMushroom({ x, y }, { 32, 32 }, WHITE, 0.1f, 4, DIRECTION_RIGHT));
            }
        }
        if (layer["type"] == "objectgroup" && layer["name"] == "FireFlower") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                // You can customize direction or other params as needed
                items.emplace_back(new FireFlower({ x, y }, { 32, 32 }, WHITE, 0.1f, 2));
            }
        }
        if (layer["type"] == "objectgroup" && layer["name"] == "Star") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                // You can customize direction or other params as needed
                items.emplace_back(new Star({ x, y }, { 32, 32 }, WHITE, 0.1f, 2, DIRECTION_RIGHT));
            }
        }
        if (layer["type"] == "objectgroup" && layer["name"] == "UpMoon") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                // You can customize direction or other params as needed
                items.emplace_back(new UpMoon({ x, y }, { 32, 32 }, WHITE, 0.1f, 2, DIRECTION_RIGHT));
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
    for (const auto& item : items) {
        item->Draw();
    }

}
