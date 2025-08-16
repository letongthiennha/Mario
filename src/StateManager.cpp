#include "StateManager.h"
#include "MenuState.h"
#include "GameState.h"
#include "CharacterSelectionState.h"
StateManager::StateManager() : currentState(new MenuState(this)), previousState(nullptr) {
    // Initialize with a default state, e.g., MenuState
}

StateManager::~StateManager()
{
    if (currentState) {
        delete currentState;  // Clean up the current state
    }
    currentState = nullptr;  // Set to nullptr to avoid dangling pointer
    
    if (previousState) {
		delete previousState;  // Clean up the previous state
    }
	previousState = nullptr;  // Set to nullptr to avoid dangling pointer
}

void StateManager::setState(State *newState)
{
    if (currentState) {
        currentState->Exit();  // Call Exit on the current state
		if (previousState) delete previousState;  // Clean up the previous state
		previousState = currentState;  // Save the current state as previous
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


    if (currentState!=nullptr) {
        if(dynamic_cast<MenuState*>(currentState)) {
            ClearBackground(WHITE);  // Clear background for MenuState
        }
       currentState->draw();  // Draw the current state
    }
}

 State* StateManager::getPreviousState() const 
 { return previousState; }

 void StateManager::goBack() {
     if (!previousState) return;

     // Call Exit on the current state
     if (currentState) currentState->Exit();

     // Swap current and previous
     State* temp = currentState;
     currentState = previousState;
     previousState = temp;
 }
