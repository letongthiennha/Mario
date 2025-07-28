#include "PlayableCharacter.h"
#include "GameClock.h"
#include "Level.h"
#include <cmath>
#include <iostream>
#include "SoundController.h"
//FUll constructor
PlayableCharacter::PlayableCharacter(Vector2 pos, int lives, PlayerState form)
    : Entity(pos, {32,40}, Vector2{0, 0}, WHITE, 0.1f, 2, DIRECTION_RIGHT),
      lives(lives),
      isDucking(false),
      form(form),
      normalSpeedX(500),
      accelerationX(600),
      jumpInitSpeed(sqrt(300 * Level::GRAVITY )),
    coin(0), isFiring(false),
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
    if(form == PLAYER_STATE_SMALL)
    {
        this->size = {32, 40};
    }
    else if(form == PLAYER_STATE_BIG)
    {
        this->size = {32, 56};
    }
    else if(form == PLAYER_STATE_FIRE)
    {
        this->size = {32, 56};
    }
    NorthHb.SetSize({size.x-4, 1});
    SouthHb.SetSize({size.x-4, 1});
    WestHb.SetSize({1, size.y-5});
    EastHb.SetSize({1, size.y-5});
    updateHitboxes();
    NorthHb.SetColor(RED);
    SouthHb.SetColor(GREEN);
    WestHb.SetColor(BLUE);
    EastHb.SetColor(BLACK);
}

PlayableCharacter::PlayableCharacter(Vector2 pos,const PlayerData &playerData): PlayableCharacter(pos, playerData.lives)
{   
    score= playerData.score;
    coin = playerData.coins;
}

PlayableCharacter::PlayableCharacter() : PlayableCharacter(Vector2{0, 0}, 3, PLAYER_STATE_SMALL) {};

PlayableCharacter::~PlayableCharacter(){
    for(auto& fireball:fireballs)
        {
            delete fireball;
            fireball = nullptr;
        }
    fireballs.clear();
    Entity::~Entity();
}

void PlayableCharacter::changeWinState(bool state) {
    winState = state;
}

bool PlayableCharacter::getWinState() const {
    return winState;
}

void PlayableCharacter::addLives(int lives)
{
    this->lives += lives;
    this->notify(GAME_EVENT::LIVES_CHANGE, this->lives);
}

void PlayableCharacter::setState(EntityState state)
{
    this->state = state;
}

PlayerState PlayableCharacter::getForm() const
{
    return form;
}

void PlayableCharacter::addCoin(int coin)
{
    if (coin < 0) coin = 0; // Prevent negative coins

    this->coin += coin;
    this->notify(GAME_EVENT::COIN_CHANGE, this->coin);
}

void PlayableCharacter::addScore(int score)
{

    this->score += score;
    this->notify(GAME_EVENT::SCORE_CHANGE, this->score);

}

int PlayableCharacter::getLives() const
{
    return lives;
}

int PlayableCharacter::getCoin() const
{
    return coin;
}

// Action

void PlayableCharacter::fire()
{
    fireballs.push_back(new Fireball(pos, facingDirection));
    SoundController::getInstance().PlaySound("MARIO_FIREBALL");
}

void PlayableCharacter::ChangeFromSmallToBig()
{
    form = PLAYER_STATE_BIG;
    frameAcum = 0;
    frameTime = 0.1f;
    currFrame = 0;
    this->size = {32, 56};
    maxFrame = 2;
    startInvincible();
}

void PlayableCharacter::ChangeFromBigToFire()
{
    form = PLAYER_STATE_FIRE;
    frameAcum = 0;
    frameTime = 0.1f;
    currFrame = 0;

    this->size = {32, 56};
    maxFrame = 2;
   startInvincible();
}

void PlayableCharacter::ChangeFromFireToBig()
{
    form = PLAYER_STATE_BIG;
    frameAcum = 0;
    frameTime = 0.1f;
    currFrame = 0;

   setSize( {32, 56});
    maxFrame = 2;
    startInvincible();
}

void PlayableCharacter::ChangeFromBigToSmall()
{
    form = PLAYER_STATE_SMALL;
    currFrame = 0;
    frameTime = 0.1f;
    frameAcum = 0;
    setSize({32, 40});
    maxFrame = 1;
    if(state==ENTITY_STATE_ON_GROUND) setPosition({pos.x, pos.y + 16}); // Adjust position when changing to small
   startInvincible();
}

void PlayableCharacter::ChangeFromSmallToFire()
{
    form = PLAYER_STATE_FIRE;
    currFrame = 0;
    frameTime = 0.1f;
    frameAcum = 0;
    setSize({32, 56});
    maxFrame = 2;
   startInvincible();
}

void PlayableCharacter::startInvincible()
{
    isInvincible = true;
    invincibleFrameAcum = 0.0f;
    invincibleFrame = 0;
}

void PlayableCharacter::moveLeft()
{
    if (form!= PLAYER_STATE_SMALL && form != PLAYER_STATE_BIG && form != PLAYER_STATE_FIRE)
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

void PlayableCharacter::moveRight()
{
    if (form!= PLAYER_STATE_SMALL && form != PLAYER_STATE_BIG && form != PLAYER_STATE_FIRE)
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

void PlayableCharacter::moveNoWhere()
{
    if(abs(velocity.x)<abs(accelerationX))
    velocity.x = 0;
    else
    velocity.x = velocity.x * 0.9;
}


void PlayableCharacter::jump()
{
    if (state != ENTITY_STATE_ON_GROUND) return; // Cannot jump if not on the ground
    if (form != PLAYER_STATE_SMALL && form != PLAYER_STATE_BIG && form != PLAYER_STATE_FIRE)
    {
        return; // Cannot jump if not in small, big, or fire state
    }
    state = ENTITY_STATE_JUMPING;
    velocity.y = -jumpInitSpeed;
    SoundController::getInstance().PlaySound("MARIO_JUMP");

}

void PlayableCharacter::Duck()
{
    this->isDucking = true;
}


std::list<Fireball *> *PlayableCharacter::getFireballs()
{
    return &fireballs;
}

void PlayableCharacter::startTransformingSmallToBig()
{
    form = PLAYER_STATE_TRANSFORMING_SMALL_TO_BIG;
    setSize({32, 56});
    frameTime = 0.075f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); // Adjust position when changing to small
}

void PlayableCharacter::startTransformingBigToSmall()
{
    form = PLAYER_STATE_TRANSFORMING_BIG_TO_SMALL;
    frameTime = 0.06f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_BEING_HIT");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); // Adjust position when changing to small
}

void PlayableCharacter::startWatingForReset()
{
    state = ENTITY_STATE_TO_BE_REMOVED;
    velocity = {0, 0}; // Stop movement
    
}

void PlayableCharacter::startTransformingBigToFire()
{
    form = PLAYER_STATE_TRANSFORMING_BIG_TO_FIRE;
    frameTime = 0.075f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); 
}

void PlayableCharacter::startTransformingFireToBig()
{
    form = PLAYER_STATE_TRANSFORMING_FIRE_TO_BIG;
    frameTime = 0.075f;
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_BEING_HIT");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0});
}

void PlayableCharacter::startTransformingSmallToFire()
{
    form = PLAYER_STATE_TRANSFORMING_SMALL_TO_FIRE;
    frameTime = 0.075f;
    setSize({32, 56});
    maxFrame = 11;
    currFrame = 0;
    frameAcum = 0;
    SoundController::getInstance().PlaySound("MARIO_POWERUP");
    if(state==ENTITY_STATE_FALLING) 
    setVelocity({velocity.x, 0}); // Adjust position when changing to small
}

void PlayableCharacter::die()
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

void PlayableCharacter::startVictoryDance()
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

void PlayableCharacter::HandleInput()
{
    const float deltaTime = GameClock::getInstance().DeltaTime;
    if(state==ENTITY_STATE_TO_BE_REMOVED){
        if(IsKeyPressed(KEY_ENTER)){
            startWatingForReset(); // Wait for reset if PlayableCharacter falls below a certain point
        }
        return; // Skip further updates when marked for removal
    }
    if (IsKeyDown(KEY_RIGHT)) moveRight();
    else if(IsKeyDown(KEY_LEFT)) moveLeft();
    else moveNoWhere();
    if(state==ENTITY_STATE_ON_GROUND){
        if(IsKeyPressed(KEY_UP)){
            jump();

        }
        if(IsKeyDown(KEY_DOWN)&& form!=PLAYER_STATE_SMALL){
            Duck();
        }
        else{
            isDucking = false;
        }
    }
    if(state==ENTITY_STATE_JUMPING){
        if(IsKeyReleased(KEY_UP)){
            if(velocity.y<0){ // If the character is still going up
                velocity.y += 100; // Stop upward movement
            }
        }
    }

    if (form==PLAYER_STATE_FIRE){
        if (IsKeyPressed(KEY_Z)&&!isFiring&&fireballs.size() <=4) {
            fire();
            isFiring = true; // Set firing state to true

        }
        if (IsKeyReleased(KEY_Z)) {
            isFiring = false; // Reset firing state when the key is released
        }
    }

}


void PlayableCharacter::updateStateAndPhysic(){
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
            startWatingForReset(); // Wait for reset if PlayableCharacter falls below a certain point
            return;
        }
        velocity.y+= (Level::GRAVITY+100) * deltaTime;
        pos.y += velocity.y * deltaTime;

        return; // Skip further updates when dying
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
    switch (form)
    {
    case PLAYER_STATE_SMALL:
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


            break;
    }
    case PLAYER_STATE_BIG:
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
    case PLAYER_STATE_FIRE:
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
    case PLAYER_STATE_TRANSFORMING_SMALL_TO_BIG:
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
    case PLAYER_STATE_TRANSFORMING_BIG_TO_SMALL:
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
    case PLAYER_STATE_TRANSFORMING_BIG_TO_FIRE:
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
    case PLAYER_STATE_TRANSFORMING_FIRE_TO_BIG:
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
    case PLAYER_STATE_TRANSFORMING_SMALL_TO_FIRE:
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

    if(form!= PLAYER_STATE_TRANSFORMING_SMALL_TO_BIG&&
        form!= PLAYER_STATE_TRANSFORMING_BIG_TO_SMALL&&
        form!= PLAYER_STATE_TRANSFORMING_BIG_TO_FIRE&&
        form!= PLAYER_STATE_TRANSFORMING_FIRE_TO_BIG&&
        form!= PLAYER_STATE_TRANSFORMING_SMALL_TO_FIRE){
        if(velocity.y>0){
            state= ENTITY_STATE_FALLING;
        }
        // if(state==ENTITY_STATE_ON_GROUND){
        //     velocity.y = 0;
        // }
        velocity.y += Level::GRAVITY * deltaTime;
        
        Entity::updateStateAndPhysic();
    }
    // Update fireballs
    for (auto i = fireballs.begin(); i != fireballs.end();)
    {
        Fireball* fireball = *i;
        if(fireball->isOutOfDistance()||fireball->getState()==ENTITY_STATE_TO_BE_REMOVED){
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

void PlayableCharacter::updateHitboxes(){
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

void PlayableCharacter::reactOnBeingHit()
{
    if(isInvincible) return; // Ignore if already invincible
    if(form == PLAYER_STATE_SMALL){
        die(); // If PlayableCharacter is small, he dies
        return;
    }
    if(form == PLAYER_STATE_BIG){
        startTransformingBigToSmall();
    }
    if(form == PLAYER_STATE_FIRE){
        startTransformingFireToBig();
    }
}

void PlayableCharacter::Draw(){
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

std::unique_ptr<PlayerData> PlayableCharacter::createMemento() const
{
    return std::unique_ptr<PlayerData>(std::make_unique<PlayerData>(lives,coin,score));
}


