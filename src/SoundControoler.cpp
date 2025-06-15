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
