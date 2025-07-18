#include "SoundControoler.h"
#include "ResourceManager.h"
#include <algorithm>

SoundController& SoundController::getInstance(){
    static SoundController instance;
    return instance;
}
void SoundController::PlaySound(const std::string& name)
{
    ::PlaySound(ResourceManager::getInstance().getSounds(name));
    registeredSounds[name] = &ResourceManager::getInstance().getSounds(name);

    ::SetSoundVolume(*registeredSounds[name], sfxVolume);
}

void SoundController::PlayMusic(const std::string & music)
{
    PlayMusicStream(ResourceManager::getInstance().getMusics(music));
    registeredMusics[music] = &ResourceManager::getInstance().getMusics(music);

    ::SetMusicVolume(*registeredMusics[music], musicVolume);
}




void SoundController::StopAllSounds()
{
    // For sounds
    for(auto it = registeredSounds.begin(); it != registeredSounds.end();)
    {
        StopSound(*it->second);
        it = registeredSounds.erase(it);  // erase() returns next valid iterator
    }
    
    // For music
    for(auto it = registeredMusics.begin(); it != registeredMusics.end();)
    {
        StopMusicStream(*it->second);
        it = registeredMusics.erase(it);  // erase() returns next valid iterator
    }
}

void SoundController::UpdateSoundStream()
{
    for(auto& pair : registeredMusics)
    {
        UpdateMusicStream(*pair.second);
    }
}

void SoundController::SetSFXVolume(float volume) {
    sfxVolume = std::clamp(volume, 0.0f, 1.0f);
    for (auto& pair : registeredSounds) {
        ::SetSoundVolume(*pair.second, sfxVolume);
    }
}

void SoundController::SetMusicVolume(float volume) {
    musicVolume = std::clamp(volume, 0.0f, 1.0f);
    for (auto& pair : registeredMusics) {
        ::SetMusicVolume(*pair.second, musicVolume);
    }
}

float SoundController::GetSFXVolume() const {
    return sfxVolume;
}

float SoundController::GetMusicVolume() const {
    return musicVolume;
}

void SoundController::MuteMusic() {
    if (!musicMuted) {
        prevMusicVolume = musicVolume;
        SetMusicVolume(0.0f);
        musicMuted = true;
    }
}

void SoundController::UnmuteMusic() {
    if (musicMuted) {
        SetMusicVolume(prevMusicVolume);
        musicMuted = false;
    }
}

void SoundController::MuteSFX() {
    if (!sfxMuted) {
        prevSFXVolume = sfxVolume;
        SetSFXVolume(0.0f);
        sfxMuted = true;
    }
}

void SoundController::UnmuteSFX() {
    if (sfxMuted) {
        SetSFXVolume(prevSFXVolume);
        sfxMuted = false;
    }
}

bool SoundController::IsMusicMuted() const {
    return musicMuted || musicVolume <= 0.0001f;
}

bool SoundController::IsSFXMuted() const {
    return sfxMuted || sfxVolume <= 0.0001f;
}
