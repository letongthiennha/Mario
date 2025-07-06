#include "QuestionBlock.h"

#include "raylib.h"
#include "ResourceManager.h"
#include "Mario.h"
#include "GameClock.h"
#include "Level.h"
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

    SetTargetFPS(144);
    bool isPaused = false;
    ResourceManager::getInstance().loadResource();

    StateManager stateManager;
    // QuestionBlock testBlock({200, 600}, {32, 32}, RED);
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_Q)) {isPaused=!isPaused;}
        if(!isPaused){
            GameClock::getInstance().updateTimeAcum += GetFrameTime();
            //Update Loop
            while (GameClock::getInstance().updateTimeAcum >= GameClock::getInstance().DeltaTime)
            {   

                // gw.UpdateLevel();
                stateManager.update();
                SoundController::getInstance().UpdateSoundStream();
                GameClock::getInstance().updateTimeAcum -= GameClock::getInstance().DeltaTime;
            }    
        }
            // testBlock.updateStateAndPhysic();
            ClearBackground(BLUE);
            BeginDrawing();
            // ClearBackground(RAYWHITE);
            stateManager.draw();
            // testBlock.Draw();
            EndDrawing();
    }
    // Unload resources
    ResourceManager::getInstance().unloadResource();
    // Close audio device
    CloseAudioDevice();
    
    CloseWindow();
}
