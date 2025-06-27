#include "HUD.h"
#include <string>
#include "ResourceManager.h"
HUD::HUD( Vector2 coinsPos, Vector2 coinsSize, Vector2 scorePos, Vector2 scoreSize):
     coins(0), score(0),
    coinsPosition(coinsPos), coinsSize(coinsSize),
    scorePosition(scorePos), scoreSize(scoreSize),
    textColor(GOLD), backgroundColor(BLACK)
{
    font = &ResourceManager::getInstance().getFonts("HUD_FONT");
}

HUD::HUD():HUD(Vector2{(float)GetScreenWidth()-200, 50}, Vector2{30, 30},Vector2{(float)GetScreenWidth()/2-200,50}, Vector2{100, 50}
    )
{

}

void HUD::Draw()
{
    // Draw coins
    DrawTextureNPatch(ResourceManager::getInstance().getInstance().getTexture("HUD_COINS"),
                      NPatchInfo{Rectangle{0, 0, (float)ResourceManager::getInstance().getInstance().getTexture("HUD_COINS").width,
                                          (float)ResourceManager::getInstance().getInstance().getTexture("HUD_COINS").height}, 0, 0, 0, 0},
                      Rectangle{coinsPosition.x, coinsPosition.y, coinsSize.x, coinsSize.y}, Vector2{0, 0}, 0.0f, WHITE);
    DrawTextEx(*font, ("x"+std::to_string(coins)).c_str(), Vector2{coinsPosition.x + 50, coinsPosition.y }, 30, 2, textColor);


    // // Draw score
    DrawTextEx(*font, "Score: ", Vector2{scorePosition.x, scorePosition.y}, 30, 2, textColor);
    DrawTextEx(*font, (std::to_string(score)).c_str(), Vector2{scorePosition.x +100, scorePosition.y }, 30, 2, textColor);
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
