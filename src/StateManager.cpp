#include "StateManager.h"
#include "MenuState.h"
StateManager::StateManager() : currentState(new MenuState(this)) {
    // Initialize with a default state, e.g., MenuState
}

StateManager::~StateManager()
{
    if (currentState) {
        delete currentState;  // Clean up the current state
    }
    currentState = nullptr;  // Set to nullptr to avoid dangling pointer
}

void StateManager::setState(State *newState)
{
    if (currentState) {
        currentState->Exit();  // Call Exit on the current state
        delete currentState;  // Clean up the previous state
    }
    currentState = newState;  // Set the new state
    if (currentState) {
        currentState->Enter();  // Call Enter on the new state
    }
}

void StateManager::update()
{
    if (currentState) {
        currentState->update();  // Update the current state
    }
}
void StateManager::draw()
{
    if (currentState) {
        currentState->draw();  // Draw the current state
    }
}

