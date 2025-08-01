#pragma once

#include "raylib.h"
#include <string>
#include <functional>

enum class Button2State {
    NORMAL,
    HOVERED,
    PRESSED
};

class Button2 {
public:
    Button2() = default;
    Button2(Vector2 position, Vector2 size);

    void update();
    void Draw();

    // Setters for customization
    void setTextures(Texture2D normal, Texture2D pressed);
 
    bool isClicked() const;

private:
    Rectangle bounds;
    Button2State state = Button2State::NORMAL;
    bool clicked = false;

    // Texture properties
    Texture2D normalTexture;
    Texture2D pressedTexture;

    float cooldownDuration = 0.5f;
    float cooldownTimer = 0.0f;
};