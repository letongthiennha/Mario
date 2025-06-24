

#include "raylib.h"
#include "ResourceManager.h"
#include "Mario.h"
#include "GameClock.h"
#include "World.h"
#include "Fireball.h"
#include <iostream>
#include "Tile.h"
#include "SoundControoler.h"
#include "Button.h"
#include "MenuState.h"
#include "StateManager.h"
int main(){
    InitWindow(1600, 900, "Mario");
    InitAudioDevice();
    // World gameWorld;
    // World::InitWorld();
    // World gw;
    SetTargetFPS(144);
    // SoundController::getInstance().PlaySound("TEST");
    // PlayMusicStream(ResourceManager::getInstance().getMusics("Test"));
    bool isPaused = false;
    StateManager stateManager;
    ResourceManager::getInstance().loadResource();
    while(!WindowShouldClose()){
        // UpdateMusicStream(ResourceManager::getInstance().getMusics("Test"));
        if(IsKeyPressed(KEY_Q)) {isPaused=!isPaused;}
        if(!isPaused){
            GameClock::getInstance().updateTimeAcum += GetFrameTime();
            //Update Loop
            while (GameClock::getInstance().updateTimeAcum >= GameClock::getInstance().DeltaTime)
            {   

                // gw.UpdateWorld();
                stateManager.update();
                GameClock::getInstance().updateTimeAcum -= GameClock::getInstance().DeltaTime;
            }    
        }
            ClearBackground(BLUE);
            BeginDrawing();
            // gw.DrawWorld();
            stateManager.draw();
            EndDrawing();
    }
    // Unload resources
    ResourceManager::getInstance().unloadResource();
    // Close audio device
    CloseAudioDevice();
    CloseWindow();
}
