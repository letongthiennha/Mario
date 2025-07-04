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
    
    Vector2 startPositionForMario;

    float currBackgroundStarX;
    Texture2D background;

    std::vector<Tile*> interactiveTiles;
    std::vector<Tile*> nonInterativeTile;

    void LoadFromJsonFile(const std::string& filename);
    void LoadMap(int mapNumber);    
public:
    std::vector<Tile *> &getInteractiveTiles();
    float getMapWidth() const;

    Vector2 getStartPositionForMario() const;

    Map(int mapNumber);  
    ~Map();
    void Draw() override;
};
