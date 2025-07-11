#include "SettingMenuState.h"
#include "SoundControoler.h"
#include "MenuState.h"
#include "ResourceManager.h"
#include "GameClock.h"
#include "GameState.h"
#include <iostream>

SettingMenuState::SettingMenuState(StateManager* manager)
    : State(manager),
    musicSlider({ 600.0f, 330.0f }, 400.0f, 0.0f, 1.0f, SoundController::getInstance().GetMusicVolume()),
    sfxSlider({ 600.0f, 460.0f }, 400.0f, 0.0f, 1.0f, SoundController::getInstance().GetSFXVolume())
{
    backButton = Rectangle(20, 20, 64, 64);
    goBackButton = Rectangle(20, 100, 64, 64);
    float rectX = 520.0f;
    float rectWidth = 64.0f;
    float rectHeight = 64.0f;
    musicRect = Rectangle{ rectX, 330.0f - rectWidth/2.0f, rectWidth, rectHeight};
    sfxRect = Rectangle{ rectX, 460.0f - rectWidth/2.0f, rectWidth, rectHeight};
}

void SettingMenuState::update() {
    float deltaTime = GameClock::getInstance().DeltaTime; // raylib function, returns seconds since last frame
    if (musicButtonCooldown > 0.0f) musicButtonCooldown -= deltaTime;
	else musicButtonCooldown = 0.0f;
    if (sfxButtonCooldown > 0.0f) sfxButtonCooldown -= deltaTime;
	else sfxButtonCooldown = 0.0f;


    musicSlider.update();
    sfxSlider.update();

    // Update sound volumes in real time
    SoundController::getInstance().SetMusicVolume(musicSlider.getRatio());
    SoundController::getInstance().SetSFXVolume(sfxSlider.getRatio());

    // Back button logic
    updateBackButton();

	// Music and SFX buttons logic
	updateMusicButton();
    updateSFXButton();

	// Go back button logic
    if (dynamic_cast<GameState*>(stateManager->getPreviousState()) != nullptr) {
        updateGoBackButton();
    }
}

void SettingMenuState::drawMusicSlider() {
    // Music slider
    const char* musicLabel = "Music Volume";
    int labelFontSize = 24;
    Vector2 musicLabelSize = MeasureTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), musicLabel, labelFontSize, 1.0f);
    float musicLabelY = 300;
    float musicSliderY = 330;
    float sliderWidth = 400;
    float sliderX = 600;
    DrawTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), musicLabel, { (1600 - musicLabelSize.x) / 2, labelFontSize + musicLabelY - labelFontSize }, labelFontSize, 1.0f, BLACK);
    musicSlider.Draw();

    // Draw music value (0-100) to the right of the slider, vertically centered with the track
    int musicValue = static_cast<int>(musicSlider.getRatio() * 100.0f + 0.5f);
    char musicValueText[8];
    snprintf(musicValueText, sizeof(musicValueText), "%d", musicValue);
    int valueFontSize = 28;
    Rectangle musicTrack = musicSlider.getTrackRect();
    float valueX = sliderX + sliderWidth + 20;
    float valueY = static_cast<int>(musicTrack.y + musicTrack.height / 2 - valueFontSize / 2);
    DrawTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), musicValueText, { valueX, valueY }, valueFontSize, 1.0f, BLACK);
}

void SettingMenuState::drawSFXSlider() {
    // SFX slider
    const char* sfxLabel = "SFX Volume";
    int labelFontSize = 24;
    Vector2 sfxLabelSize= MeasureTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), sfxLabel, labelFontSize, 1.0f);
    float sfxLabelY = 430;
    float sfxSliderY = 460;
    float sliderWidth = 400;
    float sliderX = 600;
    //DrawText(sfxLabel, (1600 - sfxLabelWidth) / 2, labelFontSize + sfxLabelY - labelFontSize, labelFontSize, DARKGRAY);
    DrawTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), sfxLabel, { (1600 - sfxLabelSize.x) / 2, labelFontSize + sfxLabelY - labelFontSize }, labelFontSize, 1.0f, BLACK);
    sfxSlider.Draw();

    // Draw SFX value (0-100) to the right of the slider, vertically centered with the track
    int sfxValue = static_cast<int>(sfxSlider.getRatio() * 100.0f + 0.5f);
    char sfxValueText[8];
    snprintf(sfxValueText, sizeof(sfxValueText), "%d", sfxValue);
    int valueFontSize = 28;
    Rectangle sfxTrack = sfxSlider.getTrackRect();
    float valueX = sliderX + sliderWidth + 20;
    float valueY = static_cast<int>(sfxTrack.y + sfxTrack.height / 2 - valueFontSize / 2);
    DrawTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), sfxValueText, { valueX, valueY }, valueFontSize, 1.0f, BLACK);
}

void SettingMenuState::draw() {
    //ClearBackground(RAYWHITE);
    Texture2D& bg = ResourceManager::getInstance().getTexture("SETTING_BACKGROUND");
    float screenWidth = static_cast<float>(GetScreenWidth());
    float screenHeight = static_cast<float>(GetScreenHeight());
    DrawTexturePro(
        bg,
        Rectangle{ 0, 0, static_cast<float>(bg.width), static_cast<float>(bg.height) },
        Rectangle{ 0, 0, screenWidth, screenHeight },
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );

    // Title
    const char* title = "Settings";
    int titleFontSize = 48;
    Vector2 titleSize = MeasureTextEx(ResourceManager::getInstance().getFonts("SETTING_FONT"), title, 48, 1.0f);
    float titleX = (1600 - titleSize.x) / 2;
    float titleY = 200; 
    //DrawText(title, titleX, titleY, titleFontSize, BLACK);
	DrawTextPro(ResourceManager::getInstance().getFonts("SETTING_FONT"), title, { titleX, titleY }, { 0, 0 }, 0.0f, titleFontSize, 1.0f, BLACK);
    
    // Music slider
	drawMusicSlider();
    // SFX slider
	drawSFXSlider();
    
    // Back button
    drawBackButton();

	// Music and SFX buttons
	drawMusicButton();
    drawSFXButton();

	// Back to previous state button
    if(dynamic_cast<GameState*>(stateManager->getPreviousState()) != nullptr) {
        drawGoBackButton();
	}
}

void SettingMenuState::updateBackButton() {
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, backButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        stateManager->setState(new MenuState(stateManager));
    }
}

void SettingMenuState::drawBackButton() {
    // Rectangle for the back button
    Rectangle backRect = backButton;

    // Get mouse state
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, backRect);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    // Select the correct texture
    const char* texKey = hovered ? "HOME_BUTTON_PRESS" : "HOME_BUTTON_RELEASE";
    Texture2D& tex = ResourceManager::getInstance().getTexture(texKey);

    // Draw the texture
        DrawTexturePro(
            tex,
            Rectangle{ 0, 0, (float)tex.width, (float)tex.height },
            backRect,
            Vector2{ 0, 0 },
            0.0f,
            WHITE
        );

     //std::cout << "Drawing " << texKey << ", id: " << tex.id << std::endl;
    // Optional: Draw a border/highlight
    //DrawRectangleLinesEx(backRect, 2, hovered ? ORANGE : DARKGRAY);
}

void SettingMenuState::updateMusicButton() {
    if (musicButtonCooldown > 0.0f) return;
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, musicRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Toggle music on/off
		auto& soundController = SoundController::getInstance();
        if (!soundController.IsMusicMuted()) {
            soundController.MuteMusic();
            musicSlider.setRatio(0.0f);
        }
        else {
			soundController.UnmuteMusic();
            musicSlider.setRatio(soundController.GetMusicVolume());
        }
        musicButtonCooldown = buttonCooldownTime;
	}
}

void SettingMenuState::drawMusicButton() {
    // Determine if the button is hovered or pressed
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, musicRect);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    // Determine if music is muted
    bool isMuted = SoundController::getInstance().IsMusicMuted();

    // Select the correct texture key
    const char* texKey = nullptr;
    if (!isMuted) {
        texKey = hovered ? "UNMUTE_BUTTON_PRESS" : "UNMUTE_BUTTON_RELEASE";
    }
    else {
        texKey = hovered ? "MUTE_BUTTON_PRESS" : "MUTE_BUTTON_RELEASE";
    }

    // Get the texture
    Texture2D& tex = ResourceManager::getInstance().getTexture(texKey);

    // Draw the texture in the button rectangle
    DrawTexturePro(
        tex,
        Rectangle{ 0, 0, (float)tex.width, (float)tex.height },
        musicRect,
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );
}

void SettingMenuState::updateSFXButton() {
    if (musicButtonCooldown > 0.0f) return;
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, sfxRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Toggle music on/off
        auto& soundController = SoundController::getInstance();
        if (!soundController.IsSFXMuted()) {
            soundController.MuteSFX();
			sfxSlider.setRatio(0.0f);
        }
        else {
            soundController.UnmuteSFX();
			sfxSlider.setRatio(soundController.GetSFXVolume());
        }
        musicButtonCooldown = buttonCooldownTime;
    }
}

void SettingMenuState::drawSFXButton() {
    // Determine if the button is hovered or pressed
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, sfxRect);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    // Determine if music is muted
    bool isMuted = SoundController::getInstance().IsSFXMuted();

    // Select the correct texture key
    const char* texKey = nullptr;
    if (!isMuted) {
        texKey = hovered ? "UNMUTE_BUTTON_PRESS" : "UNMUTE_BUTTON_RELEASE";
    }
    else {
        texKey = hovered ? "MUTE_BUTTON_PRESS" : "MUTE_BUTTON_RELEASE";
    }

    // Get the texture
    Texture2D& tex = ResourceManager::getInstance().getTexture(texKey);

    // Draw the texture in the button rectangle
    DrawTexturePro(
        tex,
        Rectangle{ 0, 0, (float)tex.width, (float)tex.height },
        sfxRect,
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );
}

void SettingMenuState::updateGoBackButton() {
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, goBackButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        stateManager->goBack();
	}
}

void SettingMenuState::drawGoBackButton() {
    // Rectangle for the go back button
    Rectangle goBackRect = goBackButton;
    // Get mouse state
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, goBackRect);
    bool pressed = hovered && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    // Select the correct texture
    const char* texKey = hovered ? "BACK_BUTTON_PRESS" : "BACK_BUTTON_RELEASE";
    Texture2D& tex = ResourceManager::getInstance().getTexture(texKey);
    // Draw the texture
    DrawTexturePro(
        tex,
        Rectangle{ 0, 0, (float)tex.width, (float)tex.height },
        goBackRect,
        Vector2{ 0, 0 },
        0.0f,
        WHITE
    );
    // Optional: Draw a border/highlight
	//DrawRectangleLinesEx(goBackRect, 2, hovered ? ORANGE : DARKGRAY);
}
SettingMenuState::~SettingMenuState() {
}