#pragma once
#include "raylib.h"

class GameClock
{
private:
   static double previousUpdateTime;

public:
    static constexpr double FIXED_TIME_STEP=1/360.0;
    static double updateTimeAcum;
    static void startClock();
    static const double GetUpdateDeltaTime();
    static void update();
};