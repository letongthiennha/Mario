#include "MenuState.h"
#include "ResourceManager.h"
#include "GameState.h"
#include <iostream>
MenuState::MenuState(StateManager*manager): State(manager),
    startButton(Vector2{1050, 350}, Vector2{400, 150}, "", &ResourceManager::getInstance().getTexture("MENU_STATE_START_BUTTON"), WHITE, LIGHTGRAY, DARKGRAY),
    optionsButton(Vector2{1050, 550}, Vector2{400, 150}, "", &ResourceManager::getInstance().getTexture("MENU_STATE_OPTIONS_BUTTON"), WHITE, LIGHTGRAY, DARKGRAY),
    exitButton(Vector2{100, 750}, Vector2{100, 100}, "", &ResourceManager::getInstance().getTexture("EXIT_BUTTON"), WHITE, LIGHTGRAY, RED),
    creditsButton(Vector2{1350, 750}, Vector2{100, 100}, "Credits", nullptr, WHITE, LIGHTGRAY, RED, BLACK, WHITE, RED)
    , backgroundTexture(&ResourceManager::getInstance().getTexture("MENU_STATE_BACKGROUND"))
    {
        startButton.OffBackground();
        startButton.fitTexture();
        optionsButton.fitTexture();
        optionsButton.OffBackground();

        exitButton.OffBackground();
        exitButton.fitTexture();
        creditsButton.OffBackground();
        creditsButton.setTextSize(50);

}

MenuState::~MenuState()
{
}

void MenuState::update()
{
    startButton.update();
    if (startButton.isClicked()) {

        stateManager->setState(new GameState(stateManager));  // Switch to GameState
    }
    // Update other buttons similarly
    optionsButton.update();
    if (optionsButton.isClicked()) {
        // Handle options button click
        std::cout << "Options button clicked!" << std::endl;
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
