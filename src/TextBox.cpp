#include "TextBox.h"
#include "ResourceManager.h"

TextBox::TextBox(Rectangle bounds, int maxLength, Color fill, Color hover, Color select)
        : bounds(bounds), maxLength(maxLength), fillColor(fill), hoverColor(hover), selectedColor(select) {
    }

void TextBox::Update() {
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

        // Adjust font size based on the height of the text box
        float fontSize = bounds.height * 0.8f;

        // Calculate text dimensions with the custom font
        Vector2 textSize = MeasureTextEx(ResourceManager::getInstance().getFonts("USER_INPUT_FONT"), displayText.c_str(), fontSize, 1);

        // Calculate text position to be centered vertically
        float textY = bounds.y + (bounds.height / 2.0f) - (textSize.y / 2.0f);

        // Use DrawTextEx to specify the font
        DrawTextEx(ResourceManager::getInstance().getFonts("USER_INPUT_FONT"), displayText.c_str(), { bounds.x + 5, textY }, fontSize, 1, BLACK);
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

    void TextBox::setSelected(bool isSelected) {
            selected = isSelected;
		    showCursor = isSelected; // Show cursor if selected
    }

