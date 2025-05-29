#pragma once
#include "raylib.h"
#include "Tile.h"
#include "Mario.h"
#include <vector>
class Map: public DrawableObj {
private:
    int currentMap;
    float width;
    const float height= 900.0f;
    float currBackgroundStarX;
    Texture2D background;
    std::vector<Tile*> interactiveTiles;
    std::vector<Tile*> nonInterativeTile;
    void LoadFromJsonFile(const std::string& filename);
public:
    std::vector<Tile *> &getInteractiveTiles();
    float getMapWidth() const;
    Map();
    ~Map();
    void nextMap();
    void LoadMap(int mapNumber);
    void Draw() override;
};
