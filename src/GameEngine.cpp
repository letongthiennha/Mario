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
    // Avoid spawning FlyingGoombas near Mario's starting position (assume Mario starts at x=64, y=700)
    // We'll skip any spawn within 100 pixels horizontally and 80 pixels vertically of (64, 700)
    auto isNearMario = [](float x, float y) {
        return (std::abs(x - 64) < 100) && (std::abs(y - 700) < 80);
    };

    struct SpawnInfo { float x, y; };
    std::vector<SpawnInfo> flyingGoombaSpawns = {
        // Higher in the sky and farther from Mario's start
        {300, 80}, {500, 60}, {700, 50}, {900, 40},
        // A few at tile level
        {300, 350}, {500, 375}, {700, 325}
    };

    for (const auto& spawn : flyingGoombaSpawns) {
        if (!isNearMario(spawn.x, spawn.y)) {
            world->addMonster(new FlyingGoomba(Vector2{spawn.x, spawn.y}, 50.0f));
        }
    }

    // Spawn Goombas exactly on tile tops (y=700 or y=500, adjusted for Goomba height 20)
    world->addMonster(new Goomba(Vector2{32, 700 - 20}, 50.0f));  // On tile at x=32, y=700
    world->addMonster(new Goomba(Vector2{96, 700 - 20}, 50.0f));  // On tile at x=96, y=700
    world->addMonster(new Goomba(Vector2{352, 700 - 20}, 50.0f)); // On tile at x=352, y=700
    world->addMonster(new Goomba(Vector2{416, 500 - 20}, 50.0f)); // On tile at x=416, y=500
    world->addMonster(new PiranhaPlant(Vector2{400, 700}, 0.0f));
    world->addMonster(new PiranhaPlant(Vector2{1200, 500}, 0.0f));
    world->addMonster(new BlueKoopaTroopa(Vector2{200, 700 - 48}, 60.0f));
    world->addMonster(new BlueKoopaTroopa(Vector2{600, 700 - 48}, 60.0f));
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
        // Draw a semi-transparent rectangle as the "Game Over" tab
        int rectWidth = 500;
        int rectHeight = 120;
        int rectX = (screenWidth - rectWidth) / 2;
        int rectY = (screenHeight - rectHeight) / 2;
        DrawRectangle(rectX, rectY, rectWidth, rectHeight, Fade(BLACK, 0.7f));
        DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, RED);

        // Draw "Game Over!" text centered
        const char* gameOverText = "Game Over!";
        int fontSize = 48;
        int textWidth = MeasureText(gameOverText, fontSize);
        DrawText(gameOverText, screenWidth / 2 - textWidth / 2, rectY + 20, fontSize, RED);

        // Draw "Press R to Restart" text centered below
        const char* restartText = "Press R to Restart";
        int restartFontSize = 28;
        int restartTextWidth = MeasureText(restartText, restartFontSize);
        DrawText(restartText, screenWidth / 2 - restartTextWidth / 2, rectY + 70, restartFontSize, WHITE);
    }
    EndDrawing();
}

void GameEngine::run() {
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}