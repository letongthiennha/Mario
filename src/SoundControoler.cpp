#include "SoundControoler.h"
#include "ResourceManager.h"
SoundController& SoundController::getInstance(){
    static SoundController instance;
    return instance;
}
void SoundController::PlaySound(const std::string& name)
{
    ::PlaySound(ResourceManager::getInstance().getSounds(name));

}

void SoundController::PlayMusic(const std::string & music)
{
    PlayMusicStream(ResourceManager::getInstance().getMusics(music));
}

void SoundController::StopMusic(const std::string &)
{
    StopMusicStream(ResourceManager::getInstance().getMusics("Test"));
}

void SoundController::PauseMusic(const std::string &)
{
    PauseMusicStream(ResourceManager::getInstance().getMusics("Test"));
}
