#include "raylib.h"
#include "../include/Application.h"
#include "../include/ResourceManager.h"
#include "../include/Mario.h"
#include "../include/GameClock.h"
#include "../include/World.h"
#include "../include/Fireball.h"
#include "../include/Tile.h"
#include <iostream>
int main(){
    InitWindow(1600, 900, "Mario");
    // World gameWorld;
    World::InitWorld();
    World gw;
    SetTargetFPS(144);

    bool isPaused = false;
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_Q)) {isPaused=!isPaused;}
        if(!isPaused){
            GameClock::updateTimeAcum += GetFrameTime();
            //Update Loop
            while (GameClock::updateTimeAcum >= GameClock::GetUpdateDeltaTime())
            {
                gw.UpdateWorld();
                GameClock::updateTimeAcum -= GameClock::GetUpdateDeltaTime();
            }    
        }
            ClearBackground(RAYWHITE);
            BeginDrawing();
            gw.DrawWorld();
            EndDrawing();
    }
    ResourceManager::unloadResource();
    CloseWindow();
    
}
