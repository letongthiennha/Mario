#pragma once
#include "UIObject.h"
#include "Observer.h"
class UIObject;
class Observer;
class HUD:public UIObject , public Observer {
private:
    int coins;
    int score;
    int lives;
    
    Vector2 coinsPosition;
    Vector2 coinsSize;
    Texture2D *coinTexture;

    Vector2 scorePosition;
    Vector2 scoreSize;
    Texture2D *PlayerHUD;

    Color textColor;
    Color backgroundColor;
    Font* font;
public:
    HUD(Vector2 coinsPos, Vector2 coinsSize, Vector2 scorePos, Vector2 scoreSize);
    HUD();
    ~HUD() override = default;

    void update() override{};
    void Draw() override;

    // Observer interface
    void onNotify(GAME_EVENT event, int newValue) override;

    // Setters
    HUD& setFont(Font& font);
    HUD& setTextColor(Color color);
    HUD& setBackgroundColor(Color color);
};