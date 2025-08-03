#pragma once

#include "StateManager.h"
#include "Slider.h"
#include "raylib.h"
#include "Button2.h"
#include <map>  

class SettingMenuState : public State {
public:
    SettingMenuState(StateManager* manager);

    void update() override;
    void draw() override;

	void drawMusicSlider();
	void drawSFXSlider();

    void updateMusicButton();
	void drawMusicButton();

	void updateSFXButton();
	void drawSFXButton();

	void updateGoBackButton();
	void drawGoBackButton();

    void updateBackGround();
    void drawBackGround();

	void DrawConfirmationBox();
	void UpdateConfirmationBox();

    ~SettingMenuState();
private:
    enum class ConfirmationState {
        NONE,
        VISIBLE
    };

    Slider musicSlider;
    Slider sfxSlider;

    Button2 homeButton;
    Button2 saveButton;
    Button2 resumeButton;
    Rectangle goBackButton;
    Rectangle musicRect;
    Rectangle sfxRect;

    ConfirmationState confirmationState;
    Button2 yesButton;
	Button2 noButton;
    bool isSaved = false;

    float musicButtonCooldown = 0.0f;
	float sfxButtonCooldown = 0.0f;
	float buttonCooldownTime = 0.5f; // Cooldown time in seconds

    Texture2D* mapBg;
    float mapBgScrollX = 0.0f;
};