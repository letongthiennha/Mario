#include "../include/GameEngine.h"

GameEngine::GameEngine(int width, int height) : screenWidth(width), screenHeight(height), isPaused(false), isGameOver(false), startDelay(1.0f) {
    InitWindow(screenWidth, screenHeight, "Mario Game");
    ResourceManager::loadResource();
    World::InitWorld();
    world = new World();
    player = &world->getPlayer();
    spawnMonsters();
    // Initial collision check to settle Goombas on tiles
    for (auto& monster : world->getMonsters()) {
        if (!monster->getIsActive()) continue;
        for (auto const& tile : world->getInteractiveTiles()) {
            CollisionInfo collision = monster->CheckCollisionType(*tile);
            monster->handleCollision(*tile, collision); // Virtual method call
        }
    }
    SetTargetFPS(144);
}

GameEngine::~GameEngine() {
    delete world;
    ResourceManager::unloadResource();
    CloseWindow();
}

void GameEngine::spawnMonsters() {
    // Spawn Goombas exactly on tile tops (y=700 or y=500, adjusted for Goomba height 20)
    world->addMonster(new Goomba(Vector2{32, 700 - 20}, 50.0f));  // On tile at x=32, y=700
    world->addMonster(new Goomba(Vector2{96, 700 - 20}, 50.0f));  // On tile at x=96, y=700
    world->addMonster(new Goomba(Vector2{352, 700 - 20}, 50.0f)); // On tile at x=352, y=700
    world->addMonster(new Goomba(Vector2{416, 500 - 20}, 50.0f)); // On tile at x=416, y=500
}

void GameEngine::update() {
    if (IsKeyPressed(KEY_Q)) isPaused = !isPaused;
    if (isPaused) return;

    if (isGameOver && IsKeyPressed(KEY_R)) {
        // Restart: Reset game state
        delete world;
        World::InitWorld();
        world = new World();
        player = &world->getPlayer();
        spawnMonsters();
        for (auto& monster : world->getMonsters()) {
            if (!monster->getIsActive()) continue;
            for (auto const& tile : world->getInteractiveTiles()) {
                CollisionInfo collision = monster->CheckCollisionType(*tile);
                monster->handleCollision(*tile, collision); // Virtual method call
            }
        }
        isGameOver = false;
        startDelay = 1.0f;
    }

    if (isGameOver) return;

    GameClock::updateTimeAcum += GetFrameTime();
    startDelay -= GetFrameTime();
    while (GameClock::updateTimeAcum >= GameClock::GetUpdateDeltaTime()) {
        world->UpdateWorld();

        // Check player-monster collisions
        for (auto& monster : world->getMonsters()) {
            if (!monster->getIsActive()) continue;
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
    if (isGameOver) {
        DrawText("Game Over! Press R to Restart", screenWidth / 2 - 200, screenHeight / 2, 40, RED);
    }
    EndDrawing();
}

void GameEngine::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}