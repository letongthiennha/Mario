#include "ResourceManager.h"
std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound> ResourceManager::sounds;
std::unordered_map<std::string, Music> ResourceManager::musics;

void ResourceManager::loadTexture()
{
    //Mario
    textures["smallMario0Left"] = LoadTexture("resources/Character/Mario/SmallMario_0.png");
}

Texture2D& ResourceManager::getTexture(const std::string &name){
    return textures[name];
}
void ResourceManager::loadResource(){
    loadTexture();
}