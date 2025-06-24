#include "Mario.h"
#include "GameClock.h"
#include "World.h"
#include <cmath>
#include <iostream>
#include "SoundControoler.h"
//FUll constructor
Mario::Mario(Vector2 pos, int lives, MarioState form)
    : Entity(pos, {32,40}, Vector2{0, 0}, WHITE, 0.1f, 2, DIRECTION_RIGHT),
      lives(lives),
      isDucking(false),
      form(form),
      normalSpeedX(500),
      accelerationX(600),
      jumpInitSpeed(sqrt(300 * World::GetGravity() ))
    //   invincibleFrameTime(0.1f),
    //   invincibleAcum(0.0f),
    //   invincibleFrame(0),
    //   invincibleMaxFrame(2),
    //   immortalFrameTime(0.1f),
    //   immortalAcum(0.0f),
    //   immortalFrame(0),
    //   immortalMaxFrame(2)
{
    this->sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_0_RIGHT");
    if(form == MARIO_STATE_SMALL)
    {
        this->size = {32, 40};
    }
    else if(form == MARIO_STATE_BIG)
    {
        this->size = {32, 56};
    }
    else if(form == MARIO_STATE_FIRE)
    {
        this->size = {32, 56};
    }
    NorthHb.SetSize({size.x/2, 1});
    SouthHb.SetSize({size.x/2, 1});
    WestHb.SetSize({1, size.y-5});
    EastHb.SetSize({1, size.y-5});
    updateHitboxes();
    NorthHb.SetColor(RED);
    SouthHb.SetColor(GREEN);
    WestHb.SetColor(BLUE);
    EastHb.SetColor(BLACK);
}

Mario::Mario() : Mario(Vector2{0, 0}, 3, MARIO_STATE_SMALL) {};

Mario::~Mario(){
    for(auto& fireball:fireballs)
        {
            delete fireball;
            fireball = nullptr;
        }
    fireballs.clear();
    Entity::~Entity();
}

void Mario::setState(EntityState state)
{
    this->state = state;
}

// Action

void Mario::fire()
{
    fireballs.push_back(new Fireball(pos, facingDirection));
    SoundController::getInstance().PlaySound("MARIO_FIREBALL");
}

void Mario::changeToBig()
{
    form = MARIO_STATE_BIG;
    this->size = {32, 56};
    maxFrame = 2;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");

}

void Mario::changeToFire()
{
    form = MARIO_STATE_FIRE;
    this->size = {32, 56};
    maxFrame = 2;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
}

void Mario::changeToSmall()
{
    form = MARIO_STATE_SMALL;
    this->size = {32, 40};
    maxFrame = 1;
}

void Mario::moveLeft()
{
    if(facingDirection==DIRECTION_RIGHT){
        facingDirection = DIRECTION_LEFT;
        velocity.x = 0;
        frameAcum = 0;
        }
        if(velocity.x+accelerationX * GameClock::getInstance().DeltaTime<=-normalSpeedX)
        velocity.x = -normalSpeedX;
    else
        velocity.x -= accelerationX * GameClock::getInstance().DeltaTime;
}

void Mario::moveRight()
{
    if (facingDirection == DIRECTION_LEFT)
    {
        facingDirection = DIRECTION_RIGHT;
        velocity.x = 0;
        frameAcum = 0;
    }
        if(velocity.x+accelerationX * GameClock::getInstance().DeltaTime>=normalSpeedX)
            velocity.x = normalSpeedX;
        else
        velocity.x += accelerationX * GameClock::getInstance().DeltaTime;
}

void Mario::moveNoWhere()
{
    if(abs(velocity.x)<abs(accelerationX))
    velocity.x = 0;
    else
    velocity.x = velocity.x * 0.9;
}


void Mario::jump()
{
    state = ENTITY_STATE_JUMPING;
    velocity.y = -jumpInitSpeed;
    SoundController::getInstance().PlaySound("MARIO_JUMP");

}

void Mario::Duck()
{
    this->isDucking = true;
}


std::list<Fireball *> *Mario::getFireballs()
{
    return &fireballs;
}


void Mario::HandleInput()
{
    const float deltaTime = GameClock::getInstance().DeltaTime;

    if (IsKeyDown(KEY_RIGHT)) moveRight();
    else if(IsKeyDown(KEY_LEFT)) moveLeft();
    else moveNoWhere();
    if(state==ENTITY_STATE_ON_GROUD){
        if(IsKeyPressed(KEY_UP)){
            jump();

        }
        if(IsKeyDown(KEY_DOWN)&& form!=MARIO_STATE_SMALL){
            Duck();
        }
        else{
            isDucking = false;
        }
    }
    if(IsKeyPressed(KEY_SPACE)){
        changeToBig();
    }
    if(IsKeyPressed(KEY_F)){
        changeToFire();
    }
    if (form==MARIO_STATE_FIRE){
        if (IsKeyPressed(KEY_Z)){
            fire();
        }
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

                    if(facingDirection==DIRECTION_RIGHT) {
                                if(currFrame==0){
                                sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_0_RIGHT");
                                }
                                else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_1_RIGHT");
                                }
                            }
                    else {
                        if(currFrame==0){
                                sprite= &ResourceManager::getInstance().getTexture("SMALL_MARIO_0_LEFT");
                                }
                        else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_1_LEFT");
                                }
                        }
                }
                    //Staying
                    if(velocity.x==0&&!isDucking){
                                if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_0_RIGHT");
                            else sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_0_LEFT");
                    }
                   
                }

                //Jumping
                if(state==ENTITY_STATE_JUMPING){    
                //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_JUMPING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_JUMPING_0_LEFT");
                }
                //Falling
                if(state==ENTITY_STATE_FALLING){
                    //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_FALLING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_FALLING_0_LEFT");
                }
                break;
            }
        case MARIO_STATE_BIG:
        {   
            //On Ground
            if(state==ENTITY_STATE_ON_GROUD){
                //Moving
                if(velocity.x!=0&&!isDucking){
                
                    if(facingDirection==DIRECTION_RIGHT) {
                                if(currFrame==0){
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_0_RIGHT");
                                }
                                else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_1_RIGHT");
                                }
                                else if(currFrame==2) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_2_RIGHT");
                                }
                            }
                    else {
                        if(currFrame==0){
                                sprite= &ResourceManager::getInstance().getTexture("SUPER_MARIO_0_LEFT");
                                }
                        else if(currFrame==1) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_1_LEFT");
                                }
                        else if(currFrame==2) {
                                sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_2_LEFT");
                                }
                        }
                }
                    //Staying
                if(velocity.x==0&&!isDucking){
                            if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_0_RIGHT");
                            else sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_0_LEFT");
                    }
                    //Ducking
                if(isDucking){
                        velocity.x = 0;
                        if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_DUCKING_0_RIGHT");
                        else sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_DUCKING_0_LEFT");
                }
            }

                //Jumping
            if(state==ENTITY_STATE_JUMPING){    
                //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_JUMPING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_JUMPING_0_LEFT");
            }
                //Falling
            if(state==ENTITY_STATE_FALLING){
                    //Image
                    if(facingDirection==DIRECTION_RIGHT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_FALLING_0_RIGHT");
                    if(facingDirection==DIRECTION_LEFT)
                        sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_FALLING_0_LEFT");
            }
            break;
        }
        case MARIO_STATE_FIRE:
        {
                        //On Ground
                        if(state==ENTITY_STATE_ON_GROUD){
                            //Moving
                            if(velocity.x!=0&&!isDucking){
                                if(facingDirection==DIRECTION_RIGHT) {
                                            if(currFrame==0){
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_0_RIGHT");
                                            }
                                            else if(currFrame==1) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_1_RIGHT");
                                            }
                                            else if(currFrame==2) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_2_RIGHT");
                                            }
                                        }
                                else {
                                    if(currFrame==0){
                                            sprite= &ResourceManager::getInstance().getTexture("FIRE_MARIO_0_LEFT");
                                            }
                                    else if(currFrame==1) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_1_LEFT");
                                            }
                                    else if(currFrame==2) {
                                            sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_2_LEFT");
                                            }
                                    }
                            }
                                //Staying
                            if(velocity.x==0&&!isDucking){
                                        if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_0_RIGHT");
                                        else sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_0_LEFT");
                                }
                                //Ducking
                            if(isDucking){
                                    velocity.x = 0;
                                    if(facingDirection==DIRECTION_RIGHT) sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_DUCKING_0_RIGHT");
                                    else sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_DUCKING_0_LEFT");
                            }
                        }
            
                            //Jumping
                        if(state==ENTITY_STATE_JUMPING){    
                            //Image
                                if(facingDirection==DIRECTION_RIGHT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_JUMPING_0_RIGHT");
                                if(facingDirection==DIRECTION_LEFT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_JUMPING_0_LEFT");
                        }
                            //Falling
                        if(state==ENTITY_STATE_FALLING){
                                //Image
                                if(facingDirection==DIRECTION_RIGHT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_FALLING_0_RIGHT");
                                if(facingDirection==DIRECTION_LEFT)
                                    sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_FALLING_0_LEFT");
                        }
                        break;
            
        }
    }
}

void Mario::updateStateAndPhysic(){
    HandleInput();
    const float deltaTime = GameClock::getInstance().DeltaTime;
    switch (form)
    {
    case MARIO_STATE_SMALL:
        {
            if(state==ENTITY_STATE_ON_GROUD){
            if(velocity.x!=0&&!isDucking){
                frameTime = 0.1;
                frameAcum += deltaTime;
                maxFrame = 1;
                if(frameAcum>frameTime){
                    currFrame++;
                    if(currFrame>maxFrame) currFrame =0;
                    frameAcum -= frameTime;
                }
            }
        }
        break;
    }
    case MARIO_STATE_BIG:
        {if(state==ENTITY_STATE_ON_GROUD){
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
            }
        }
        break;
    }
    case MARIO_STATE_FIRE:
        {if(state==ENTITY_STATE_ON_GROUD){
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
            }
        }
        break;
    }
    }

   
    //Velocity pixel/second
    //Gravity pixel/second^2


    if(velocity.y>0){
        state= ENTITY_STATE_FALLING;
    }
    // if(state==ENTITY_STATE_ON_GROUD){
    //     velocity.y = 0;
    // }
    velocity.y += World::GetGravity() * deltaTime;
    
    Entity::updateStateAndPhysic();

    // Update fireballs
    for (auto i = fireballs.begin(); i != fireballs.end();)
    {
        Fireball* fireball = *i;
        if(fireball->isOutOfDistance()){
            delete fireball;
            fireball = nullptr;
            i = fireballs.erase(i);
        }
        else{
            fireball->updateStateAndPhysic();
            ++i;
        }
    }

    // Update hitboxes
    updateHitboxes();
}

void Mario::updateHitboxes(){
    if(isDucking){
        NorthHb .SetPosition({pos.x + size.x / 2 - NorthHb.GetSize().x / 2, pos.y+size.y/2 - NorthHb.GetSize().y});
        EastHb.SetSize({5, size.y / 2});
        EastHb.SetPosition({pos.x+size.x-EastHb.GetSize().x, pos.y + size.y*3/4 - EastHb.GetSize().y/2});
        WestHb.SetSize({5, size.y / 2});
        WestHb.SetPosition({pos.x , pos.y+  size.y*3/4- WestHb.GetSize().y/2});

    }
    else{
    EastHb.SetSize({1, size.y-5});
    WestHb.SetSize({1, size.y-5});
    Entity::updateHitboxes();
    }
}

void Mario::Draw(){
    updateSprite();
    for(auto& fireball:fireballs)
        {
            fireball->Draw();
        }
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
    // NorthHb.Draw();
    // SouthHb.Draw();
    // EastHb.Draw();
    // WestHb.Draw();
}