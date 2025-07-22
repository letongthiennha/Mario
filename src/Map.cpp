#include "Map.h"
#include "json.hpp"
#include "ItemFactory.h"
#include "MonsterFactory.h"
#include "QuestionBlock.h"
#include "BlockFactory.h"
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

std::vector<Monster *> &Map::getMonsters()
{
    return monsters;
}

std::vector<Block *> &Map::getBlocks()
{
    return blocks;
}

float Map::getMapWidth() const
{
    return width;
}

Vector2 Map::getStartPositionForMario() const
{
    return startPositionForMario;
}

Map::Map(int mapNumber)
{
    //blocks.push_back(new QuestionBlock({200, 600}, {32, 32}, WHITE, "Mushroom", items));
    //blocks.push_back(new QuestionBlock({168, 600}, {32, 32}, WHITE, "Coin", items));
    currBackgroundStarX = 0.0f;
    background= ResourceManager::getInstance().getTexture("BACKGROUND_"+std::to_string(mapNumber));
    monsters.push_back( MonsterFactory::createMonster("BanzaiBill", Vector2{1000, 700}, 300));
    monsters.push_back(MonsterFactory::createMonster("Rex", Vector2{800, 700}, -100)); // Rex

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
    for (auto& item : items) {
        delete item;
        item = nullptr;
    }
    items.clear();
    for (auto& tile : nonInterativeTile)
    {
        delete tile;
        tile = nullptr;
    }
    nonInterativeTile.clear();
    for (auto& monster : monsters) {
        delete monster;
        monster = nullptr;
    }
    monsters.clear();
    for (auto& block : blocks) {
        delete block;
        block = nullptr;
    }
    blocks.clear();
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

    int startPosX = 0; // Default value in case it's not found
    int startPosY = 0; // Default value in case it's not found
        for (const auto& prop : mapJson["properties"]) {
            // Check if the name is "startPosX"
            if (prop["name"] == "startPosX") {
                // Get the value
                    startPosX = prop["value"];
            }
            // Check if the name is "startPosY"
            if (prop["name"] == "startPosY")
            {
                // Get the value
                    startPosY = prop["value"];
            }
        }

    startPositionForMario = Vector2{(float)startPosX, (float)startPosY};

    int blockTilesetFirstGid = -1;
    for (const auto& tileset : mapJson["tilesets"]) {
        std::string name = tileset.contains("name") ? tileset["name"].get<std::string>() : "";
        std::string source = tileset.contains("source") ? tileset["source"].get<std::string>() : "";
        if (name == "Blocks" || source.find("Blocks.tsx") != std::string::npos) {
            blockTilesetFirstGid = tileset["firstgid"];
            break;
        }
    }

    if (blockTilesetFirstGid == -1) {
        std::cerr << "Block tileset not found!" << std::endl;
    }

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int tileId = data[y * width + x];
			if (tileId == 0)
                continue;
            else if(tileId==1 || (tileId >= 108 && tileId <= 111))
				nonInterativeTile.push_back(new Tile(Vector2{(float) x * 32,(float) y * 32 },mapNumber,tileId-1));
            else interactiveTiles.push_back(new Tile(Vector2{(float) x * 32,(float) y * 32 },mapNumber,tileId-1));
                }
            }

    for (const auto& layer : mapJson["layers"]) {
        if (layer["type"] == "tilelayer" && layer["name"] == "Coin") {
         
            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int tileId = data[y * width + x];
                    if (tileId == 0) continue; // Skip empty tiles
                    // Create a coin item at the position of the tile
                    items.emplace_back(ItemFactory::createItem("Coin", { (float)x * 32, (float)y * 32 }, DIRECTION_RIGHT));
                }
            }
        }
        if (layer["type"] == "tilelayer" && layer["name"] == "ClearCourseToken") {

            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int tileId = data[y * width + x];
                    if (tileId == 0) continue; // Skip empty tiles
                    // Create a ClearToken item at the position of the tile
                    items.emplace_back(ItemFactory::createItem("ClearToken", { (float)x * 32, (float)y * 32 }, DIRECTION_RIGHT));
                }
            }
        }

        if (layer["type"] == "objectgroup" && layer["name"] == "Monsters") {
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                //std::cout << "Monster object: " << obj.dump() << std::endl;
                std::string type = obj["type"];
                //if (type.empty()) continue;
                float speed = 100.0f; // Default speed
                if (obj.contains("speed")) {
                 speed = obj["speed"];
                }
                Monster* monster = MonsterFactory::createMonster(type, {x, y}, speed);
                if(monster) {
                    monsters.push_back(monster);
                    monster->setIsActive(false);
                } else {
                    std::cerr << "Unknown monster type: " << type << std::endl;
                }
            }
        }

        if(layer["type"]=="tilelayer" && layer["name"] == "Block") {
            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                        int rawId = data[y * width + x];
                        int tileId = rawId - blockTilesetFirstGid;
                        if (rawId == 0) continue;
                        Block* block = BlockFactory::createBlockFromId(tileId, { (float)x * 32, (float)y * 32 }, items);
                        if (block) {
                            blocks.push_back(block);
                        } else {
                            std::cerr << "Unknown block ID: " << tileId << std::endl;
                        }
                        
                    }
                }
            }
        if(layer["type"]=="objectgroup"&&layer["name"]=="QuestionBlock"){
            for (const auto& obj : layer["objects"]) {
                float x = obj["x"];
                float y = obj["y"];
                if (obj.contains("properties") && !obj["properties"].empty()) {
                    // Assuming the first property is the item type

                    std::string itemType = obj["properties"][0]["value"];
                    Block* block = BlockFactory::createBlock("QuestionBlock", { x, y - 32 }, items, itemType);
                    if (block)
                    {
                        blocks.push_back(block);
                    }
                    else
                    {
                        std::cerr << "Unknown block type: " << itemType << std::endl;
                    }
                }
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
    for (const auto& monster : monsters) {
        monster->Draw();
    }
    for (const auto& block : blocks) {
        block->Draw();
    }
}
