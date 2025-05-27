#include "Fireball.h"
#include "GameClock.h"
#include "World.h"
#include "ResourceManager.h"
const float Fireball::MAX_DISTANCE = 1000.0f;
const float Fireball::FIREBALL_SPEEDX = 500.0f;
Fireball::Fireball(Vector2 pos, Direction direction) : Entity(pos, Vector2{ 16, 16 }, WHITE), distanceLeft(MAX_DISTANCE)
{
    this->sprite = &ResourceManager::getTexture("FIRE_BALL_0_RIGHT");
    this->frameTime = 0.1f;
    this->frameAcum = 0.0f;
    this->currFrame = 0;
    this->maxFrame = 3;
    this->velocity = Vector2{FIREBALL_SPEEDX,0};
    this->facingDirection = direction;
    if (facingDirection == DIRECTION_LEFT){
    this->sprite = &ResourceManager::getTexture("FIRE_BALL_0_LEFT");
        velocity.x = -FIREBALL_SPEEDX;
    }
}

void Fireball::HandleGroundCollision(float groundY)
{
        pos.y = groundY - size.y; // Adjust position to be on top of the ground
        state = ENTITY_STATE_JUMPING; // Change state to on ground
        velocity.y = -500; // Reset vertical velocity
}
void Fireball::updateStateAndPhysic()
{
    if(isOutOfDistance()) return; // Do not update if out of distance
    updateHitboxes();

    const float deltaTime = GameClock::GetUpdateDeltaTime();

    //Image logic
        frameAcum += deltaTime;
        maxFrame = 3;
        if (frameAcum > frameTime)
    {
        currFrame++;
        if (currFrame > maxFrame) currFrame = 0;
        frameAcum -= frameTime;
    }
    
    //Physics logic
        distanceLeft -= abs(velocity.x) * deltaTime;


        
        // Update position based on velocity
        Entity::updateStateAndPhysic();
        velocity.y += World::GetGravity()*deltaTime;
    }
void Fireball::updateSprite(){
    if (facingDirection == DIRECTION_RIGHT)
        switch (currFrame)
        {
        case 0:
            sprite = &ResourceManager::getTexture("FIRE_BALL_0_RIGHT");
        break;
        case 1:
            sprite = &ResourceManager::getTexture("FIRE_BALL_1_RIGHT");
        break;
        case 2:
            sprite = &ResourceManager::getTexture("FIRE_BALL_2_RIGHT");
        break;
        case 3:
            sprite = &ResourceManager::getTexture("FIRE_BALL_3_RIGHT");
        break;
        }

    else
    if(facingDirection == DIRECTION_LEFT)
        switch (currFrame)
        {
        case 0:
            sprite = &ResourceManager::getTexture("FIRE_BALL_0_LEFT");
        break;
        case 1:
            sprite = &ResourceManager::getTexture("FIRE_BALL_1_LEFT");
        break;
        case 2:
            sprite = &ResourceManager::getTexture("FIRE_BALL_2_LEFT");
        break;
        case 3:
            sprite = &ResourceManager::getTexture("FIRE_BALL_3_LEFT");
        break;
        }
}

bool Fireball::isOutOfDistance() const
{
    return distanceLeft < 0.0f;
}

void Fireball::Draw(){
    if (isOutOfDistance()) return; // Do not draw if out of distance
    updateSprite();
    DrawTexture(*sprite, pos.x, pos.y, WHITE);
}