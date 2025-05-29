#include "SoundControoler.h"
#include "ResourceManager.h"
SoundController *SoundController::instance = nullptr;
SoundController& SoundController::getInstance(){
    if(!instance){
        instance = new SoundController;
    }
    return *instance;
}
void SoundController::PlaySound(const std::string& name)
{
    ::PlaySound(ResourceManager::getInstance().getSounds(name));

}
SoundController::~SoundController()
{
    instance = nullptr;
}