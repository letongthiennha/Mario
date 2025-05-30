#include "../include/World.h"
#include "../include/ResourceManager.h"
#include "../include/Monster.h"
#include "../include/Fireball.h"

float World::GRAVITY = 0.0f;

World::World() : player() {
    interactiveTiles.push_back(new Tile(Vector2{0, 700}, TileType::TILE_TYPE_RIGHT_EDGE, "MAP1_GRASS"));
    for (int i = 1; i < 10; i++) {
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 700}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 300}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    }
    interactiveTiles.push_back(new Tile(Vector2{10 * 32, 700}, TileType::TILE_TYPE_LEFT_EDGE, "MAP1_GRASS"));
    interactiveTiles.push_back(new Tile(Vector2{11 * 32, 500}, TileType::TILE_TYPE_RIGHT_EDGE, "MAP1_GRASS"));
    for (int i = 12; i < 25; i++) {
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32, 500}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
        interactiveTiles.push_back(new Tile(Vector2{(float)i * 32 + 64, 700}, TileType::TILE_TYPE_NORMAL, "MAP1_GRASS"));
    }
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