#pragma once
#include "raylib.h"
#include<string>
class SoundController {
    private:

    SoundController() = default;
    ~SoundController() = default;

    SoundController(const SoundController&) = delete;
    SoundController& operator=(const SoundController&) = delete;
public:
    static SoundController &getInstance();
    void PlaySound(const std::string&);
    void StopSound(const std::string&);
};