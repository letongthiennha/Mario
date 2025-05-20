

#include "raylib.h"
#include "Application.h"


int main(){
    Texture2D a = LoadTexture("D:\\Project\\Data Structure\\Data-Structure\\assets\\background.png");

    InitWindow(1600, 900, "Mario");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        ClearBackground(RAYWHITE);
        BeginDrawing();
        DrawTexture(a, 50, 50, BLANK);
        EndDrawing();
    }
    CloseWindow();
}

