

#include "raylib.h"
#include "Application.h"
#include "ResourceManager.h"
#include "Mario.h"
#include "GameClock.h"
int main(){
    InitWindow(1600, 900, "Mario");
    ResourceManager::loadResource();
    GameClock::startClock();
    Mario player;
    SetTargetFPS(144);

    while(!WindowShouldClose()){
        GameClock::updateTimeAcum += GetFrameTime();
        //Update Loop
        while (GameClock::updateTimeAcum >= GameClock::FIXED_TIME_STEP)
        {
            player.update();
            GameClock::update();
            if(GameClock::GetUpdateDeltaTime()==0)
                GameClock::updateTimeAcum -= GameClock::FIXED_TIME_STEP;
            GameClock::updateTimeAcum -= GameClock::GetUpdateDeltaTime();
        }
    ClearBackground(RAYWHITE);
    BeginDrawing();
    player.Draw();
    EndDrawing();
    }
    ResourceManager::unloadResource();
    CloseWindow();
}

