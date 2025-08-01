#include "Button2.h"
#include "raylib.h"
#include "GameClock.h"
#include <iostream>

Button2::Button2(Vector2 position, Vector2 size)
    : bounds({ position.x, position.y, size.x, size.y }),
    state(Button2State::NORMAL),
    clicked(false){
}

void Button2::update() {
    clicked = false;
    Vector2 mousePoint = GetMousePosition();

    if (cooldownTimer > 0) {
        cooldownTimer -= GameClock::getInstance().DeltaTime;
    }

    if (CheckCollisionPointRec(mousePoint, bounds)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            state = Button2State::PRESSED;
        }
        else {
            state = Button2State::HOVERED;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && cooldownTimer <= 0.0f) {
            clicked = true;
            cooldownTimer = cooldownDuration;
        }
    }
    else {
        state = Button2State::NORMAL;
    }
}

void Button2::Draw() {
    if (normalTexture.id != 0 && pressedTexture.id != 0) {
        Texture2D textureToDraw = (state == Button2State::HOVERED) ? pressedTexture : normalTexture;
        Rectangle sourceRec = { 0.0f, 0.0f, (float)textureToDraw.width, (float)textureToDraw.height };
        DrawTexturePro(textureToDraw, sourceRec, bounds, { 0, 0 }, 0.0f, WHITE);
    } else {
		// Handle the case where textures are not set
    std:: cerr << "Faild to draw button: textures not set." << std::endl;
    }
}

void Button2::setTextures(Texture2D normal, Texture2D pressed) {
    this->normalTexture = normal;
    this->pressedTexture = pressed;
    //// Update bounds to match new texture size
    //this->bounds.width = normal.width;
    //this->bounds.height = normal.height;
}

bool Button2::isClicked() const {
    return clicked;
}