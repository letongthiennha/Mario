#pragma once
#include "raylib.h"
#include<string>
#include <unordered_map>
class SoundController {
    private:

    SoundController() = default;
    ~SoundController() = default;

    SoundController(const SoundController&) = delete;
    SoundController& operator=(const SoundController&) = delete;
    std::unordered_map<std::string, Sound*> registeredSounds;
    std::unordered_map<std::string, Music*> registeredMusics;
public:
    static SoundController &getInstance();
    void PlaySound(const std::string&);

    void PlayMusic(const std::string&);
    void PauseMusic(const std::string&);
    void StopAllSounds();
    void UpdateSoundStream();
};