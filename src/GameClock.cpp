#include "GameClock.h"
double GameClock::previousUpdateTime = 0.0;
double GameClock::updateTimeAcum = 0.0;

void GameClock::startClock(){
    previousUpdateTime = GetTime();
}
const double GameClock::GetUpdateDeltaTime()
{
    return GetTime()-previousUpdateTime;
}

void GameClock::update(){
    previousUpdateTime = GetTime();
}