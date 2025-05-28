#include "ResourceManager.h"
std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound> ResourceManager::sounds;
std::unordered_map<std::string, Music> ResourceManager::musics;

//Load
void ResourceManager::loadTextures()
{
    //SMALL MARIO
    {
    textures["SMALL_MARIO_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMario_0.png");
    textures["SMALL_MARIO_1_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMario_1.png");
    textures["SMALL_MARIO_0_LEFT"]=  FlipTextureHorizontal(textures["SMALL_MARIO_0_RIGHT"]);
    textures["SMALL_MARIO_1_LEFT"]=  FlipTextureHorizontal(textures["SMALL_MARIO_1_RIGHT"]);

    textures["SMALL_MARIO_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMarioFalling_0.png");
    textures["SMALL_MARIO_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_FALLING_0_RIGHT"]);
    
    textures["SMALL_MARIO_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMarioJumping_0.png");
    textures["SMALL_MARIO_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_JUMPING_0_RIGHT"]);

    textures["SMALL_MARIO_VICTORY"] = LoadTexture("resources/Entity/Mario/SmallMarioVictory_0.png");
    };
    //BIG MARIO
    {
    textures["SUPER_MARIO_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SuperMario_0.png");
    textures["SUPER_MARIO_1_RIGHT"] = LoadTexture("resources/Entity/Mario/SuperMario_1.png");
    textures["SUPER_MARIO_2_RIGHT"] = LoadTexture("resources/Entity/Mario/SuperMario_2.png");
    textures["SUPER_MARIO_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_MARIO_0_RIGHT"]);
    textures["SUPER_MARIO_1_LEFT"] = FlipTextureHorizontal(textures["SUPER_MARIO_1_RIGHT"]);
    textures["SUPER_MARIO_2_LEFT"] = FlipTextureHorizontal(textures["SUPER_MARIO_2_RIGHT"]);

    textures["SUPER_MARIO_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SuperMarioJumping_0.png");
    textures["SUPER_MARIO_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_MARIO_JUMPING_0_RIGHT"]);
    textures["SUPER_MARIO_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SuperMarioFalling_0.png");
    textures["SUPER_MARIO_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_MARIO_FALLING_0_RIGHT"]);

    textures["SUPER_MARIO_DUCKING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SuperMarioDucking_0.png");
    textures["SUPER_MARIO_DUCKING_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_MARIO_DUCKING_0_RIGHT"]);

    
    textures["SUPER_MARIO_VICTORY"] = LoadTexture("resources/Entity/Mario/SuperMarioVictory_0.png");

    textures["TRANSITIONING_MARIO_0_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_0.png");
    textures["TRANSITIONING_MARIO_0_LEFT"] = FlipTextureHorizontal(textures["TRANSITIONING_MARIO_0_RIGHT"]);
    textures["TRANSITIONING_MARIO_1_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_1.png");
    textures["TRANSITIONING_MARIO_1_LEFT"] = FlipTextureHorizontal(textures["TRANSITIONING_MARIO_1_RIGHT"]);
    textures["TRANSITIONING_MARIO_2_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_2.png");
    textures["TRANSITIONING_MARIO_2_LEFT"] = FlipTextureHorizontal(textures["TRANSITIONING_MARIO_2_RIGHT"]);
    //FIRE MARIO
    textures["FIRE_MARIO_0_RIGHT"] = LoadTexture("resources/Entity/Mario/FireMario_0.png");
    textures["FIRE_MARIO_1_RIGHT"] = LoadTexture("resources/Entity/Mario/FireMario_1.png");
    textures["FIRE_MARIO_2_RIGHT"] = LoadTexture("resources/Entity/Mario/FireMario_2.png");
    textures["FIRE_MARIO_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_MARIO_0_RIGHT"]);
    textures["FIRE_MARIO_1_LEFT"] = FlipTextureHorizontal(textures["FIRE_MARIO_1_RIGHT"]);
    textures["FIRE_MARIO_2_LEFT"] = FlipTextureHorizontal(textures["FIRE_MARIO_2_RIGHT"]);

    textures["FIRE_MARIO_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/FireMarioJumping_0.png");
    textures["FIRE_MARIO_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_MARIO_JUMPING_0_RIGHT"]);
    textures["FIRE_MARIO_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/FireMarioFalling_0.png");
    textures["FIRE_MARIO_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_MARIO_FALLING_0_RIGHT"]);

    textures["FIRE_MARIO_DUCKING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/FireMario_Ducking_0.png");
    textures["FIRE_MARIO_DUCKING_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_MARIO_DUCKING_0_RIGHT"]);
    textures["FIRE_MARIO_VICTORY"] = LoadTexture("resources/Entity/Mario/FireMarioVictory_0.png");
    };

    //FIRE BALL
    {
    textures["FIRE_BALL_0_RIGHT"] = LoadTexture("resources/Entity/Fireball/Fireball_0.png");
    textures["FIRE_BALL_1_RIGHT"] = LoadTexture("resources/Entity/Fireball/Fireball_1.png");
    textures["FIRE_BALL_2_RIGHT"] = LoadTexture("resources/Entity/Fireball/Fireball_2.png");
    textures["FIRE_BALL_3_RIGHT"] = LoadTexture("resources/Entity/Fireball/Fireball_3.png");
    textures["FIRE_BALL_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_BALL_0_RIGHT"]);
    textures["FIRE_BALL_1_LEFT"] = FlipTextureHorizontal(textures["FIRE_BALL_1_RIGHT"]);
    textures["FIRE_BALL_2_LEFT"] = FlipTextureHorizontal(textures["FIRE_BALL_2_RIGHT"]);
    textures["FIRE_BALL_3_LEFT"] = FlipTextureHorizontal(textures["FIRE_BALL_3_RIGHT"]);
    }
    //BACKGROUND
    {
    textures["BACKGROUND_0"] = LoadTexture("resources/Background/background1.png");
    }
    //TILE
    textures["MAP_0_TILE_A"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_A.png");
    textures["MAP_0_TILE_B"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_B.png");
    textures["MAP_0_TILE_C"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_C.png");
    textures["MAP_0_TILE_D"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_D.png");
    textures["MAP_0_TILE_E"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_E.png");
    textures["MAP_0_TILE_F"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_F.png");
    textures["MAP_0_TILE_G"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_G.png");
    textures["MAP_0_TILE_H"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_H.png");
    textures["MAP_0_TILE_I"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_I.png");
    textures["MAP_0_TILE_J"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_J.png");
    textures["MAP_0_TILE_K"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_K.png");
    textures["MAP_0_TILE_L"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_L.png");
    textures["MAP_0_TILE_M"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_M.png");
    textures["MAP_0_TILE_N"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_N.png");
    textures["MAP_0_TILE_O"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_O.png");
    textures["MAP_0_TILE_P"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_P.png");
    textures["MAP_0_TILE_Q"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_Q.png");
    textures["MAP_0_TILE_R"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_R.png");
    textures["MAP_0_TILE_S"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_S.png");
    textures["MAP_0_TILE_T"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_T.png");
    textures["MAP_0_TILE_U"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_U.png");
    textures["MAP_0_TILE_V"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_V.png");
    textures["MAP_0_TILE_W"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_W.png");
    textures["MAP_0_TILE_X"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_X.png");
    textures["MAP_0_TILE_Y"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_Y.png");
    textures["MAP_0_TILE_Z"] = LoadTexture("resources/Entity/Tiles/Map 0/tile_Z.png");
    {
    textures["MAP_1_TILE_A"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_A.png");
    textures["MAP_1_TILE_B"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_B.png");
    textures["MAP_1_TILE_C"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_C.png");
    textures["MAP_1_TILE_D"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_D.png");
    textures["MAP_1_TILE_E"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_E.png");
    textures["MAP_1_TILE_F"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_F.png");
    }
    
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
