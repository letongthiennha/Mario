#include "HUD.h"
#include <string>
#include "ResourceManager.h"
HUD::HUD( Vector2 coinsPos, Vector2 coinsSize, Vector2 scorePos, Vector2 scoreSize,CharacterType characterType):
     coins(0), score(0), lives(3),
    coinsPosition(coinsPos), coinsSize(coinsSize), coinTexture(&ResourceManager::getInstance().getInstance().getTexture("HUD_COINS")),
    scorePosition(scorePos), scoreSize(scoreSize), selectedCharacterType(characterType),
    textColor(GOLD), backgroundColor(BLACK)
{
    if(selectedCharacterType == CharacterType::MARIO) {
        PlayerHUD = &ResourceManager::getInstance().getTexture("HUD_MARIO");
    } else if(selectedCharacterType == CharacterType::LUIGI) {
        PlayerHUD = &ResourceManager::getInstance().getTexture("HUD_LUIGI");
    } else {
        PlayerHUD = &ResourceManager::getInstance().getTexture("HUD_MARIO"); // Default to Mario if no character is selected
    }
    font = &ResourceManager::getInstance().getFonts("SUPER_MARIO_WORLD_FONT");
}

HUD::HUD(CharacterType characterType):HUD(Vector2{(float)GetScreenWidth()-200, 20}, Vector2{30, 30},Vector2{(float)GetScreenWidth()-150,20}, Vector2{100, 50}, characterType)
{

}

void HUD::Draw()
{
    // Draw coins
    DrawTextureNPatch(*coinTexture,
                      NPatchInfo{Rectangle{0, 0, (float)(*coinTexture).width,
                                          (float)(*coinTexture).height}, 0, 0, 0, 0},
                      Rectangle{coinsPosition.x, coinsPosition.y, coinsSize.x, coinsSize.y}, Vector2{0, 0}, 0.0f, WHITE);
    DrawTextEx(*font, ("x"+std::to_string(coins)).c_str(), Vector2{coinsPosition.x + 50, coinsPosition.y }, 20, 2, WHITE);

/// Draw score
    DrawTextEx(*font, (std::to_string(score)).c_str(), Vector2{scorePosition.x , scorePosition.y +30 }, 20, 2, WHITE);

    //Draw Lives
    DrawTextureNPatch(*PlayerHUD,

                      NPatchInfo{Rectangle{0, 0, (float)(*PlayerHUD).width,
                                          (float)(*PlayerHUD).height}, 0, 0, 0, 0},
                      Rectangle{(float)GetScreenWidth()/2-16-300, scorePosition.y, 120, 24}, Vector2{0, 0}, 0.0f, WHITE);

    if(selectedCharacterType == CharacterType::MARIO){
        DrawTextureNPatch(ResourceManager::getInstance().getTexture("SMALL_MARIO_0_RIGHT"),
                       NPatchInfo{Rectangle{0, 0, (float)ResourceManager::getInstance().getTexture("SMALL_MARIO_0_RIGHT").width,
                                           24}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -365,scorePosition.y+25 , 32, 24}, Vector2{0, 0}, 0.0f, WHITE);
    }
    else if(selectedCharacterType == CharacterType::LUIGI){
    DrawTextureNPatch(ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_RIGHT"),
                       NPatchInfo{Rectangle{0, 0, (float)ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_RIGHT").width,
                                           24}, 0, 0, 0, 0},
                       Rectangle{(float)GetScreenWidth() / 2 -365,scorePosition.y+25 , 32, 24}, Vector2{0, 0}, 0.0f, WHITE);
    }

    DrawTextEx(*font, ("x"+std::to_string(lives)).c_str(), Vector2{(float)GetScreenWidth()/2-20-300, scorePosition.y+30 }, 20, 2, WHITE);
    // // Draw score    
}

void HUD::onNotify(GAME_EVENT event, int newValue)
{
    switch (event) {
        case GAME_EVENT::COIN_CHANGE:
            coins = newValue;
            break;
        case GAME_EVENT::SCORE_CHANGE:
            score = newValue;
            break;
        case GAME_EVENT::LIVES_CHANGE:
            lives = newValue;
            break;
    }

}

HUD &HUD::setFont(Font& font)
{
    this->font = &font;
    return *this;
}

HUD &HUD::setTextColor(Color color)
{
    this->textColor = color;
    return *this;
}

HUD &HUD::setBackgroundColor(Color color)
{
    this->backgroundColor = color;
    return *this;
}
