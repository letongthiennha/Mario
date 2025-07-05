#include "Mario.h"
#include "GameClock.h"
#include "Level.h"
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
      jumpInitSpeed(sqrt(300 * Level::GRAVITY )),
    coin(0),
    isInvincible(false), invincibleFrameTime(0.03f), invincibleFrameAcum(0.0f), invincibleFrame(0), invincibleTime(3.0f)
    

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

Mario::Mario(Vector2 pos,const PlayerData &playerData): Mario(pos, playerData.lives)
{   
    score= playerData.score;
    coin = playerData.coins;
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

void Mario::addLives(int lives)
{
    this->lives += lives;
    this->notify(GAME_EVENT::LIVES_CHANGE, this->lives);
}

void Mario::setState(EntityState state)
{
    this->state = state;
}

MarioState Mario::getForm() const
{
    return form;
}

void Mario::addCoin(int coin)
{
    if (coin < 0) coin = 0; // Prevent negative coins

    this->coin += coin;
    this->notify(GAME_EVENT::COIN_CHANGE, this->coin);
}

void Mario::addScore(int score)
{

    this->score += score;
    this->notify(GAME_EVENT::SCORE_CHANGE, this->score);

}

int Mario::getLives() const
{
    return lives;
}

int Mario::getCoin() const
{
    return coin;
}

// Action

void Mario::fire()
{
    fireballs.push_back(new Fireball(pos, facingDirection));
    SoundController::getInstance().PlaySound("MARIO_FIREBALL");
}

void Mario::ChangeFromSmallToBig()
{
    form = MARIO_STATE_BIG;
    frameAcum = 0;
    frameTime = 0.1f;
    currFrame = 0;
    this->size = {32, 56};
    maxFrame = 2;
}

void Mario::ChangeFromBigToFire()
{
    form = MARIO_STATE_FIRE;
    frameAcum = 0;
    frameTime = 0.1f;
    currFrame = 0;

    this->size = {32, 56};
    maxFrame = 2;
}

void Mario::ChangeFromFireToBig()
{
    form = MARIO_STATE_BIG;
    frameAcum = 0;
    frameTime = 0.1f;
    currFrame = 0;

   setSize( {32, 56});
    maxFrame = 2;
}

void Mario::ChangeFromBigToSmall()
{
    form = MARIO_STATE_SMALL;
    currFrame = 0;
    frameTime = 0.1f;
    frameAcum = 0;
    setSize({32, 40});
    maxFrame = 1;
    if(state==ENTITY_STATE_ON_GROUD) setPosition({pos.x, pos.y + 16}); // Adjust position when changing to small
    startInvincible();
}

void Mario::ChangeFromSmallToFire()
{
    form = MARIO_STATE_FIRE;
    currFrame = 0;
    frameTime = 0.1f;
    frameAcum = 0;
    setSize({32, 56});
    maxFrame = 2;

}

void Mario::startInvincible()
{
    isInvincible = true;
    invincibleFrameAcum = 0.0f;
    invincibleFrame = 0;
}

void Mario::moveLeft()
{
    if (form!= MARIO_STATE_SMALL && form != MARIO_STATE_BIG && form != MARIO_STATE_FIRE)
    {
        return; // Cannot move left if not in small, big, or fire state
    }
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
    if (form!= MARIO_STATE_SMALL && form != MARIO_STATE_BIG && form != MARIO_STATE_FIRE)
    {
        return; // Cannot move right if not in small, big, or fire state
    }
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
    if (state != ENTITY_STATE_ON_GROUD) return; // Cannot jump if not on the ground
    if (form != MARIO_STATE_SMALL && form != MARIO_STATE_BIG && form != MARIO_STATE_FIRE)
    {
        return; // Cannot jump if not in small, big, or fire state
    }
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

void Mario::startTransformingSmallToBig()
{
    form = MARIO_STATE_TRANSFORMING_SMALL_TO_BIG;
    setSize({32, 56});
    frameTime = 0.075f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); // Adjust position when changing to small
}

void Mario::startTransformingBigToSmall()
{
    form = MARIO_STATE_TRANSFORMING_BIG_TO_SMALL;
    frameTime = 0.06f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_BEING_HIT");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); // Adjust position when changing to small
}

void Mario::startWatingForReset()
{
    state = ENTITY_STATE_TO_BE_REMOVED;
    velocity = {0, 0}; // Stop movement
    
}

void Mario::startTransformingBigToFire()
{
    form = MARIO_STATE_TRANSFORMING_BIG_TO_FIRE;
    frameTime = 0.075f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); 
}

void Mario::startTransformingFireToBig()
{
    form = MARIO_STATE_TRANSFORMING_FIRE_TO_BIG;
    frameTime = 0.075f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_BEING_HIT");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0});
}

void Mario::startTransformingSmallToFire()
{
    form = MARIO_STATE_TRANSFORMING_SMALL_TO_FIRE;
    frameTime = 0.075f;
    setSize({32, 56});
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); // Adjust position when changing to small
}

void Mario::die()
{
    if(state == ENTITY_STATE_DYING || state == ENTITY_STATE_TO_BE_REMOVED||state==ENTITY_STATE_VICTORY_DANCE) return; // Prevent multiple deaths
    state= ENTITY_STATE_DYING;
    velocity = {0, -1000};
    addLives(-1);
    addCoin(-coin); // Reset coins on death
    score = 0; // Reset score on death
    SoundController::getInstance().StopAllSounds(); // Stop all sounds
    SoundController::getInstance().PlaySound("MARIO_DIE");
}

void Mario::startVictoryDance()
{
    state = ENTITY_STATE_VICTORY_DANCE;
    velocity = {0, 0}; // Stop movement
    maxFrame = 0; // Number of frames in the victory dance animation
    frameTime = 0.0f; // Set frame time for the victory dance
    currFrame = 0; // Start from the first frame
    frameAcum = 0; // Reset frame accumulation
    SoundController::getInstance().StopAllSounds(); // Stop all sounds
    SoundController::getInstance().PlayMusic("VICTORY_MUSIC"); // Play victory music
}

void Mario::HandleInput()
{
    const float deltaTime = GameClock::getInstance().DeltaTime;
    if(state==ENTITY_STATE_TO_BE_REMOVED){
        if(IsKeyPressed(KEY_ENTER)){
            startWatingForReset(); // Wait for reset if Mario falls below a certain point
        }
        return; // Skip further updates when marked for removal
    }
    if (IsKeyDown(KEY_RIGHT)) moveRight();
    else if(IsKeyDown(KEY_LEFT)) moveLeft();
    else moveNoWhere();
    if(state==ENTITY_STATE_ON_GROUND){
        if(IsKeyPressed(KEY_UP))
            jump();

        }
        if(IsKeyDown(KEY_DOWN)&& form!=MARIO_STATE_SMALL){
            Duck();
        }
        else{
            isDucking = false;
        }
    }

    if (form==MARIO_STATE_FIRE){
        if (IsKeyPressed(KEY_Z)){
            fire();
        }
    }

    if(IsKeyPressed(KEY_SPACE)){
        reactOnBeingHit();
    }

    if(IsKeyDown(KEY_M)) {
        DrawText(std::to_string(lives).c_str(), 10, 10, 20, RED);
        DrawText(std::to_string(coin).c_str(), 10, 30,
        20, YELLOW);
        DrawText(std::to_string(score).c_str(), 10, 50,20, BLUE);
    }
    if(IsKeyPressed(KEY_KP_1)){
        startTransformingSmallToBig();
    }
    if(IsKeyPressed(KEY_KP_2)){
        startTransformingBigToFire();
    }
    if(IsKeyPressed(KEY_KP_3) ){
        startTransformingSmallToFire();
    }
    if(IsKeyPressed(KEY_KP_4)){
        addCoin(1);
    }
    if(IsKeyPressed(KEY_KP_5)){
        addScore(100);
    }
    if(IsKeyPressed(KEY_KP_6)){
        addLives(1);
    }
    
}

void Mario::updateSprite(){
    const float deltaTime = GetFrameTime();
    if(state==ENTITY_STATE_TO_BE_REMOVED){
        sprite = nullptr; // Hide sprite when marked for removal
        return;
    }
    switch (form){
        case MARIO_STATE_SMALL:
            {
                //On Ground
                if(state==ENTITY_STATE_ON_GROUND){
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
                if(state==ENTITY_STATE_DYING){
                    sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_DYING");
                }
                if(state==ENTITY_STATE_VICTORY_DANCE){
                    sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_VICTORY");
                }
                // Invincibility
                if(isInvincible){
                    if(!invincibleFrame)
                        return;
                    if(invincibleFrame==1){
                        sprite = nullptr;// Hide sprite for invincibility frame
                    }
                }
                break;
            }
        case MARIO_STATE_BIG:
        {   
            //On Ground
            if(state==ENTITY_STATE_ON_GROUND){
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
            if(state==ENTITY_STATE_DYING){
                sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_DYING");
            }
            if(state==ENTITY_STATE_VICTORY_DANCE){
                sprite = &ResourceManager::getInstance().getTexture("SUPER_MARIO_VICTORY");
            }
            break;
        }
        case MARIO_STATE_FIRE:
        {
                        //On Ground
                        if(state==ENTITY_STATE_ON_GROUND){
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
                        if(state==ENTITY_STATE_DYING){
                            sprite = &ResourceManager::getInstance().getTexture("SMALL_MARIO_DYING");
                        }
                        if(state==ENTITY_STATE_VICTORY_DANCE){
                            sprite = &ResourceManager::getInstance().getTexture("FIRE_MARIO_VICTORY");
                        }
                        break;

        }
        case MARIO_STATE_TRANSFORMING_SMALL_TO_BIG:
        {
            const std::string prefix= "MARIO_TRANSFORM_SMALL_TO_BIG_"+ std::to_string(TRANSFORM_SMALL_TO_BIG_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case MARIO_STATE_TRANSFORMING_BIG_TO_SMALL:
        {
            const std::string prefix= "MARIO_TRANSFORM_SMALL_TO_BIG_"+ std::to_string(TRANSFORM_BIG_TO_SMALL_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case MARIO_STATE_TRANSFORMING_BIG_TO_FIRE:
        {
            const std::string prefix= "MARIO_TRANSFORM_BIG_TO_FIRE_"+ std::to_string(TRANSFORM_BIG_TO_FIRE_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case MARIO_STATE_TRANSFORMING_FIRE_TO_BIG:
        {
            const std::string prefix= "MARIO_TRANSFORM_FIRE_TO_BIG_"+ std::to_string(TRANSFORM_FIRE_TO_BIG_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }
        case MARIO_STATE_TRANSFORMING_SMALL_TO_FIRE:
        {
            const std::string prefix= "MARIO_TRANSFORM_SMALL_TO_FIRE_"+ std::to_string(TRANSFORM_SMALL_TO_BIG_ORDER[currFrame]) + "_";
            if(facingDirection==DIRECTION_RIGHT){
                sprite = &ResourceManager::getInstance().getTexture(prefix+"RIGHT");
            }
            else{
                sprite = &ResourceManager::getInstance().getTexture(prefix+"LEFT");
            }
            break;
        }      
    }
}

void Mario::updateStateAndPhysic(){
    HandleInput();
    const float deltaTime = GameClock::getInstance().DeltaTime;
    if(state==ENTITY_STATE_TO_BE_REMOVED){
        velocity = {0, 0}; // Stop movement
        return; // Skip further updates when marked for removal
    }
    if(state==ENTITY_STATE_VICTORY_DANCE){
        return; // Skip further updates during victory dance
    }
    if(state==ENTITY_STATE_DYING){
        if(pos.y>=1000){
            startWatingForReset(); // Wait for reset if Mario falls below a certain point
            return;
        }
        velocity.y+= (Level::GRAVITY+100) * deltaTime;
        pos.y += velocity.y * deltaTime;

        return; // Skip further updates when dying
    }
    switch (form)
    {
    case MARIO_STATE_SMALL:
        {
            if(state==ENTITY_STATE_ON_GROUND){
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
            if(isInvincible){
                invincibleFrameAcum += deltaTime;
                invincibleAcum += deltaTime;
                if(invincibleFrameAcum / invincibleFrameTime>1){
                    invincibleFrame++;
                    if(invincibleFrame > 1) invincibleFrame = 0;
                    invincibleFrameAcum -= invincibleFrameTime;
                    }

                if(invincibleAcum>invincibleTime){
                    isInvincible = false;
                    invincibleAcum = 0.0f;
                    invincibleFrameAcum = 0.0f;
                    invincibleFrame = 0;
                }
            }

            break;
    }
    case MARIO_STATE_BIG:
        {if(state==ENTITY_STATE_ON_GROUND){
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
        {if(state==ENTITY_STATE_ON_GROUND){
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
    case MARIO_STATE_TRANSFORMING_SMALL_TO_BIG:
        {
            frameAcum += deltaTime;
            if(frameAcum>frameTime){
                currFrame++;
                if(currFrame>maxFrame) currFrame =0;
                frameAcum -= frameTime;
            }
            if(currFrame==maxFrame){
                ChangeFromSmallToBig();
            }
        
        break;  
        }  
    case MARIO_STATE_TRANSFORMING_BIG_TO_SMALL:
        {

            frameAcum += deltaTime;
            if(frameAcum>frameTime){
                currFrame++;
                if(currFrame>maxFrame) currFrame =0;
                frameAcum -= frameTime;
            }
            if(currFrame==maxFrame){
                ChangeFromBigToSmall();
            }
        break;
    }
    case MARIO_STATE_TRANSFORMING_BIG_TO_FIRE:
        {
            frameAcum += deltaTime;
            if(frameAcum>frameTime){
                currFrame++;
                frameAcum -= frameTime;
            }
            if(currFrame==maxFrame){
                ChangeFromBigToFire();
            }
        break;
    }
    case MARIO_STATE_TRANSFORMING_FIRE_TO_BIG:
        {
            frameAcum += deltaTime;
            if(frameAcum>frameTime){
                currFrame++;
                frameAcum -= frameTime;
            }
            if(currFrame==maxFrame){
                ChangeFromFireToBig();
            }
        break;
    }
    case MARIO_STATE_TRANSFORMING_SMALL_TO_FIRE:
        {
            frameAcum += deltaTime;
            if(frameAcum>frameTime){
                currFrame++;
                frameAcum -= frameTime;
            }
            if(currFrame==maxFrame){
                ChangeFromSmallToFire();
            }
        break;
    }
}
   
    //Velocity pixel/second
    //Gravity pixel/second^2

    if(form!= MARIO_STATE_TRANSFORMING_SMALL_TO_BIG&&
        form!= MARIO_STATE_TRANSFORMING_BIG_TO_SMALL&&
        form!= MARIO_STATE_TRANSFORMING_BIG_TO_FIRE&&
        form!= MARIO_STATE_TRANSFORMING_FIRE_TO_BIG&&
        form!= MARIO_STATE_TRANSFORMING_SMALL_TO_FIRE){
        if(velocity.y>0){
            state= ENTITY_STATE_FALLING;
        }
        // if(state==ENTITY_STATE_ON_GROUD){
        //     velocity.y = 0;
        // }
        velocity.y += Level::GRAVITY * deltaTime;
        
        Entity::updateStateAndPhysic();
    }
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

void Mario::reactOnBeingHit()
{
    if(form == MARIO_STATE_SMALL){
        die(); // If Mario is small, he dies
        return;
    }
    if(form == MARIO_STATE_BIG){
        startTransformingBigToSmall();
    }
    if(form == MARIO_STATE_FIRE){
        startTransformingFireToBig();
    }
}

void Mario::Draw(){
    updateSprite();
    for(auto& fireball:fireballs)
        {
            fireball->Draw();
        }
    if(sprite)
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
    // NorthHb.Draw();
    // SouthHb.Draw();
    // EastHb.Draw();
    // WestHb.Draw();
}

std::unique_ptr<PlayerData> Mario::createMemento() const
{
    return std::unique_ptr<PlayerData>(std::make_unique<PlayerData>(lives,coin,score));
}


