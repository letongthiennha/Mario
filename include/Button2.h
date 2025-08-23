#pragma once

#include "raylib.h"
#include <string>

enum class Button2State {
    NORMAL,
    HOVERED,
    PRESSED
};

class Button2 {
public:
    Button2(Vector2 position, Vector2 size);

    void update();
    void Draw();

    bool isClicked() const;

    // Methods for text-based button
    void setText(const std::string& text);
    void setColors(Color normal, Color pressed, Color textColor);

    // Methods for texture-based button
    void setTextures(Texture2D normal, Texture2D pressed);

    void setFont(Font* font);

private:
    Rectangle bounds;
    Button2State state;
    bool receiveClick;
    bool doneClick;
    float acumTimer = 0.0f;

    // Text properties
    std::string buttonText;
    Color normalColor;
    Color pressedColor;
    Color textColor;
    Font* font = nullptr;

    // Texture properties
    Texture2D normalTexture = { 0 };
    Texture2D pressedTexture = { 0 };
    bool useTextures = false;

};