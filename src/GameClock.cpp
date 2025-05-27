#include "GameClock.h"
double GameClock::updateTimeAcum = 0.0;


const double GameClock::GetUpdateDeltaTime()
{
    return FIXED_TIME_STEP;
}

