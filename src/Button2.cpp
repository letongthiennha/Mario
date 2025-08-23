#include "Button2.h"
#include "raylib.h"
#include "GameClock.h"
#include <iostream>

Button2::Button2(Vector2 position, Vector2 size)
    : bounds({ position.x, position.y, size.x, size.y }),
    state(Button2State::NORMAL),
    receiveClick(false),
    doneClick(false),
    normalColor(LIGHTGRAY),
    pressedColor(DARKGRAY),
    textColor(BLACK) {
}

void Button2::update() {
    doneClick = false;
    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, bounds)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            receiveClick = true;
            state = Button2State::PRESSED;
        }
        else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && receiveClick) {
            doneClick = true;
            receiveClick = false;
            state = Button2State::HOVERED;
        }
        else {
            state = (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) ? Button2State::PRESSED : Button2State::HOVERED;
        }
    }
    else {
        state = Button2State::NORMAL;
        receiveClick = false; // cancel click if mouse leaves
    }
}

void Button2::Draw() {
    if (useTextures) {
        Texture2D textureToDraw = (state == Button2State::HOVERED || state == Button2State::PRESSED) ? pressedTexture : normalTexture;
        Rectangle sourceRec = { 0.0f, 0.0f, (float)textureToDraw.width, (float)textureToDraw.height };
        DrawTexturePro(textureToDraw, sourceRec, bounds, { 0, 0 }, 0.0f, WHITE);
    }
    else {
        Color bgColor = (state == Button2State::PRESSED || state == Button2State::HOVERED) ? pressedColor : normalColor;
        DrawRectangleRec(bounds, bgColor);

        if (!buttonText.empty()) {
            Font currentFont = (font == nullptr) ? GetFontDefault() : *font;
            Vector2 textSize = MeasureTextEx(currentFont, buttonText.c_str(), currentFont.baseSize, 2);
            float textX = bounds.x + (bounds.width - textSize.x) / 2;
            float textY = bounds.y + (bounds.height - textSize.y) / 2;
            DrawTextEx(currentFont, buttonText.c_str(), { textX, textY }, currentFont.baseSize, 2, textColor);
        }
    }
}

void Button2::setText(const std::string& text) {
    this->buttonText = text;
}

void Button2::setColors(Color normal, Color pressed, Color textColor) {
    this->normalColor = normal;
    this->pressedColor = pressed;
    this->textColor = textColor;
}

void Button2::setTextures(Texture2D normal, Texture2D pressed) {
    this->normalTexture = normal;
    this->pressedTexture = pressed;
    this->useTextures = true;
}

void Button2::setFont(Font* font) {
	this->font = font;
}

bool Button2::isClicked() const {
    return doneClick;
}