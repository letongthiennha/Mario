#include "ResourceManager.h"
void ResourceManager::loadFonts()
{
    fonts["HUD_FONT"] = LoadFont("resources/Font/HudFont.otf");
    fonts["SUPER_MARIO_WORLD_FONT"] = LoadFont("resources/Font/SuperMarioWorld.ttf");
	fonts["SETTING_FONT"] = LoadFont("resources/Font/SuperMario256.ttf");
}

// Load
void ResourceManager::loadTextures()
{
    //SMALL MARIO
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


    //Luigi
        //SMALL LUIGI
    {
        textures["SMALL_LUIGI_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SmallLuigi_0.png");
        textures["SMALL_LUIGI_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/SmallLuigi_1.png");
        textures["SMALL_LUIGI_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_LUIGI_0_RIGHT"]);
        textures["SMALL_LUIGI_1_LEFT"] = FlipTextureHorizontal(textures["SMALL_LUIGI_1_RIGHT"]);

        textures["SMALL_LUIGI_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SmallLuigiFalling_0.png");
        textures["SMALL_LUIGI_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_LUIGI_FALLING_0_RIGHT"]);

        textures["SMALL_LUIGI_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SmallLuigiJumping_0.png");
        textures["SMALL_LUIGI_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["SMALL_LUIGI_JUMPING_0_RIGHT"]);

    textures["SMALL_LUIGI_VICTORY"] = LoadTexture("resources/Entity/Luigi/SmallLuigiVictory_0.png");

    textures["SMALL_LUIGI_DYING"]= LoadTexture("resources/Entity/Luigi/SmallLuigiDying_0.png");
    };
    //Transform small to big
    {
    textures["LUIGI_TRANSFORM_SMALL_TO_BIG_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_0.png");
    textures["LUIGI_TRANSFORM_SMALL_TO_BIG_0_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_SMALL_TO_BIG_0_RIGHT"]);
    textures["LUIGI_TRANSFORM_SMALL_TO_BIG_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_1.png");
    textures["LUIGI_TRANSFORM_SMALL_TO_BIG_1_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_SMALL_TO_BIG_1_RIGHT"]);
    textures["LUIGI_TRANSFORM_SMALL_TO_BIG_2_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_2.png");
    textures["LUIGI_TRANSFORM_SMALL_TO_BIG_2_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_SMALL_TO_BIG_2_RIGHT"]);
    }
    //Transform small to fire
    {
    textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_0.png");
    textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_0_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_0_RIGHT"]);
    textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningFireLuigi.png");
    textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_1_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_1_RIGHT"]);
    textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_2_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningFireLuigi_2.png");
    textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_2_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_SMALL_TO_FIRE_2_RIGHT"]);

    }
    //BIG LUIGI
    {
        textures["SUPER_LUIGI_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SuperLuigi_0.png");
        textures["SUPER_LUIGI_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/SuperLuigi_1.png");
        textures["SUPER_LUIGI_2_RIGHT"] = LoadTexture("resources/Entity/Luigi/SuperLuigi_2.png");
        textures["SUPER_LUIGI_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_LUIGI_0_RIGHT"]);
        textures["SUPER_LUIGI_1_LEFT"] = FlipTextureHorizontal(textures["SUPER_LUIGI_1_RIGHT"]);
        textures["SUPER_LUIGI_2_LEFT"] = FlipTextureHorizontal(textures["SUPER_LUIGI_2_RIGHT"]);

        textures["SUPER_LUIGI_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SuperLuigiJumping_0.png");
        textures["SUPER_LUIGI_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_LUIGI_JUMPING_0_RIGHT"]);
        textures["SUPER_LUIGI_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SuperLuigiFalling_0.png");
        textures["SUPER_LUIGI_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_LUIGI_FALLING_0_RIGHT"]);

        textures["SUPER_LUIGI_DUCKING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/SuperLuigiDucking_0.png");
        textures["SUPER_LUIGI_DUCKING_0_LEFT"] = FlipTextureHorizontal(textures["SUPER_LUIGI_DUCKING_0_RIGHT"]);

        textures["SUPER_LUIGI_VICTORY"] = LoadTexture("resources/Entity/Luigi/SuperLuigiVictory_0.png");

        textures["TRANSITIONING_LUIGI_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_0.png");
        textures["TRANSITIONING_LUIGI_0_LEFT"] = FlipTextureHorizontal(textures["TRANSITIONING_LUIGI_0_RIGHT"]);
        textures["TRANSITIONING_LUIGI_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_1.png");
        textures["TRANSITIONING_LUIGI_1_LEFT"] = FlipTextureHorizontal(textures["TRANSITIONING_LUIGI_1_RIGHT"]);
        textures["TRANSITIONING_LUIGI_2_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningLuigi_2.png");
        textures["TRANSITIONING_LUIGI_2_LEFT"] = FlipTextureHorizontal(textures["TRANSITIONING_LUIGI_2_RIGHT"]);
    }

    // ────────────────────────────────
    // FIRE LUIGI
    // ────────────────────────────────
    {
        textures["FIRE_LUIGI_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/FireLuigi_0.png");
        textures["FIRE_LUIGI_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/FireLuigi_1.png");
        textures["FIRE_LUIGI_2_RIGHT"] = LoadTexture("resources/Entity/Luigi/FireLuigi_2.png");
        textures["FIRE_LUIGI_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_LUIGI_0_RIGHT"]);
        textures["FIRE_LUIGI_1_LEFT"] = FlipTextureHorizontal(textures["FIRE_LUIGI_1_RIGHT"]);
        textures["FIRE_LUIGI_2_LEFT"] = FlipTextureHorizontal(textures["FIRE_LUIGI_2_RIGHT"]);

        textures["FIRE_LUIGI_JUMPING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/FireLuigiJumping_0.png");
        textures["FIRE_LUIGI_JUMPING_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_LUIGI_JUMPING_0_RIGHT"]);
        textures["FIRE_LUIGI_FALLING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/FireLuigiFalling_0.png");
        textures["FIRE_LUIGI_FALLING_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_LUIGI_FALLING_0_RIGHT"]);

    textures["FIRE_LUIGI_DUCKING_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/FireLuigiDucking_0.png");
    textures["FIRE_LUIGI_DUCKING_0_LEFT"] = FlipTextureHorizontal(textures["FIRE_LUIGI_DUCKING_0_RIGHT"]);
    textures["FIRE_LUIGI_VICTORY"] = LoadTexture("resources/Entity/Luigi/FireLuigiVictory.png");
    };
    //Transform big to fire
    {
    textures["LUIGI_TRANSFORM_BIG_TO_FIRE_0_RIGHT"] = textures["SUPER_LUIGI_0_RIGHT"];
    textures["LUIGI_TRANSFORM_BIG_TO_FIRE_0_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_BIG_TO_FIRE_0_RIGHT"]);
    textures["LUIGI_TRANSFORM_BIG_TO_FIRE_1_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningFireLuigi_2.png");
    textures["LUIGI_TRANSFORM_BIG_TO_FIRE_1_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_BIG_TO_FIRE_1_RIGHT"]);
    }
    //Transform fire to big
    {
    textures["LUIGI_TRANSFORM_FIRE_TO_BIG_0_RIGHT"] = LoadTexture("resources/Entity/Luigi/TransitioningFireLuigi_2.png");
    textures["LUIGI_TRANSFORM_FIRE_TO_BIG_0_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_FIRE_TO_BIG_0_RIGHT"]);
    textures["LUIGI_TRANSFORM_FIRE_TO_BIG_1_RIGHT"] = textures["SUPER_LUIGI_0_RIGHT"];
    textures["LUIGI_TRANSFORM_FIRE_TO_BIG_1_LEFT"] = FlipTextureHorizontal(textures["LUIGI_TRANSFORM_FIRE_TO_BIG_1_RIGHT"]);
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
    textures["BACKGROUND_LEVEL_2"] = LoadTexture("resources/Background/background2.png");
	textures["SETTING_BACKGROUND"] = LoadTexture("resources/Background/setting_background.png");

    }
    //BLOCK
    {
    textures["Stone_Block"] = LoadTexture("resources/Entity/Blocks/Stone_0.png");
    textures["Cloud_Block"] = LoadTexture("resources/Entity/Blocks/Cloud_0.png");
    textures["Wood_Block"] = LoadTexture("resources/Entity/Blocks/Wood_0.png");
    textures["Glass_Block"] = LoadTexture("resources/Entity/Blocks/Glass_0.png");
    textures["Exclamation_Block"] = LoadTexture("resources/Entity/Blocks/Exclamation_0.png");
    textures["Eyes_Closed_Block"] = LoadTexture("resources/Entity/Blocks/EyesClosed_0.png");
    textures["Eyes_Opened_Block_0"] = LoadTexture("resources/Entity/Blocks/EyesOpened_0.png");
    textures["Eyes_Opened_Block_1"] = LoadTexture("resources/Entity/Blocks/EyesOpened_1.png");
    textures["Eyes_Opened_Block_2"] = LoadTexture("resources/Entity/Blocks/EyesOpened_2.png");
    textures["Eyes_Opened_Block_3"] = LoadTexture("resources/Entity/Blocks/EyesOpened_3.png");
    textures["Question_Block_0"] = LoadTexture("resources/Entity/Blocks/Question_0.png");
    textures["Question_Block_1"] = LoadTexture("resources/Entity/Blocks/Question_1.png");
    textures["Question_Block_2"] = LoadTexture("resources/Entity/Blocks/Question_2.png");
    textures["Question_Block_3"] = LoadTexture("resources/Entity/Blocks/Question_3.png");
    }
    //TILE
    for (int i = 0;i<113;i++){
        int index = i;
        if (index >= 104) index += 4;
        std::string tileName = "TILE_" + std::to_string(index);
        std::string path= "resources/Entity/Tiles/tile_" + std::to_string(i) + ".png";
        textures[tileName] = LoadTexture(path.c_str());
    }
    //BUTTON
    textures["MENU_STATE_BACKGROUND"] = LoadTexture("resources/Background/menu_background.png");
    textures["MENU_STATE_START_BUTTON"] = LoadTexture("resources/Button/MenuStartButton.png");
    textures["MENU_STATE_OPTIONS_BUTTON"] = LoadTexture("resources/Button/MenuOptionsButton.png");
    textures["EXIT_BUTTON"] = LoadTexture("resources/Button/ExitButton.png");

    textures["HOME_BUTTON_RELEASE"] = LoadTexture("resources/Button/homeButtonRelease.png");
    textures["HOME_BUTTON_PRESS"] = LoadTexture("resources/Button/homeButtonPress.png");
	textures["MUTE_BUTTON_RELEASE"] = LoadTexture("resources/Button/muteButtonRelease.png");
	textures["MUTE_BUTTON_PRESS"] = LoadTexture("resources/Button/muteButtonPress.png");
	textures["UNMUTE_BUTTON_RELEASE"] = LoadTexture("resources/Button/unmuteButtonRelease.png");
	textures["UNMUTE_BUTTON_PRESS"] = LoadTexture("resources/Button/unmuteButtonPress.png");
	textures["BACK_BUTTON_RELEASE"] = LoadTexture("resources/Button/backButtonRelease.png");
	textures["BACK_BUTTON_PRESS"] = LoadTexture("resources/Button/backButtonPress.png");
	textures["RESUME_BUTTON_PRESS"] = LoadTexture("resources/Button/resumeButtonPress.png");
	textures["RESUME_BUTTON_RELEASE"] = LoadTexture("resources/Button/resumeButtonRelease.png");
	textures["MENU_BUTTON_PRESS"] = LoadTexture("resources/Button/menuButtonPress.png");
	textures["MENU_BUTTON_RELEASE"] = LoadTexture("resources/Button/menuButtonRelease.png");

    textures["MARIO_BUTTON"] = LoadTexture("resources/Button/marioButton.png");
    textures["LUIGI_BUTTON"] = LoadTexture("resources/Button/luigiButton.png");
    //GAMESTATE
    textures["GAME_STATE_MENU_BUTTON"]= LoadTexture("resources/Button/GameStateMenuButton.png");
    
    //HUD
    textures["HUD_COINS"] = LoadTexture("resources/UI/hud_coin.png");
    textures["LEVEL_END_CONGRATULATIONS"] = LoadTexture("resources/UI/Congratulations.png");
    textures["LEVEL_END_ENTER"]= LoadTexture("resources/UI/PressEnter.png");
    textures["GAME_OVER"] = LoadTexture("resources/UI/GameOver.png");
    textures["HUD_MARIO"] = LoadTexture("resources/UI/MarioUI.png");
    textures["HUD_LUIGI"] = LoadTexture("resources/UI/LuigiUI.png");

    //ITEMS
	textures["COIN_0"] = LoadTexture("resources/Entity/Items/Coin_0.png");
	textures["COIN_1"] = LoadTexture("resources/Entity/Items/Coin_1.png");
	textures["COIN_2"] = LoadTexture("resources/Entity/Items/Coin_2.png");
	textures["COIN_3"] = LoadTexture("resources/Entity/Items/Coin_3.png");

	textures["MUSHROOM"] = LoadTexture("resources/Entity/Items/Mushroom.png");
	textures["UP_MUSHROOM"] = LoadTexture("resources/Entity/Items/1UpMushroom.png");
	textures["UP_MOON"] = LoadTexture("resources/Entity/Items/3UpMoon.png");
    
	textures["FIRE_FLOWER_0"] = LoadTexture("resources/Entity/Items/FireFlower_0.png");
	textures["FIRE_FLOWER_1"] = LoadTexture("resources/Entity/Items/FireFlower_1.png");

	textures["STAR"] = LoadTexture("resources/Entity/Items/Star.png");

    //EFFECTS
    textures["PUFT_0"] = LoadTexture("resources/Effects/Puft_0.png");
    textures["PUFT_1"] = LoadTexture("resources/Effects/Puft_1.png");
    textures["PUFT_2"] = LoadTexture("resources/Effects/Puft_2.png");
    textures["PUFT_3"] = LoadTexture("resources/Effects/Puft_3.png");


    textures["STAR_DUST_0"] = LoadTexture("resources/Effects/StarDust_0.png");
	textures["STAR_DUST_1"] = LoadTexture("resources/Effects/StarDust_1.png");
	textures["STAR_DUST_2"] = LoadTexture("resources/Effects/StarDust_2.png");
	textures["STAR_DUST_3"] = LoadTexture("resources/Effects/StarDust_3.png");

	textures["200_POINTS"] = LoadTexture("resources/Effects/guiHundredsPoints_200.png");
    textures["400_POINTS"] = LoadTexture("resources/Effects/guiHundredsPoints_400.png");
    textures["1000_POINTS"] = LoadTexture("resources/Effects/guiThousandsPoints_1000.png");
    textures["1_UP"] = LoadTexture("resources/Effects/gui1Up.png");
    textures["3_UP"] = LoadTexture("resources/Effects/gui3Up.png");
    {
        textures["GOOMBA_0_RIGHT"] = LoadTexture("resources/Entity/Monsters/Goomba/Goomba_0.png");
        textures["GOOMBA_0_LEFT"] = FlipTextureHorizontal(textures["GOOMBA_0_RIGHT"]);
        textures["GOOMBA_1_RIGHT"] = LoadTexture("resources/Entity/Monsters/Goomba/Goomba_1.png");
        textures["GOOMBA_1_LEFT"] = FlipTextureHorizontal(textures["GOOMBA_1_RIGHT"]);
    }
    //MONSTERS:

        // ────────────────────────────────
        // FLYING GOOMBA
        // ────────────────────────────────
        {
    
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
            textures["BLUE_KOOPA_0_RIGHT"] = LoadTexture("resources/Entity/Monsters/BlueKoopaTroopa/BlueKoopaTroopa_0.png");
            textures["BLUE_KOOPA_1_RIGHT"] = LoadTexture("resources/Entity/Monsters/BlueKoopaTroopa/BlueKoopaTroopa_1.png");
            textures["BLUE_KOOPA_0_LEFT"] = FlipTextureHorizontal(textures["BLUE_KOOPA_0_RIGHT"]);
            textures["BLUE_KOOPA_1_LEFT"] = FlipTextureHorizontal(textures["BLUE_KOOPA_1_RIGHT"]);
        }
        // ────────────────────────────────
        // GREEN KOOPA TROOPA
        // ────────────────────────────────
        {
            textures["GREEN_KOOPA_0_RIGHT"] = LoadTexture("resources/Entity/Enemies/GreenKoopaTroopa_0.png");
            textures["GREEN_KOOPA_1_RIGHT"] = LoadTexture("resources/Entity/Enemies/GreenKoopaTroopa_1.png");
            textures["GREEN_KOOPA_0_LEFT"] = FlipTextureHorizontal(textures["GREEN_KOOPA_0_RIGHT"]);
            textures["GREEN_KOOPA_1_LEFT"] = FlipTextureHorizontal(textures["GREEN_KOOPA_1_RIGHT"]);
        }
        // ────────────────────────────────
        // RED KOOPA TROOPA
        // ────────────────────────────────
        {
            textures["RED_KOOPA_0_RIGHT"] = LoadTexture("resources/Entity/Enemies/RedKoopaTroopa_0.png");
            textures["RED_KOOPA_1_RIGHT"] = LoadTexture("resources/Entity/Enemies/RedKoopaTroopa_1.png");
            textures["RED_KOOPA_0_LEFT"] = FlipTextureHorizontal(textures["RED_KOOPA_0_RIGHT"]);
            textures["RED_KOOPA_1_LEFT"] = FlipTextureHorizontal(textures["RED_KOOPA_1_RIGHT"]);
        }
        // ────────────────────────────────
        //YELLOW KOOPA TROOPA
        // ────────────────────────────────
        {
            textures["YELLOW_KOOPA_0_RIGHT"] = LoadTexture("resources/Entity/Enemies/YellowKoopaTroopa_0.png");
            textures["YELLOW_KOOPA_1_RIGHT"] = LoadTexture("resources/Entity/Enemies/YellowKoopaTroopa_1.png");
            textures["YELLOW_KOOPA_0_LEFT"] = FlipTextureHorizontal(textures["YELLOW_KOOPA_0_RIGHT"]);
            textures["YELLOW_KOOPA_1_LEFT"] = FlipTextureHorizontal(textures["YELLOW_KOOPA_1_RIGHT"]);
        }

        // PIRANHA PLANT
        {
            textures["PIRANHA_0"] = LoadTexture("resources/Entity/Monsters/PiranhaPlant/PiranhaPlant_0.png");
        } 

        // BANZABILL
        {
            textures["BANZAIBILL_0"] = FlipTextureHorizontal(LoadTexture("resources/Entity/Monsters/BanzaiBill/BanzaiBill_0.png"));
        }   
        //TREX
        {
            textures["REX_0_0_RIGHT"]= LoadTexture("resources/Entity/Monsters/Rex_2_0.png");
            textures["REX_0_0_LEFT"]= FlipTextureHorizontal(textures["REX_0_0_RIGHT"]);
            textures["REX_0_1_RIGHT"]= LoadTexture("resources/Entity/Monsters/Rex_2_1.png");
            textures["REX_0_1_LEFT"]= FlipTextureHorizontal(textures["REX_0_1_RIGHT"]);

            textures["REX_1_0_RIGHT"]= LoadTexture("resources/Entity/Monsters/Rex_1_0.png");
            textures["REX_1_0_LEFT"]= FlipTextureHorizontal(textures["REX_1_0_RIGHT"]);
            textures["REX_1_1_RIGHT"]= LoadTexture("resources/Entity/Monsters/Rex_1_1.png");
            textures["REX_1_1_LEFT"]= FlipTextureHorizontal(textures["REX_1_1_RIGHT"]);
        }

        // COURSE CLEAR TOKEN
		textures["COURSE_CLEAR_TOKEN"] = LoadTexture("resources/Entity/Items/CourseClearToken.png");


}   

void ResourceManager::loadSounds(){
    sounds["MARIO_JUMP"] = LoadSound("resources/SFX/smw_jump.wav");
    sounds["MARIO_FIREBALL"] = LoadSound("resources/SFX/smw_fireball.wav");
    sounds["MARIO_STOMP"] = LoadSound("resources/SFX/smw_stomp.wav");
    // Transform sounds
    {
    sounds["MARIO_POWERUP"] = LoadSound("resources/SFX/smw_power-up.wav");
    sounds["MARIO_BEING_HIT"] = LoadSound("resources/SFX/smw_pipe.wav");
    }
    sounds["MARIO_DIE"] = LoadSound("resources/SFX/playerDown.mp3");

	// COIN COLLECTION SFX
	sounds["COIN_COLLECTION"] = LoadSound("resources/SFX/smw_coin.wav");

    // POWER UP SFX
	sounds["POWER_UP_APPEARS"] = LoadSound("resources/SFX/smw_power-up_appears.wav");
	sounds["POWER_UP"] = LoadSound("resources/SFX/smw_power-up.wav");
}

void ResourceManager::loadMusics(){
    musics["GAME_OVER"] = LoadMusicStream("resources/Music/gameOver.mp3");

    musics["TITLE_BACKGROUND_MUSIC"] = LoadMusicStream("resources/Music/title.mp3");
    musics["VICTORY_MUSIC"] = LoadMusicStream("resources/Music/courseClear.mp3");
    musics["LEVEL_1_MUSIC"]= LoadMusicStream("resources/Music/music1.mp3");
    musics["LEVEL_2_MUSIC"]= LoadMusicStream("resources/Music/music2.mp3");
    musics["LEVEL_3_MUSIC"]= LoadMusicStream("resources/Music/music3.mp3");
    musics["CREDITS_MUSIC"] = LoadMusicStream("resources/Music/Credits.mp3");
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
