#include "CreditState.h"
#include "ResourceManager.h"
#include "SoundController.h"
CreditState::CreditState(StateManager *manager): State(manager),
    SkipButton(Vector2{(float)GetScreenWidth() - 150, (float)GetScreenHeight() - 100}, Vector2{100, 50})

{
    SkipButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("SKIP_BUTTON"));
    SkipButton
        .setText("Skip")
        .setTextSize(20);
    SoundController::getInstance().StopAllSounds(); // Stop all sounds before starting the credits
    SoundController::getInstance().PlayMusic("CREDITS_MUSIC");
    for (int i = 0; i <5;++i){
            // Coin(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);

        coins.emplace_back( new Coin(Vector2{(float)GetScreenWidth()/2 -250 + i*110, (float)GetScreenHeight()/2 + 200}, Vector2{100, 100}, WHITE, 0.2f, 4));
    }
}

CreditState::~CreditState()
{
    for (auto coin : coins)
    {
        delete coin;
    }
}

void CreditState::draw()
{
    ClearBackground(RAYWHITE); // Clear background to white
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Credits", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Credits", 40, 1).x/2, 50}, 40, 1, RED);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Game Design: Nhan & Khai", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Game Design: Nhan & Khai", 30, 1).x/2, 150}, 30, 1, BLUE);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Programming: Nhan", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Mario: Nhan", 30, 1).x/2, 200}, 30, 1, GOLD);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Monster: Loc & Nhan", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Monster: Loc & Nhan", 30, 1).x/2, 250}, 30, 1, RED);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Block: Huu", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Block: Huu", 30, 1).x/2, 300}, 30, 1, GREEN);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Items: Khai", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Items: Khai", 30, 1).x/2, 350}, 30, 1, GOLD);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "UI: Khai & Nhan", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "UI: Khai & Nhan", 30, 1).x/2, 400}, 30, 1, BLUE);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "GROUP 10", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "GROUP 10", 30, 1).x/2, 450}, 30, 1, RED);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Thanks For Playing", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Thanks For Playing", 30, 1).x/2, (float)GetScreenHeight()/2 + 150}, 30, 1, GOLD);
    DrawTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Press Skip to return to Menu", Vector2{(float)GetScreenWidth()/2 - MeasureTextEx(ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT"), "Press Skip to return to Menu", 30, 1).x/2, (float)GetScreenHeight() - 100}, 30, 1, BLACK);
    DrawTextureEx(ResourceManager::getInstance().getTexture("SUPER_MARIO_VICTORY"), Vector2{100,(float)GetScreenHeight()-200}, 0, 2.0f, WHITE); // Draw background texture
    DrawTextureEx(ResourceManager::getInstance().getTexture("FIRE_LUIGI_VICTORY"), Vector2{(float)GetScreenWidth()-200,(float)GetScreenHeight()/2-100}, 0, 2.0f, WHITE); // Draw background texture
    DrawTextureEx(ResourceManager::getInstance().getTexture("MUSHROOM"), Vector2{(float)GetScreenWidth()/2-200,40}, 0, 2.0f, WHITE); // Draw background texture
    DrawTextureEx(ResourceManager::getInstance().getTexture("MUSHROOM"), Vector2{(float)GetScreenWidth()/2+130,40}, 0, 2.0f, WHITE); // Draw background texture
    DrawTextureEx(ResourceManager::getInstance().getTexture("FIRE_FLOWER_0"), Vector2{100,(float)GetScreenHeight()/2-200}, 0, 2.0f, WHITE); // Draw background texture
    DrawTextureEx(ResourceManager::getInstance().getTexture("STAR"), Vector2{(float)GetScreenWidth()-200,(float)GetScreenHeight()/2-200}, 0, 2.0f, WHITE); // Draw background texture
    // DrawTextureEx(ResourceManager::getInstance().getTexture("COIN_2"), Vector2{(float)GetScreenWidth()/2-200,(float)GetScreenHeight()/2+200}, 0, 2.0f, WHITE); // Draw background texture
    // DrawTextureEx(ResourceManager::getInstance().getTexture("COIN_2"), Vector2{(float)GetScreenWidth()/2-100,(float)GetScreenHeight()/2+200}, 0, 2.0f, WHITE); // Draw background texture
    // DrawTextureEx(ResourceManager::getInstance().getTexture("COIN_2"), Vector2{(float)GetScreenWidth()/2,(float)GetScreenHeight()/2+200}, 0, 2.0f, WHITE); // Draw background texture
    for(auto &coin : coins)
    {
        coin->Draw();
    }
    DrawTextureEx(ResourceManager::getInstance().getTexture("Question_Block_0"), Vector2{100,(float)GetScreenHeight()/2}, 0, 2.0f, WHITE); // Draw background texture
    DrawTextureEx(ResourceManager::getInstance().getTexture("BANZAIBILL_0"), Vector2{(float)GetScreenWidth()-200,(float)GetScreenHeight()/2+200}, 0, 1.0f, WHITE); // Draw background texture
    SkipButton.Draw();
}
void CreditState::update()
{
    SkipButton.update();
    if (SkipButton.isClicked()) {
        stateManager->setState(new MenuState(stateManager)); // Switch to MenuState when skip button is clicked
    }
}