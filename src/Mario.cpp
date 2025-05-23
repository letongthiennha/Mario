#include "Mario.h"
#include "GameClock.h"
#include <cmath>
#include <iostream>
Mario::Mario() : Entity(),sprite(ResourceManager::getTexture("SMALL_MARIO_0_RIGHT")), lives(3), 
                isDucking(false),form(MARIO_STATE_SMALL), gravity((2*GetScreenHeight())), isInvincible(false), 
                 isImmortal(false),normalSpeedX(500),jumpInitSpeed(sqrt(gravity*2*200)),accelerationX(600)
{
}

Mario:: Mario(Vector2 pos, Vector2 size, MarioState startState, Color color, int lives,
    MarioState form):sprite(ResourceManager::getTexture("SMALL_MARIO_0_LEFT")),Entity(pos,size,color),lives(lives),form(startState)
{}
Mario::~Mario(){
    for(auto& fireball:fireballs)
        {
            delete fireball;
            fireball = nullptr;
        }
}
void Mario::moveLeft(){
    if(facingDirection==DIRECTION_RIGHT){
        facingDirection = DIRECTION_LEFT;
        velocity.x = 0;
        }
        if(velocity.x+accelerationX * GameClock::GetUpdateDeltaTime()<=-normalSpeedX)
        velocity.x = -normalSpeedX;
    else
        velocity.x -= accelerationX * GameClock::GetUpdateDeltaTime();
}
void Mario::moveRight()
{
    if (facingDirection == DIRECTION_LEFT)
    {
        facingDirection = DIRECTION_RIGHT;
        velocity.x = 0;
    }
        if(velocity.x+accelerationX * GameClock::GetUpdateDeltaTime()>=normalSpeedX)
            velocity.x = normalSpeedX;
        else
        velocity.x += accelerationX * GameClock::GetUpdateDeltaTime();
}
void Mario::moveNoWhere()
{
    if(abs(velocity.x)<abs(accelerationX))
    velocity.x = 0;
    else
    velocity.x = velocity.x * 0.9;
}
void Mario::jump(){
    state = ENTITY_STATE_JUMPING;
    velocity.y = -jumpInitSpeed;
}
void Mario::Duck()
{
    this->isDucking = true;
}

void Mario::HandleInput()
{
    const float deltaTime = GameClock::GetUpdateDeltaTime();

    if (IsKeyDown(KEY_RIGHT)) moveRight();
    else if(IsKeyDown(KEY_LEFT)) moveLeft();
    else moveNoWhere();
    if(state==ENTITY_STATE_ON_GROUD){
        if(IsKeyPressed(KEY_UP))
            jump();
        if(IsKeyDown(KEY_DOWN)&& form==MARIO_STATE_BIG){
            Duck();
        }
        else{
            isDucking = false;
        }
    }
    if(IsKeyPressed(KEY_SPACE)){
        form=MARIO_STATE_BIG;
    }
}
void Mario::updateSprite(){
    const float deltaTime = GetFrameTime();
    switch (form){
        case MARIO_STATE_SMALL:
            {
                //On Ground
                if(state==ENTITY_STATE_ON_GROUD){
                    //Moving
                    if(velocity.x!=0&&!isDucking){
                    frameTime = 0.1;
                    frameAcum += deltaTime;
                    maxFrame = 1;
                    if(frameAcum>frameTime){
                        currFrame++;
                        if(currFrame>maxFrame) currFrame =0;
                        frameAcum -= frameTime;
                    }
                    if(facingDirection==DIRECTION_RIGHT) {
                                if(currFrame==0){
                                sprite = ResourceManager::getTexture("SMALL_MARIO_0_RIGHT");
                                }
                                else if(currFrame==1) {
                                sprite = ResourceManager::getTexture("SMALL_MARIO_1_RIGHT");
                                }
                            }
                    else {
                        if(currFrame==0){
                                sprite= ResourceManager::getTexture("SMALL_MARIO_0_LEFT");
                                }
                        else if(currFrame==1) {
                                sprite = ResourceManager::getTexture("SMALL_MARIO_1_LEFT");
                                }
                        }
                }
                    //Staying
                    if(velocity.x==0&&!isDucking){
                                if(facingDirection==DIRECTION_RIGHT) sprite = ResourceManager::getTexture("SMALL_MARIO_0_RIGHT");
                            else sprite = ResourceManager::getTexture("SMALL_MARIO_0_LEFT");
                    }
                   
                }

                //Jumping
                if(state==ENTITY_STATE_JUMPING){    
                //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = ResourceManager::getTexture("SMALL_MARIO_JUMPING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = ResourceManager::getTexture("SMALL_MARIO_JUMPING_0_LEFT");
                }
                //Falling
                if(state==ENTITY_STATE_FALLING){
                    //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = ResourceManager::getTexture("SMALL_MARIO_FALLING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = ResourceManager::getTexture("SMALL_MARIO_FALLING_0_LEFT");
                }
                break;
            }
        case MARIO_STATE_BIG:
        {   
            //On Ground
            if(state==ENTITY_STATE_ON_GROUD){
                //Moving
                if(velocity.x!=0&&!isDucking){
                    frameTime = 0.1;
                    frameAcum += deltaTime;
                    maxFrame = 2;
                    if(frameAcum>frameTime){
                        currFrame++;
                        if(currFrame>maxFrame) currFrame =0;
                        frameAcum -= frameTime;
                    }
                    if(facingDirection==DIRECTION_RIGHT) {
                                if(currFrame==0){
                                sprite = ResourceManager::getTexture("SUPER_MARIO_0_RIGHT");
                                }
                                else if(currFrame==1) {
                                sprite = ResourceManager::getTexture("SUPER_MARIO_1_RIGHT");
                                }
                                else if(currFrame==2) {
                                sprite = ResourceManager::getTexture("SUPER_MARIO_2_RIGHT");
                                }
                            }
                    else {
                        if(currFrame==0){
                                sprite= ResourceManager::getTexture("SUPER_MARIO_0_LEFT");
                                }
                        else if(currFrame==1) {
                                sprite = ResourceManager::getTexture("SUPER_MARIO_1_LEFT");
                                }
                        else if(currFrame==2) {
                                sprite = ResourceManager::getTexture("SUPER_MARIO_2_LEFT");
                                }
                        }
                }
                    //Staying
                if(velocity.x==0&&!isDucking){
                            if(facingDirection==DIRECTION_RIGHT) sprite = ResourceManager::getTexture("SUPER_MARIO_0_RIGHT");
                            else sprite = ResourceManager::getTexture("SUPER_MARIO_0_LEFT");
                    }
                    //Ducking
                if(isDucking){
                        velocity.x = 0;
                        if(facingDirection==DIRECTION_RIGHT) sprite = ResourceManager::getTexture("SUPER_MARIO_DUCKING_0_RIGHT");
                        else sprite = ResourceManager::getTexture("SUPER_MARIO_DUCKING_0_LEFT");
                }
            }

                //Jumping
            if(state==ENTITY_STATE_JUMPING){    
                //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = ResourceManager::getTexture("SUPER_MARIO_JUMPING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = ResourceManager::getTexture("SUPER_MARIO_JUMPING_0_LEFT");
            }
                //Falling
            if(state==ENTITY_STATE_FALLING){
                    //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = ResourceManager::getTexture("SUPER_MARIO_FALLING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = ResourceManager::getTexture("SUPER_MARIO_FALLING_0_LEFT");
            }
            break;
        }
        case MARIO_STATE_FIRE:
        {
            
        }
    }
}
void Mario::update(){
    HandleInput();
    const float deltaTime = GameClock::GetUpdateDeltaTime();
    if(state!= ENTITY_STATE_ON_GROUD){
        if(velocity.y>=0)
            state = ENTITY_STATE_FALLING;
    }
    //Velocity pixel/second
    //Gravity pixel/second^2
    pos.x += velocity.x*deltaTime;
    pos.y += velocity.y*deltaTime;
    if(pos.y+velocity.y*deltaTime>=700){
    pos.y=700;
    state = ENTITY_STATE_ON_GROUD;
    velocity.y = 0;
    }
    else     velocity.y += gravity*deltaTime;

}
void Mario::Draw(){
    updateSprite();
    DrawTexture(sprite, pos.x, pos.y, WHITE);
}