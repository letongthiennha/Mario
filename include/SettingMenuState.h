#pragma once

#include "StateManager.h"
#include "Slider.h"
#include "raylib.h"
#include "Button.h"
#include <map>

class SettingMenuState : public State {
public:
    SettingMenuState(StateManager* manager);

    void update() override;
    void draw() override;

	void drawMusicSlider();
	void drawSFXSlider();

    void updateBackButton();
    void drawBackButton();

    void updateMusicButton();
	void drawMusicButton();

	void updateSFXButton();
	void drawSFXButton();

	void updateGoBackButton();
	void drawGoBackButton();

    void updateBackGround();
    void drawBackGround();

    ~SettingMenuState();
private:

    Slider musicSlider;
    Slider sfxSlider;

    Rectangle backButton;
    Rectangle goBackButton;
    Rectangle musicRect;
    Rectangle sfxRect;

    float musicButtonCooldown = 0.0f;
	float sfxButtonCooldown = 0.0f;
	float buttonCooldownTime = 0.5f; // Cooldown time in seconds

    Texture2D* mapBg;
    float mapBgScrollX = 0.0f;
};