#include "MenuState.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "SoundController.h"
#include "SettingMenuState.h"
#include <iostream>
MenuState::MenuState(StateManager*manager): State(manager),
    startButton(Vector2{1050, 350}, Vector2{400, 150}),
    optionsButton(Vector2{1050, 550}, Vector2{400, 150}),
    exitButton(Vector2{100, 750}, Vector2{100, 100}),
    creditsButton(Vector2{1350, 750}, Vector2{100, 100})
    , backgroundTexture(&ResourceManager::getInstance().getTexture("MENU_STATE_BACKGROUND"))
    {
        startButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("MENU_STATE_START_BUTTON"))
            .DisableBackground()
            .fitTexture();
        optionsButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("MENU_STATE_OPTIONS_BUTTON"))
            .DisableBackground()
            .fitTexture();

        exitButton.setPrimaryTexture(ResourceManager::getInstance().getTexture("MENU_STATE_EXIT_BUTTON"))
            .DisableBackground()
            .fitTexture();
        creditsButton.DisableBackground()
            .setText("Credits")
            .setTextSize(50)
            .setTextActiveColor(RED);
        SoundController::getInstance().StopAllSounds();  // Stop all sounds when entering the menu state
        SoundController::getInstance().PlayMusic("TITLE_BACKGROUND_MUSIC");  // Play the
}

MenuState::~MenuState()
{
}

void MenuState::update()
{
    startButton.update();
    if (startButton.isClicked()) {

        stateManager->setState(new GameState(stateManager));  // Switch to GameState
        return;
    }
    // Update other buttons similarly
    optionsButton.update();
    if (optionsButton.isClicked()) {
        // Handle options button click
        stateManager->setState(new SettingMenuState(stateManager));
        //std::cout << "Options button clicked!" << std::endl;
        return;
    }
    exitButton.update();
    if (exitButton.isClicked()) {
        // Handle exit button click
        std::cout << "Exit button clicked!" << std::endl;
    }
    creditsButton.update();
    if (creditsButton.isClicked()) {
        // Handle credits button click
        std::cout << "Credits button clicked!" << std::endl;
    }

    
}

void MenuState::draw()
{
    DrawTextureNPatch(*backgroundTexture, NPatchInfo{Rectangle{0, 0, (float)backgroundTexture->width, (float)backgroundTexture->height}, 10, 10, 10, 10}, Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0},0, WHITE);
    startButton.Draw();  // Draw the start button
    optionsButton.Draw();  // Draw the options button
    exitButton.Draw();  // Draw the exit button
    creditsButton.Draw();  // Draw the credits button
}
