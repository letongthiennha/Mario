#include "Slider.h"
#include "raylib.h"
#include <algorithm>

Slider::Slider(Vector2 position, float width, float minValue, float maxValue, float initialValue)
    : minValue(minValue), maxValue(maxValue), width(width), dragging(false)
{
    // Clamp initial value and calculate ratio
    float clampedValue = std::clamp(initialValue, minValue, maxValue);
    ratio = (maxValue != minValue) ? (clampedValue - minValue) / (maxValue - minValue) : 0.0f;

    // Track is a thin rectangle
    track = { position.x, position.y, width, 6 };

    // Handle is a square, centered vertically on the track
    float handleX = position.x + ratio * width - 10;
    float handleY = position.y - 7;
    handle = { handleX, handleY, 20, 20 };
}

void Slider::update() {
    Vector2 mouse = GetMousePosition();

    // Start dragging if mouse pressed on handle
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, handle)) {
        dragging = true;
    }
    // Stop dragging if mouse released
    if (dragging && !IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        dragging = false;
    }
    // Update ratio and handle position while dragging
    if (dragging) {
        float x = std::clamp(mouse.x, track.x, track.x + width);
        ratio = (x - track.x) / width;
        handle.x = x - handle.width / 2;
    }
    else {
        // Keep handle in sync with ratio if changed externally
        handle.x = track.x + ratio * width - handle.width / 2;
    }
}

void Slider::Draw() {
    // Draw track
    DrawRectangleRec(track, DARKGRAY);

    // Draw handle (highlight if hovered or dragging)
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, handle);
    Color handleColor = dragging ? ORANGE : (hovered ? LIGHTGRAY : GRAY);
    DrawRectangleRec(handle, handleColor);

    // Optionally, draw border
    DrawRectangleLinesEx(handle, 2, BLACK);
}

float Slider::getValue() const {
    return minValue + ratio * (maxValue - minValue);
}

float Slider::getRatio() const {
    return ratio;
}

void Slider::setRatio(float ratio) {
    this->ratio = ratio;
}

Rectangle Slider::getTrackRect() const {
    return track;
}