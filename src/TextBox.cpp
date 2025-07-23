#include "TextBox.h"

TextBox::TextBox(Rectangle bounds, int maxLength = 128, Color fill = WHITE, Color hover = LIGHTGRAY, Color select = RAYWHITE)
        : bounds(bounds), maxLength(maxLength), fillColor(fill), hoverColor(hover), selectedColor(select) {
    }

void TextBox::Update(float delta) {
        // Check if clicked inside the box
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            selected = CheckCollisionPointRec(mouse, bounds);
        }

        // Handle typing
        if (selected) {
            int key = GetCharPressed();
            while (key > 0) {
                if (text.length() < maxLength && key >= 32 && key <= 125) {
                    text += static_cast<char>(key);
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
                text.pop_back();
            }
        }

        // Blink logic
        blinkTimer += GameClock::getInstance().DeltaTime;
        if (blinkTimer >= 0.5f) {
            blinkTimer = 0.0f;
            showCursor = !showCursor;
        }
    }

    void TextBox::Draw() const {
        Vector2 mouse = GetMousePosition();
        bool hovered = CheckCollisionPointRec(mouse, bounds);

        // Fill color logic
        Color background = fillColor;
        if (selected)
            background = selectedColor;
        else if (hovered)
            background = hoverColor;

        std::string displayText = text;
        if (selected && showCursor) {
            displayText += "|";
        }

        DrawRectangleRec(bounds, background);
        DrawRectangleLinesEx(bounds, 2, BLACK);

        DrawText(displayText.c_str(), bounds.x + 5, bounds.y + 8, 20, BLACK);
    }

    const std::string& TextBox::GetText() const {
        return text;
    }

    void TextBox::Clear() {
        text.clear();
    }

    void TextBox::SetText(const std::string& newText) {
        text = newText.substr(0, maxLength);
    }
