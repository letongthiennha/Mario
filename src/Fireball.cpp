#include "Fireball.h"
#include "GameClock.h"
#include "Level.h"
#include "ResourceManager.h"
const float Fireball::MAX_DISTANCE = 1000.0f;
const float Fireball::FIREBALL_SPEEDX = 500.0f;
Fireball::Fireball(Vector2 pos, Direction direction) : Entity(pos, Vector2{ 16, 16 }, WHITE), distanceLeft(MAX_DISTANCE)
{
    this->sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_0_RIGHT");
    this->frameTime = 0.1f;
    this->frameAcum = 0.0f;
    this->currFrame = 0;
    this->maxFrame = 3;
    this->velocity = Vector2{FIREBALL_SPEEDX,0};
    this->facingDirection = direction;
    if (facingDirection == DIRECTION_LEFT){
    this->sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_0_LEFT");
        velocity.x = -FIREBALL_SPEEDX;
    }
    // Initialize hitboxes
    this->NorthHb.SetColor(RED);
    this->NorthHb.SetSize(Vector2{size.x-8, 1});

    this->SouthHb.SetColor(GREEN);
    this->SouthHb.SetSize(Vector2{size.x-8, 1});
    this->WestHb.SetColor(BLUE);
    this->WestHb.SetSize(Vector2{1, size.y-8});
    this->EastHb.SetColor(BLACK);
    this->EastHb.SetSize(Vector2{1, size.y-8});
    this->updateHitboxes();

}


void Fireball::updateStateAndPhysic()
{
    if(isOutOfDistance()) return; // Do not update if out of distance
    updateHitboxes();

    const float deltaTime = GameClock::getInstance().DeltaTime;

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

        if(velocity.x>0) 
            facingDirection = DIRECTION_RIGHT;
        else if(velocity.x<0)
            facingDirection = DIRECTION_LEFT;

        
        // Update position based on velocity
        Entity::updateStateAndPhysic();
        velocity.y += Level::GRAVITY*deltaTime;
    }

    void Fireball::updateSprite(){
    if (facingDirection == DIRECTION_RIGHT)
        switch (currFrame)
        {
        case 0:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_0_RIGHT");
        break;
        case 1:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_1_RIGHT");
        break;
        case 2:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_2_RIGHT");
        break;
        case 3:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_3_RIGHT");
        break;
        }

    else
    if(facingDirection == DIRECTION_LEFT)
        switch (currFrame)
        {
        case 0:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_0_LEFT");
        break;
        case 1:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_1_LEFT");
        break;
        case 2:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_2_LEFT");
        break;
        case 3:
            sprite = &ResourceManager::getInstance().getTexture("FIRE_BALL_3_LEFT");
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