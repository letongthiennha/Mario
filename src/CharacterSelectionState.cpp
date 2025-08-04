#include "CharacterSelectionState.h"
#include "StateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "GameModeSelectionState.h"

CharacterSelectionState::CharacterSelectionState(StateManager *manager): State(manager),
    marioButton( Vector2{2*(float)GetScreenWidth()/3-200, (float)GetScreenHeight()/2-300}, Vector2{300, 600} ),
    luigiButton( Vector2{(float)GetScreenWidth()/3-200, (float)GetScreenHeight()/2-300}, Vector2{600*428/725, 600}),
    home( Vector2{50, 50}, Vector2{64, 64})
{
    marioButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("MARIO_BUTTON")).DisableBackground()
        .fitTexture()
    ;
    luigiButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("LUIGI_BUTTON")).DisableBackground()
        .fitTexture();
    home.setTextures(ResourceManager::getInstance().getTexture("MENU_BUTTON_RELEASE"), ResourceManager::getInstance().getTexture("MENU_BUTTON_PRESS"));
    titleTexture = ResourceManager::getInstance().getTexture("SELECT_CHARACTER_TITLE");
}
CharacterSelectionState::~CharacterSelectionState() {
    // Cleanup if necessary
}
void CharacterSelectionState::update() {
    // Update button states and handle input
    marioButton.update();
    luigiButton.update();
    home.update();

    if (marioButton.isClicked()) {
        stateManager->setState(new GameState(stateManager, CharacterType::MARIO));
    } else if (luigiButton.isClicked()) {
        stateManager->setState(new GameState(stateManager, CharacterType::LUIGI));
    } else if (home.isClicked()) {
        stateManager->setState(new GameModeSelectionState(stateManager));
    }
}
void CharacterSelectionState::draw() {
    // Draw buttons and any other UI elements
    ClearBackground(Color{255, 210, 29, 255}); // Clear background to white
    DrawTexture(titleTexture, GetScreenWidth() / 2 - titleTexture.width / 2, 0, WHITE);
    marioButton.Draw();
    DrawTextureEx(ResourceManager::getInstance().getTexture("HUD_MARIO"),Vector2{2.0f*GetScreenWidth()/3-100,(float)GetScreenHeight()/2+350},0,2.0f,WHITE);
    DrawTextureEx(ResourceManager::getInstance().getTexture("HUD_LUIGI"),Vector2{(float)GetScreenWidth()/3-100,(float)GetScreenHeight()/2+350},0,1.0f,WHITE);
    if(marioButton.isHover()) {
    DrawRectangleRounded(Rectangle{2.0f*GetScreenWidth()/3+150,(float)GetScreenHeight()/2-250,300,300}, 0.2f, 180, Color{255, 245, 137, 220}); // Semi-transparent background
    DrawTextureEx(ResourceManager::getInstance().getTexture("HUD_MARIO"),Vector2{2.0f*GetScreenWidth()/3+200,(float)GetScreenHeight()/2-200},0,2.0f,WHITE);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Speed: 5", Vector2{2.0f*GetScreenWidth()/3+200, (float)GetScreenHeight()/2-150}, 30, 1, Color{255, 0, 0, 255});
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Accel: 4", Vector2{2.0f*GetScreenWidth()/3+200, (float)GetScreenHeight()/2-100}, 30, 1, Color{255, 0, 0, 255});

    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Jump: 3", Vector2{2.0f*GetScreenWidth()/3+200, (float)GetScreenHeight()/2-50}, 30, 1, Color{255, 0, 0, 255});
    }
    if(luigiButton.isHover()) {
    DrawRectangleRounded(Rectangle{(float)GetScreenWidth()/3-500,(float)GetScreenHeight()/2-250,300,300}, 0.2f, 180, Color{255, 245, 137, 220}); // Semi-transparent background
    DrawTextureEx(ResourceManager::getInstance().getTexture("HUD_LUIGI"),
    Vector2{(float)GetScreenWidth()/3-450,(float)GetScreenHeight()/2-200},0,1.0f,WHITE);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"),
    "Speed: 3", Vector2{(float)GetScreenWidth()/3-450, (float)GetScreenHeight()/2-150}, 30, 1, Color{0, 200, 48,255});
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"),
    "Accel: 3", Vector2{(float)GetScreenWidth()/3-450, (float)GetScreenHeight()/2-100}, 30, 1, Color{0, 200, 48,255});
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"),
    "Jump: 5", Vector2{(float)GetScreenWidth()/3-450, (float)GetScreenHeight()/2-50}, 30, 1, Color{0, 200, 48,255});
    }
    luigiButton.Draw();
    home.Draw();
}