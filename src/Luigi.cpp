#include "Luigi.h"
#include "Level.h"
#include <cmath>
Luigi::Luigi(Vector2 pos, const PlayerData &playerData): PlayableCharacter(pos, playerData)
{
        normalSpeedX = 350;
        accelerationX = 400;
    jumpInitSpeed = sqrt(400 * Level::GRAVITY);
}

void Luigi::updateSprite()
{
        const float deltaTime = GetFrameTime();
    if(state==ENTITY_STATE_TO_BE_REMOVED){
        sprite = nullptr; // Hide sprite when marked for removal
        return;
    }

    switch (form){
        case PLAYER_STATE_SMALL:
            {
                //On Ground
                if(state==ENTITY_STATE_ON_GROUND){
                    //Moving
                    if(velocity.x!=0&&!isDucking){

                    if(facingDirection==DIRECTION_RIGHT) {
                                if(currFrame==0){
                                sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_RIGHT");
                                }
                                else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_1_RIGHT");
                                }
                            }
                    else {
                        if(currFrame==0){
                                sprite= &ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_LEFT");
                                }
                        else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_1_LEFT");
                                }
                        }
                }
                    //Staying
                    if(velocity.x==0&&!isDucking){
                                if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_RIGHT");
                            else sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_0_LEFT");
                    }
                   
                }

                //Jumping
                if(state==ENTITY_STATE_JUMPING){    
                //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_JUMPING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_JUMPING_0_LEFT");
                }
                //Falling
                if(state==ENTITY_STATE_FALLING){
                    //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_FALLING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_FALLING_0_LEFT");
                }
                if(state==ENTITY_STATE_DYING){
                    sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_DYING");
                }
                if(state==ENTITY_STATE_VICTORY_DANCE){
                    sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_VICTORY");
                }
                // Invincibility

                break;
            }
        case PLAYER_STATE_BIG:
        {   
            //On Ground
            if(state==ENTITY_STATE_ON_GROUND){
                //Moving
                if(velocity.x!=0&&!isDucking){
                
                    if(facingDirection==DIRECTION_RIGHT) {
                                if(currFrame==0){
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_0_RIGHT");
                                }
                                else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_1_RIGHT");
                                }
                                else if(currFrame==2) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_2_RIGHT");
                                }
                            }
                    else {
                        if(currFrame==0){
                                sprite= &ResourceManager::getInstance().getTexture("SUPER_LUIGI_0_LEFT");
                                }
                        else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_1_LEFT");
                                }
                        else if(currFrame==2) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_2_LEFT");
                                }
                        }
                }
                    //Staying
                if(velocity.x==0&&!isDucking){
                            if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_0_RIGHT");
                            else sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_0_LEFT");
                    }
                    //Ducking
                if(isDucking){
                        velocity.x = 0;
                        if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_DUCKING_0_RIGHT");
                        else sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_DUCKING_0_LEFT");
                }
            }

                //Jumping
            if(state==ENTITY_STATE_JUMPING){    
                //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_JUMPING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_JUMPING_0_LEFT");
            }
                //Falling
            if(state==ENTITY_STATE_FALLING){
                    //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_FALLING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_FALLING_0_LEFT");
            }
            if(state==ENTITY_STATE_DYING){
                sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_DYING");
            }
            if(state==ENTITY_STATE_VICTORY_DANCE){
                sprite = &ResourceManager::getInstance().getTexture("SUPER_LUIGI_VICTORY");
            }
            break;
        }
        case PLAYER_STATE_FIRE:
        {
                        //On Ground
                        if(state==ENTITY_STATE_ON_GROUND){
                            //Moving
                            if(velocity.x!=0&&!isDucking){
                                if(facingDirection==DIRECTION_RIGHT) {
                                            if(currFrame==0){
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_0_RIGHT");
                                            }
                                            else if(currFrame==1) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_1_RIGHT");
                                            }
                                            else if(currFrame==2) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_2_RIGHT");
                                            }
                                        }
                                else {
                                    if(currFrame==0){
                                            sprite= &ResourceManager::getInstance().getTexture("FIRE_LUIGI_0_LEFT");
                                            }
                                    else if(currFrame==1) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_1_LEFT");
                                            }
                                    else if(currFrame==2) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_2_LEFT");
                                            }
                                    }
                            }
                                //Staying
                            if(velocity.x==0&&!isDucking){
                                        if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_0_RIGHT");
                                        else sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_0_LEFT");
                                }
                                //Ducking
                            if(isDucking){
                                    velocity.x = 0;
                                    if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_DUCKING_0_RIGHT");
                                    else sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_DUCKING_0_LEFT");
                            }
                        }
            
                            //Jumping
                        if(state==ENTITY_STATE_JUMPING){    
                            //Image
                                if(facingDirection==DIRECTION_RIGHT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_JUMPING_0_RIGHT");
                                if(facingDirection==DIRECTION_LEFT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_JUMPING_0_LEFT");
                        }
                            //Falling
                        if(state==ENTITY_STATE_FALLING){
                                //Image
                                if(facingDirection==DIRECTION_RIGHT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_FALLING_0_RIGHT");
                                if(facingDirection==DIRECTION_LEFT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_FALLING_0_LEFT");
                        }
                        if(state==ENTITY_STATE_DYING){
                            sprite = &ResourceManager::getInstance().getTexture("SMALL_LUIGI_DYING");
                        }
                        if(state==ENTITY_STATE_VICTORY_DANCE){
                            sprite = &ResourceManager::getInstance().getTexture("FIRE_LUIGI_VICTORY");
                        }
                        break;

        }
        case PLAYER_STATE_TRANSFORMING_SMALL_TO_BIG:
        {
            const std::string prefix= "LUIGI_TRANSFORM_SMALL_TO_BIG_"+ std::to_string(TRANSFORM_SMALL_TO_BIG_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case PLAYER_STATE_TRANSFORMING_BIG_TO_SMALL:
        {
            const std::string prefix= "LUIGI_TRANSFORM_SMALL_TO_BIG_"+ std::to_string(TRANSFORM_BIG_TO_SMALL_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case PLAYER_STATE_TRANSFORMING_BIG_TO_FIRE:
        {
            const std::string prefix= "LUIGI_TRANSFORM_BIG_TO_FIRE_"+ std::to_string(TRANSFORM_BIG_TO_FIRE_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case PLAYER_STATE_TRANSFORMING_FIRE_TO_BIG:
        {
            const std::string prefix= "LUIGI_TRANSFORM_FIRE_TO_BIG_"+ std::to_string(TRANSFORM_FIRE_TO_BIG_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case PLAYER_STATE_TRANSFORMING_SMALL_TO_FIRE:
        {
            const std::string prefix= "LUIGI_TRANSFORM_SMALL_TO_FIRE_"+ std::to_string(TRANSFORM_SMALL_TO_BIG_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }      
    }
    if(isInvincible){
        if(!invincibleFrame)
            return;
        if(invincibleFrame==1){
            sprite = nullptr;// Hide sprite for invincibility frame
        }
    }
}
