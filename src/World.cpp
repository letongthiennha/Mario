#include "../include/World.h"
#include "../include/ResourceManager.h"
#include "../include/Monster.h"
#include "../include/Fireball.h"

float World::GRAVITY = 0.0f;

static World* instance = nullptr;

World* World::getInstance() {
    if (instance == nullptr) {
        instance = new World();
    }
    return instance;
}

World::World() : player() {
    instance = this;

    // Ground layer: make it longer
    int groundStart = -20;
    int groundEnd = 40; // Increased from 10 to 40 for a longer ground

    interactiveTiles.push_back(new Tile(Vector2{(float)groundStart * 32, 700}, TileType::TILE_TYPE_RIGHT_EDGE, "MAP1_GRASS"));
    for (int i = groundStart + 1; i < groundEnd; i++) {
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 700}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    }
    interactiveTiles.push_back(new Tile(Vector2{(float)groundEnd * 32, 700}, TileType::TILE_TYPE_LEFT_EDGE, "MAP1_GRASS"));

    // Elevated platform 1: longer
    int plat1Start = -10;
    int plat1End = 20;
    for (int i = plat1Start; i < plat1End; i++) {
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 300}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    }

    // Elevated platform 2: new, higher
    int plat2Start = 22;
    int plat2End = 30;
    for (int i = plat2Start; i < plat2End; i++) {
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 200}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    }

    // Middle platform: longer
    int midPlatStart = 11;
    int midPlatEnd = 35;
    interactiveTiles.push_back(new Tile(Vector2{(float)midPlatStart * 32, 500}, TileType::TILE_TYPE_RIGHT_EDGE, "MAP1_GRASS"));
    for (int i = midPlatStart + 1; i < midPlatEnd; i++) {
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 500}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    }
    interactiveTiles.push_back(new Tile(Vector2{(float)midPlatEnd * 32, 500}, TileType::TILE_TYPE_LEFT_EDGE, "MAP1_GRASS"));

    // Add a few floating tiles for variety
    interactiveTiles.push_back(new Tile(Vector2{900, 400}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    interactiveTiles.push_back(new Tile(Vector2{1200, 350}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    interactiveTiles.push_back(new Tile(Vector2{1500, 250}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));

    camera.offset = Vector2{(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    camera.target = player.getPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

World::~World() {
    for (auto& tile : interactiveTiles) {
        delete tile;
        tile = nullptr;
    }
    interactiveTiles.clear();
    for (auto& monster : monsters) {
        delete monster;
        monster = nullptr;
    }
    monsters.clear();
}

void World::addMonster(Monster* monster) {
    monsters.push_back(monster);
}

std::vector<Monster*>& World::getMonsters() {
    return monsters;
}

void World::UpdateWorld() {
    camera.target = player.getPosition();

    for (auto const& tile : interactiveTiles) {
        CollisionInfo playerCollision = player.CheckCollisionType(*tile);
        player.HandleTileCollision(*tile, playerCollision);
        
        for (auto& fireball : *player.getFireballs()) {
            CollisionInfo fireballCollision = fireball->CheckCollisionType(*tile);
            switch (fireballCollision) {
                case COLLISION_SOUTH: {
                    fireball->HandleGroundCollision(tile->getPosition().y);
                    break;
                }
                default:
                    break;
            }
        }
    }

    player.updateStateAndPhysic();

    for (auto& monster : monsters) {
        if (!monster->getIsActive()) continue;
        monster->updateStateAndPhysic();
        for (auto const& tile : interactiveTiles) {
            CollisionInfo collision = monster->CheckCollisionType(*tile);
            monster->handleCollision(*tile, collision); // Virtual method call
        }
    }
}

void World::DrawWorld() {       
    BeginMode2D(camera);
    // Draw player
    player.Draw();
    // Draw interactive tiles
    for (auto& tile : interactiveTiles) {
        tile->Draw();
    }
    // Draw monsters
    for (auto& monster : monsters) {
        monster->Draw();
    }
    EndMode2D();
}

const float World::GetGravity() {
    return GRAVITY;
}

void World::InitWorld() {
    ResourceManager::loadResource();
    GRAVITY = 2 * GetScreenHeight();
}

Mario& World::getPlayer() {
    return player;
}

std::vector<Tile*>& World::getInteractiveTiles() {
    return interactiveTiles;
}