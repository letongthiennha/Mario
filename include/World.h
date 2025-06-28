#include "raylib.h"
#include "GameClock.h"
#include "Tile.h"
#include <vector>
#include "Mario.h"
#include"Map.h"    
#include "Coin.h"
#include "CollisionMediator.h"

class World
{   
private:
    static  constexpr float GRAVITY=1800;
    float currBackgroundStarX=0.0f;
    Texture2D background= ResourceManager::getInstance().getTexture("BACKGROUND_0");
    Map map;
    CollisionMediator collisionMediator;
    Mario player;
    std::vector<Tile *> &interactiveTiles;
    Camera2D camera;
    std::vector<Item*> items;
public:
    World();
    ~World();
    void UpdateWorld();
    void DrawWorld();
    static const float GetGravity();
    static void InitWorld();

    void loadCoins();
};