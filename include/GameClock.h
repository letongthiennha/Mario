#pragma once
#include "raylib.h"

class GameClock
{
private:
    static GameClock *instance ;

    GameClock() = default;
    ~GameClock() = default;
public:
    static  GameClock &getInstance();
    double updateTimeAcum;
    const double FIXED_TIME_STEP=1/360.0;

};