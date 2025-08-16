#pragma once
#include "State.h"
#include "MenuState.h"
#include "Coin.h"
#include <vector>
class CreditState : public State {
private:
    Button SkipButton;
    std::vector<Coin*> coins;
public:
    CreditState(StateManager *manager);
    ~CreditState() ;


    void update() override;
    void draw() override;
};