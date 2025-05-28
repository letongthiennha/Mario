

#include "raylib.h"
#include "Application.h"
#include "ResourceManager.h"
#include "Mario.h"
#include "GameClock.h"
#include "World.h"
#include "Fireball.h"
#include <iostream>
#include "Tile.h"
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
            ClearBackground(BLUE);
            BeginDrawing();
            gw.DrawWorld();
            EndDrawing();
    }
    ResourceManager::unloadResource();
    CloseWindow();
    
}
