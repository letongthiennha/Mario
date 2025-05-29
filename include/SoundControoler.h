#pragma once
#include "raylib.h"
#include<string>
class SoundController {
    private:
    static SoundController *instance;

    SoundController() = default;
    ~SoundController() ;


public:
    static SoundController &getInstance();
    void PlaySound(const std::string&);
    void StopSound(const std::string&);
};