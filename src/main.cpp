#include "QuestionBlock.h"

#include "raylib.h"
#include "ResourceManager.h"
#include "PlayableCharacter.h"
#include "GameClock.h"
#include "Level.h"
#include "Fireball.h"
#include <iostream>
#include "Tile.h"
#include "SoundController.h"
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
    while(!WindowShouldClose()){
        if(IsKeyPressed(KEY_Q)) {isPaused=!isPaused;}
        if(!isPaused){
            GameClock::getInstance().updateTimeAcum += GetFrameTime();
            //Update Loop
            while (GameClock::getInstance().updateTimeAcum >= GameClock::getInstance().DeltaTime)
            {   
                if(IsKeyPressed(KEY_A)){
                }


                stateManager.update();
                SoundController::getInstance().UpdateSoundStream();

				// Test SoundController functionality
                if (IsKeyPressed(KEY_F2)) {
                    float current = SoundController::getInstance().GetMusicVolume();
                    SoundController::getInstance().SetMusicVolume(current - 0.02f);
                }
                if (IsKeyPressed(KEY_F3)) {
                    float current = SoundController::getInstance().GetMusicVolume();
                    SoundController::getInstance().SetMusicVolume(current + 0.02f);
                }
                if (IsKeyPressed(KEY_F4)) { // Mute/unmute music with M
                    auto& sc = SoundController::getInstance();
                    if (sc.IsMusicMuted()) sc.UnmuteMusic();
                    else sc.MuteMusic();
                }
                if (IsKeyPressed(KEY_F5)) { // Mute/unmute SFX with N
                    auto& sc = SoundController::getInstance();
                    if (sc.IsSFXMuted()) sc.UnmuteSFX();
                    else sc.MuteSFX();
                }

                GameClock::getInstance().updateTimeAcum -= GameClock::getInstance().DeltaTime;
            }    
        }
            ClearBackground(BLUE);
            BeginDrawing();

            stateManager.draw();
            EndDrawing();
    }
    // Unload resources
    ResourceManager::getInstance().unloadResource();
    // Close audio device
    CloseAudioDevice();
    
    CloseWindow();
}
