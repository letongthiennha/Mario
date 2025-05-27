#pragma once
#include "raylib.h"

class GameClock
{
private:
    static constexpr double FIXED_TIME_STEP=1/360.0;

public:
    static double updateTimeAcum;
    static const double GetUpdateDeltaTime();
};