#include "ResourceManager.h"
std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound> ResourceManager::sounds;
std::unordered_map<std::string, Music> ResourceManager::musics;

//Load
void ResourceManager::loadTextures()
{
    //Mario
    textures["SMALL_MARIO_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMario_0.png");
    textures["SMALL_MARIO_1_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMario_1.png");
    textures["SMALL_MARIO_0_LEFT"]=  FlipTextureHorizontal(textures["SMALL_MARIO_0_RIGHT"]);
    textures["SMALL_MARIO_1_LEFT"]=  FlipTextureHorizontal(textures["SMALL_MARIO_1_RIGHT"]);

    textures["SMALL_MARIO_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMarioFalling_0.png");
    textures["SMALL_MARIO_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_FALLING_0_RIGHT"]);
    
    textures["SMALL_MARIO_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMarioJumping_0.png");
    textures["SMALL_MARIO_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_JUMPING_0_RIGHT"]);
}

void ResourceManager::loadSounds(){

}

void ResourceManager::loadMusics(){

}

void ResourceManager::loadResource(){
    loadTextures();
    loadMusics();
    loadSounds();
}
//Unload
void ResourceManager::unloadTexture(){
    for(auto&pair :textures)
        UnloadTexture(pair.second);
}

void ResourceManager::unloadSounds(){
    for(auto&pair :sounds)
    UnloadSound(pair.second);
}

void ResourceManager::unloadMusics(){
    for(auto&pair :musics)
    UnloadMusicStream(pair.second);
}

void ResourceManager::unloadResource(){
    unloadTexture();
    unloadSounds();
    unloadMusics();
}
//Getters
Texture2D& ResourceManager::getTexture( std::string name){
    return textures[name];
}
Sound &ResourceManager::getSounds( std::string name){
    return sounds[name];
}
Music &ResourceManager::getMusics( std::string name){
    return musics[name];
}

Texture2D FlipTextureHorizontal(const Texture2D &texture)
{
    Image img = LoadImageFromTexture(texture);
    ImageFlipHorizontal(&img);
    Texture2D flip = LoadTextureFromImage(img);
    return flip;
}
