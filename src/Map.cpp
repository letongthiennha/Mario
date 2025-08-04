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


 std::vector<std::vector<Tile *>> &Map::getInteractiveTilesSection()
{
    return interactiveTilesSection;
}

std::vector<std::vector<Tile *>> &Map::getNonInteractiveTilesSection()
{
    return nonInteractiveTilesSection;
}

std::vector<std::vector<Block *>> &Map::getBlocksSection()
{
    return blocksSection;
}

std::vector<std::vector<Item *>> &Map::getItemsSection()
{
    return itemsSection;
}

std::vector<std::vector<Monster *>> &Map::getMonstersSection()
{
    return monstersSection;
}

int Map::getSectionWidth() const
{
    return sectionWidth;
}

float Map::getMapWidth() const
{
    return width;
}

Vector2 Map::getStartPositionForPlayer() const
{
    return startPositionForPlayer;
}

Map::Map(int mapNumber) :sectionWidth(GetScreenWidth()/2)
{
    //blocks.push_back(new QuestionBlock({200, 600}, {32, 32}, WHITE, "Mushroom", items));
    //blocks.push_back(new QuestionBlock({168, 600}, {32, 32}, WHITE, "Coin", items));
    currBackgroundStarX = 0.0f;
    background= ResourceManager::getInstance().getTexture("BACKGROUND_"+std::to_string(mapNumber));
    // monsters.push_back( MonsterFactory::createMonster("BanzaiBill", Vector2{1000, 700}, 300));
    // monsters.push_back( MonsterFactory::createMonster("Rex", Vector2{500, 600}, -200));
    LoadMap(mapNumber);
}
    Map::~Map()
{

    for (auto& section : interactiveTilesSection) {
        for (auto& tile : section) {
            delete tile;
            tile = nullptr;
        }
        section.clear();
    }
    interactiveTilesSection.clear();
    for (auto& section : nonInteractiveTilesSection) {
        for (auto& tile : section) {
            delete tile;
            tile = nullptr;
        }
        section.clear();
    }
    nonInteractiveTilesSection.clear();
    for (auto& section : blocksSection) {
        for (auto& block : section) {
            delete block;
            block = nullptr;
        }
        section.clear();
    }   
    blocksSection.clear();
    for (auto& section : itemsSection) {
        for (auto& item : section) {
            delete item;
            item = nullptr;
        }
        section.clear();
    }
    itemsSection.clear();
    for (auto& section : monstersSection) {
        for (auto& monster : section) {
            delete monster;
            monster = nullptr;
        }
        section.clear();
    }   
    monstersSection.clear();

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

    maxSection = getMapWidth() / sectionWidth;
    interactiveTilesSection= std::vector<std::vector<Tile*>>(maxSection+1);
    nonInteractiveTilesSection= std::vector<std::vector<Tile*>>(maxSection+1);
    blocksSection= std::vector<std::vector<Block*>>(maxSection+1);
    itemsSection= std::vector<std::vector<Item*>>(maxSection+1);
    monstersSection= std::vector<std::vector<Monster*>>(maxSection+1);
    //monstersSection[2].push_back(MonsterFactory::createMonster("BanzaiBill", Vector2{1000, 700}, 300));
    //monstersSection[2].push_back(MonsterFactory::createMonster("Rex",   Vector2{500, 600}, -200));
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

    startPositionForPlayer = Vector2{(float)startPosX, (float)startPosY};

   int blockTilesetFirstGid = -1;
    int mainTilesetFirstGid = -1;
    for (const auto& tileset : mapJson["tilesets"]) {
        std::string name = tileset.contains("name") ? tileset["name"].get<std::string>() : "";
        std::string source = tileset.contains("source") ? tileset["source"].get<std::string>() : "";
        if (name == "Blocks" || source.find("Blocks.tsx") != std::string::npos) {
            blockTilesetFirstGid = tileset["firstgid"];
        }
        else if (source.find("Tileset.tsx") != std::string::npos) {
            mainTilesetFirstGid = tileset["firstgid"];
        }
    }

   if (blockTilesetFirstGid == -1) {
        std::cerr << "Block tileset not found!" << std::endl;
    }

    if (mainTilesetFirstGid == -1) {
        std::cerr << "Main tileset not found!" << std::endl;
    }
//Tile
	/*for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int belongSection = (int)(x * 32 / sectionWidth);
            int tileId = data[y * width + x];
            if (tileId == 0)
                continue;
            else if(tileId==1 || (tileId >= 104 && tileId <= 107))
				nonInteractiveTilesSection[belongSection].push_back(new Tile(Vector2{(float) x * 32,(float) y * 32 },mapNumber,tileId-1));
            else interactiveTilesSection[belongSection].push_back(new Tile(Vector2{(float) x * 32,(float) y * 32 },mapNumber,tileId-1));
                }
            }*/
//ITEM
    for (const auto& layer : mapJson["layers"]) {
        if (layer["type"] == "tilelayer" && layer["name"] == "Tile Layer 1") {
            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int belongSection = (int)(x * 32 / sectionWidth);
                    int rawTileId = data[y * width + x];
                    if (rawTileId == 0)
                        continue;

                    int tileId = rawTileId - mainTilesetFirstGid;
                    if (tileId == 0 || (tileId >= 108 && tileId <= 111))
                        nonInteractiveTilesSection[belongSection].push_back(new Tile(Vector2{ (float)x * 32,(float)y * 32 }, mapNumber, tileId));
                    else
                        interactiveTilesSection[belongSection].push_back(new Tile(Vector2{ (float)x * 32,(float)y * 32 }, mapNumber, tileId));
                }
            }
        }
        //Load Coin
        if (layer["type"] == "tilelayer" && layer["name"] == "Coin") {
         
            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int tileId = data[y * width + x];
                    if (tileId == 0) continue; // Skip empty tiles
                    // Create a coin item at the position of the tile
                    int belongSection = (int)(x * 32 / sectionWidth);
                    itemsSection[belongSection].emplace_back(ItemFactory::createItem("Coin", { (float)x * 32, (float)y * 32 }, DIRECTION_RIGHT));
                }
            }
        }
        //Ending block
        if (layer["type"] == "tilelayer" && layer["name"] == "ClearCourseToken") {

            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int tileId = data[y * width + x];
                    if (tileId == 0) continue; // Skip empty tiles
                    // Create a ClearToken item at the position of the tile
                    int belongSection = (int)(x * 32 / sectionWidth);
                    itemsSection[belongSection].emplace_back(ItemFactory::createItem("ClearToken", { (float)x * 32, (float)y * 32 }, DIRECTION_RIGHT));
                }
            }
        }
        //Monster
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
                    int belongSection = (int)(x / sectionWidth);
                    monstersSection[belongSection].push_back(monster);
                    monster->setIsActive(false);
                } else {
                    std::cerr << "Unknown monster type: " << type << std::endl;
                }
            }
        }
        //Load Blocks
        if (layer["type"] == "tilelayer" && layer["name"] == "Block") {
            std::vector<int> data = layer["data"];
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                        int rawId = data[y * width + x];
                        int tileId = rawId - blockTilesetFirstGid;
                        if (rawId == 0) continue;
                        int belongSection = (int)(x * 32 / sectionWidth);
                        Block* block = BlockFactory::createBlockFromId(tileId, { (float)x * 32, (float)y * 32 }, itemsSection[belongSection]);
                        if (block) {
                            int belongSection = (int)(x * 32 / sectionWidth);
                            blocksSection[belongSection].push_back(block);
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
                    int belongSection = (int)(x / sectionWidth);
                    Block* block = BlockFactory::createBlock("QuestionBlock", { x, y - 32 }, itemsSection[belongSection], itemType);
                    if (block)
                    {
                        int belongSection = (int)(x / sectionWidth);
                        blocksSection[belongSection].push_back(block);
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
}
