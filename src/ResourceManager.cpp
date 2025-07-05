#include "../include/ResourceManager.h"
#include <iostream>
std::unordered_map<std::string, Texture2D> ResourceManager::textures;
std::unordered_map<std::string, Sound> ResourceManager::sounds;
std::unordered_map<std::string, Music> ResourceManager::musics;

//Load
void ResourceManager::loadTextures() {

    // ────────────────────────────────
    // SMALL MARIO
    // ────────────────────────────────
    {
        textures["SMALL_MARIO_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMario_0.png");
        textures["SMALL_MARIO_1_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMario_1.png");
        textures["SMALL_MARIO_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_0_RIGHT"]);
        textures["SMALL_MARIO_1_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_1_RIGHT"]);

        textures["SMALL_MARIO_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMarioFalling_0.png");
        textures["SMALL_MARIO_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_FALLING_0_RIGHT"]);

        textures["SMALL_MARIO_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Mario/SmallMarioJumping_0.png");
        textures["SMALL_MARIO_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_MARIO_JUMPING_0_RIGHT"]);

        textures["SMALL_MARIO_VICTORY"] = LoadTexture("resources/Entity/Mario/SmallMarioVictory_0.png");
    }

    // ────────────────────────────────
    // BIG MARIO
    // ────────────────────────────────
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
    }

    // ────────────────────────────────
    // FIRE MARIO
    // ────────────────────────────────
    {
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
    }

    // ────────────────────────────────
    // FIREBALL
    // ────────────────────────────────
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

    // ────────────────────────────────
    // TILES
    // ────────────────────────────────
    {
        textures["MAP1_GRASS_NORMAL"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_B.png");
        textures["MAP1_GRASS_RIGHT_EDGE"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_E.png");
        textures["MAP1_GRASS_LEFT_EDGE"] = LoadTexture("resources/Entity/Tiles/Map 1/tile_F.png");
    }

    // ────────────────────────────────
    // GOOMBA
    // ────────────────────────────────
{
    std::cout << "Loading: resources/Entity/Monsters/Goomba/Goomba_0.png" << std::endl;
    textures["GOOMBA_0_RIGHT"] = LoadTexture("resources/Entity/Monsters/Goomba/Goomba_0.png");
    textures["GOOMBA_0_LEFT"] = FlipTextureHorizontal(textures["GOOMBA_0_RIGHT"]);
    std::cout << "Loading: resources/Entity/Monsters/Goomba/Goomba_1.png" << std::endl;
    textures["GOOMBA_1_RIGHT"] = LoadTexture("resources/Entity/Monsters/Goomba/Goomba_1.png");
    textures["GOOMBA_1_LEFT"] = FlipTextureHorizontal(textures["GOOMBA_1_RIGHT"]);
}
    // ────────────────────────────────
    // FLYING GOOMBA
    // ────────────────────────────────
    {
    std::cout << "Loading: FlyingGoomba textures..." << std::endl;

    textures["flyingGoomba0R"] = LoadTexture("resources/Entity/Monsters/FlyingGoomba/FlyingGoomba_0.png");
    textures["flyingGoomba1R"] = LoadTexture("resources/Entity/Monsters/FlyingGoomba/FlyingGoomba_1.png");
    textures["flyingGoomba2R"] = LoadTexture("resources/Entity/Monsters/FlyingGoomba/FlyingGoomba_2.png");
    textures["flyingGoomba3R"] = LoadTexture("resources/Entity/Monsters/FlyingGoomba/FlyingGoomba_3.png");

    textures["flyingGoomba0L"] = FlipTextureHorizontal(textures["flyingGoomba0R"]);
    textures["flyingGoomba1L"] = FlipTextureHorizontal(textures["flyingGoomba1R"]);
    textures["flyingGoomba2L"] = FlipTextureHorizontal(textures["flyingGoomba2R"]);
    textures["flyingGoomba3L"] = FlipTextureHorizontal(textures["flyingGoomba3R"]);
    }
    // ────────────────────────────────
    // BLUE KOOPA TROOPA
    // ────────────────────────────────
    {
        std::cout << "Loading: BlueKoopaTroopa textures..." << std::endl;
        textures["BLUE_KOOPA_0_RIGHT"] = LoadTexture("resources/Entity/Monsters/BlueKoopaTroopa/BlueKoopaTroopa_0.png");
        textures["BLUE_KOOPA_1_RIGHT"] = LoadTexture("resources/Entity/Monsters/BlueKoopaTroopa/BlueKoopaTroopa_1.png");
        textures["BLUE_KOOPA_0_LEFT"] = FlipTextureHorizontal(textures["BLUE_KOOPA_0_RIGHT"]);
        textures["BLUE_KOOPA_1_LEFT"] = FlipTextureHorizontal(textures["BLUE_KOOPA_1_RIGHT"]);
    }
    // PIRANHA PLANT
    {
        std::cout << "Loading: PiranhaPlant textures..." << std::endl;
        textures["PIRANHA_0"] = LoadTexture("resources/Entity/Monsters/PiranhaPlant/PiranhaPlant_0.png");
        textures["PIRANHA_1"] = LoadTexture("resources/Entity/Monsters/PiranhaPlant/PiranhaPlant_1.png");
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
