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

    float sfxVolume = 1.0f;
    float musicVolume = 1.0f;
    float prevMusicVolume = 1.0f;
    float prevSFXVolume = 1.0f;
    bool musicMuted = false;
    bool sfxMuted = false;
public:
    static SoundController &getInstance();
    void PlaySound(const std::string&);

    void PlayMusic(const std::string&);
    void PauseMusic(const std::string&);
    void StopAllSounds();
    void UpdateSoundStream();

    void SetSFXVolume(float volume);
    void SetMusicVolume(float volume);
    float GetSFXVolume() const;
    float GetMusicVolume() const;

    void MuteMusic();
    void UnmuteMusic();
    void MuteSFX();
    void UnmuteSFX();
    bool IsMusicMuted() const;
    bool IsSFXMuted() const;
};