/* File: GameEngine.cpp */
#include "../include/GameEngine.h"

GameEngine::GameEngine(int width, int height) : screenWidth(width), screenHeight(height), isPaused(false), isGameOver(false), startDelay(1.0f) {
    InitWindow(screenWidth, screenHeight, "Mario Game");
    ResourceManager::loadResource();
    World::InitWorld();
    world = new World();
    player = &world->getPlayer();
    spawnMonsters();
    // Initial collision check to settle Goombas on tiles
    for (auto& monster : monsters) {
        if (!monster->getIsActive()) continue;
        for (auto const& tile : world->getInteractiveTiles()) {
            CollisionInfo collision = monster->CheckCollisionType(*tile);
            dynamic_cast<Goomba*>(monster)->handleCollision(*tile, collision);
        }
    }
    SetTargetFPS(144);
}

GameEngine::~GameEngine() {
    for (auto& monster : monsters) {
        delete monster;
        monster = nullptr;
    }
    monsters.clear();
    delete world;
    ResourceManager::unloadResource();
    CloseWindow();
}

void GameEngine::spawnMonsters() {
    // Spawn Goombas exactly on tile tops (y=700 or y=500, adjusted for Goomba height 20)
    monsters.push_back(new Goomba(Vector2{32, 700 - 20}));  // On tile at x=32, y=700
    monsters.push_back(new Goomba(Vector2{96, 700 - 20}));  // On tile at x=96, y=700
    monsters.push_back(new Goomba(Vector2{352, 700 - 20})); // On tile at x=352, y=700
    monsters.push_back(new Goomba(Vector2{416, 500 - 20})); // On tile at x=416, y=500
}

void GameEngine::update() {
    if (IsKeyPressed(KEY_Q)) isPaused = !isPaused;
    if (isPaused || isGameOver) return;
    
    GameClock::updateTimeAcum += GetFrameTime();
    startDelay -= GetFrameTime();
    while (GameClock::updateTimeAcum >= GameClock::GetUpdateDeltaTime()) {
        world->UpdateWorld();
        
        // Update monsters
        for (auto& monster : monsters) {
            if (!monster->getIsActive()) continue;
            monster->updateStateAndPhysic();
            
            // Check monster-tile collisions
            for (auto const& tile : world->getInteractiveTiles()) {
                CollisionInfo collision = monster->CheckCollisionType(*tile);
                dynamic_cast<Goomba*>(monster)->handleCollision(*tile, collision);
            }
            
            // Check player-monster collision after delay
            if (startDelay <= 0) {
                CollisionInfo playerCollision = player->CheckCollisionType(*monster);
                if (playerCollision == COLLISION_SOUTH) {
                    monster->setIsActive(false);
                } else if (playerCollision != COLLISION_NONE) {
                    player->changeToSmall();
                    if (player->getForm() == MARIO_STATE_SMALL) {
                        isGameOver = true;
                    }
                }
            }
        }
        GameClock::updateTimeAcum -= GameClock::GetUpdateDeltaTime();
    }
}

void GameEngine::draw() {
    ClearBackground(RAYWHITE);
    BeginDrawing();
    world->DrawWorld();
    for (auto& monster : monsters) {
        monster->Draw();
    }
    if (isGameOver) {
        DrawText("Game Over!", screenWidth / 2 - 100, screenHeight / 2, 40, RED);
    }
    EndDrawing();
}

void GameEngine::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}