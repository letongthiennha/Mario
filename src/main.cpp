

#include "raylib.h"
#include "ResourceManager.h"
#include "Mario.h"
#include "GameClock.h"
#include "World.h"
#include "Fireball.h"
#include <iostream>
#include "Tile.h"
#include "SoundControoler.h"
int main(){
    InitWindow(1600, 900, "Mario");
    InitAudioDevice();
    // World gameWorld;
    World::InitWorld();
    World gw;
    SetTargetFPS(144);
    SoundController::getInstance().PlaySound("TEST");
    PlayMusicStream(ResourceManager::getInstance().getMusics("Test"));

    bool isPaused = false;
    while(!WindowShouldClose()){
        UpdateMusicStream(ResourceManager::getInstance().getMusics("Test"));
        if(IsKeyPressed(KEY_Q)) {isPaused=!isPaused;}
        if(!isPaused){
            GameClock::getInstance().updateTimeAcum += GetFrameTime();
            //Update Loop
            while (GameClock::getInstance().updateTimeAcum >= GameClock::getInstance().FIXED_TIME_STEP)
            {
                gw.UpdateWorld();
                GameClock::getInstance().updateTimeAcum -= GameClock::getInstance().FIXED_TIME_STEP;
            }    
        }
            ClearBackground(BLUE);
            BeginDrawing();
            gw.DrawWorld();
            EndDrawing();
    }
    ResourceManager::getInstance().unloadResource();

    // Load the image (not texture!)
    // Image image = LoadImage("resources/luigi.png");

    // // Set nearest-neighbor filter mode
    // SetTextureFilter(LoadTextureFromImage(image), TEXTURE_FILTER_POINT);  // Optional for display

    // // Scale by 4x using nearest neighbor
    // ImageResizeNN(&image, image.width * 2, image.height * 2);

    // // Save the upscaled image
    // ExportImage(image, "resources/output.png");

    // // Clean up
    // UnloadImage(image);

    // return 0;

    // CloseWindow();

}
