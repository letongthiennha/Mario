#pragma once
#include "raylib.h"
#include "GameClock.h"
#include <string>

class TextBox {
private:
    Rectangle bounds;
    std::string text;
    bool selected = false;
    int maxLength = 128;
    float blinkTimer = 0.0f;
    bool showCursor = true;
    Color fillColor;
    Color hoverColor;
    Color selectedColor;

public:
    TextBox(Rectangle bounds, int maxLength = 128, Color fill = WHITE, Color hover = LIGHTGRAY, Color select = RAYWHITE);

    void Update();
    void Draw() const;
    const std::string& GetText() const;
    void Clear();
    void SetText(const std::string& newText);
	void setSelected(bool isSelected);
};
