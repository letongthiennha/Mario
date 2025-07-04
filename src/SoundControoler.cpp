#include "SoundControoler.h"
#include "ResourceManager.h"
SoundController& SoundController::getInstance(){
    static SoundController instance;
    return instance;
}
void SoundController::PlaySound(const std::string& name)
{
    ::PlaySound(ResourceManager::getInstance().getSounds(name));
    registeredSounds[name] = &ResourceManager::getInstance().getSounds(name);

}

void SoundController::PlayMusic(const std::string & music)
{
    PlayMusicStream(ResourceManager::getInstance().getMusics(music));
    registeredMusics[music] = &ResourceManager::getInstance().getMusics(music);
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
