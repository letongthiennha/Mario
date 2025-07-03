#include "ResourceManager.h"

void ResourceManager::loadFonts()
{
    fonts["HUD_FONT"] = LoadFont("resources/Font/HudFont.otf");
    fonts["SUPER_MARIO_WORLD_FONT"] = LoadFont("resources/Font/SuperMarioWorld.ttf");
}

// Load
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

    textures["SMALL_MARIO_DYING"]= LoadTexture("resources/Entity/Mario/SmallMarioDying_0.png");
    };
    //Transform small to big
    {
    textures["MARIO_TRANSFORM_SMALL_TO_BIG_0_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_0.png");
    textures["MARIO_TRANSFORM_SMALL_TO_BIG_0_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_SMALL_TO_BIG_0_RIGHT"]);
    textures["MARIO_TRANSFORM_SMALL_TO_BIG_1_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_1.png");
    textures["MARIO_TRANSFORM_SMALL_TO_BIG_1_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_SMALL_TO_BIG_1_RIGHT"]);
    textures["MARIO_TRANSFORM_SMALL_TO_BIG_2_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_2.png");
    textures["MARIO_TRANSFORM_SMALL_TO_BIG_2_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_SMALL_TO_BIG_2_RIGHT"]);
    }
    //Transform small to fire
    {
    textures["MARIO_TRANSFORM_SMALL_TO_FIRE_0_RIGHT"] = LoadTexture("resources/Entity/Mario/TransitioningMario_0.png");
    textures["MARIO_TRANSFORM_SMALL_TO_FIRE_0_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_SMALL_TO_FIRE_0_RIGHT"]);
    textures["MARIO_TRANSFORM_SMALL_TO_FIRE_1_RIGHT"] = LoadTexture("resources/Entity/Mario/TrasitioningFireMario.png");
    textures["MARIO_TRANSFORM_SMALL_TO_FIRE_1_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_SMALL_TO_FIRE_1_RIGHT"]);
    textures["MARIO_TRANSFORM_SMALL_TO_FIRE_2_RIGHT"] = LoadTexture("resources/Entity/Mario/TrasitioningFireMario_2.png");
    textures["MARIO_TRANSFORM_SMALL_TO_FIRE_2_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_SMALL_TO_FIRE_2_RIGHT"]);

    }
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
    textures["FIRE_MARIO_VICTORY"] = LoadTexture("resources/Entity/Mario/FireMarioVictory.png");
    };
    //Transform big to fire
    {
    textures["MARIO_TRANSFORM_BIG_TO_FIRE_0_RIGHT"] = textures["SUPER_MARIO_0_RIGHT"];
    textures["MARIO_TRANSFORM_BIG_TO_FIRE_0_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_BIG_TO_FIRE_0_RIGHT"]);
    textures["MARIO_TRANSFORM_BIG_TO_FIRE_1_RIGHT"] = LoadTexture("resources/Entity/Mario/TrasitioningFireMario_2.png");
    textures["MARIO_TRANSFORM_BIG_TO_FIRE_1_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_BIG_TO_FIRE_1_RIGHT"]);
    }
    //Transform fire to big
    {
    textures["MARIO_TRANSFORM_FIRE_TO_BIG_0_RIGHT"] = LoadTexture("resources/Entity/Mario/TrasitioningFireMario_2.png");
    textures["MARIO_TRANSFORM_FIRE_TO_BIG_0_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_FIRE_TO_BIG_0_RIGHT"]);
    textures["MARIO_TRANSFORM_FIRE_TO_BIG_1_RIGHT"] = textures["SUPER_MARIO_0_RIGHT"];
    textures["MARIO_TRANSFORM_FIRE_TO_BIG_1_LEFT"] = FlipTextureHorizontal(textures["MARIO_TRANSFORM_FIRE_TO_BIG_1_RIGHT"]);
    }
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
    textures["BACKGROUND_LEVEL_1"] = LoadTexture("resources/Background/background1.png");

    }
    //TILE
    for (int i = 0;i<104;i++){
        std::string tileName = "TILE_" + std::to_string(i);
        std::string path= "resources/Entity/Tiles/tile_" + std::to_string(i) + ".png";
        textures[tileName] = LoadTexture(path.c_str());
    }
    //BUTTON
    textures["MENU_STATE_BACKGROUND"] = LoadTexture("resources/Background/menu_background.png");
    textures["MENU_STATE_START_BUTTON"] = LoadTexture("resources/Button/MenuStartButton.png");
    textures["MENU_STATE_OPTIONS_BUTTON"] = LoadTexture("resources/Button/MenuOptionsButton.png");
    textures["EXIT_BUTTON"] = LoadTexture("resources/Button/ExitButton.png");
    //GAMESTATE
    textures["GAME_STATE_MENU_BUTTON"]= LoadTexture("resources/Button/GameStateMenuButton.png");
    //HUD
    textures["HUD_COINS"] = LoadTexture("resources/UI/hud_coin.png");
    textures["LEVEL_END_CONGRATULATIONS"] = LoadTexture("resources/UI/Congratulations.png");
    textures["LEVEL_END_ENTER"]= LoadTexture("resources/UI/PressEnter.png");
    textures["GAME_OVER"] = LoadTexture("resources/UI/GameOver.png");
    textures["HUD_MARIO"] = LoadTexture("resources/UI/MarioUI.png");
}   

void ResourceManager::loadSounds(){
    sounds["MARIO_JUMP"] = LoadSound("resources/SFX/smw_jump.wav");
    sounds["MARIO_FIREBALL"] = LoadSound("resources/SFX/smw_fireball.wav");
    // Transform sounds
    {
    sounds["MARIO_POWERUP"] = LoadSound("resources/SFX/smw_power-up.wav");
    sounds["MARIO_BEING_HIT"] = LoadSound("resources/SFX/smw_pipe.wav");
    }
}

void ResourceManager::loadMusics(){
    musics["Test"]= LoadMusicStream("resources/Music/music1.mp3");
}

void ResourceManager::loadResource(){
    loadFonts();
    loadTextures();
    loadMusics();
    loadSounds();
}
//Unload
void ResourceManager::unloadTexture(){
    for(auto&pair :textures)
        UnloadTexture(pair.second);
}

void ResourceManager::unloadFonts()
{
    // Fonts are not loaded in this example, but if they were, you would unload them here.
    for(auto&pair :fonts)
        UnloadFont(pair.second);
}

void ResourceManager::unloadSounds(){
    for(auto&pair :sounds)
    UnloadSound(pair.second);
}

void ResourceManager::unloadMusics(){
    for(auto&pair :musics)
    UnloadMusicStream(pair.second);
}

ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager instance;  // ← Automatic cleanup when program ends
    return instance;
}

void ResourceManager::unloadResource(){
    unloadFonts();
    unloadTexture();
    unloadSounds();
    unloadMusics();
}

//Getters
Texture2D& ResourceManager::getTexture( const std::string& name) {
    return textures[name];
}
Sound &ResourceManager::getSounds(const std::string& name) {
    return sounds[name];
}
Music &ResourceManager::getMusics(const std::string& name) {
    return musics[name];
}

Font &ResourceManager::getFonts(const std::string &name)
{
    return fonts[name];
}

Texture2D FlipTextureHorizontal(const Texture2D &texture)
{
    Image img = LoadImageFromTexture(texture);
    ImageFlipHorizontal(&img);
    Texture2D flip = LoadTextureFromImage(img);
    UnloadImage(img);  // Unload the image after creating the texture
    return flip;
}
