#include "../include/Entity.h"
#include "../include/GameClock.h"
void Entity::setPosition(Vector2 pos)
{
    this->pos = pos;
}

void Entity::setSize(Vector2 size)
{
    this->size = size;
}



void Entity::setState(EntityState state)
{
    this->state = state;
}

void Entity::setColor(Color color)
{
    this->color = color;
    this->NorthHb.SetColor(color);
    this->SouthHb.SetColor(color);
    this->WestHb.SetColor(color);
    this->EastHb.SetColor(color);
}
void Entity::setVelocity(Vector2 velocity)
{
    this->velocity = velocity;
}
void Entity::setFacingDirection(Direction direction)
{
    this->facingDirection = direction;
}
void Entity::setFrameTime(float frameTime)
{
    this->frameTime = frameTime;
}
void Entity::setFrameAcum(float frameAcum)
{
    this->frameAcum = frameAcum;
}
void Entity::setCurrFrame(int currFrame)
{
    this->currFrame = currFrame;
}
void Entity::setMaxFrame(int maxFrame)
{
    this->maxFrame = maxFrame;
}


Vector2 Entity::getPosition() const
{
    return this->pos;
}
Vector2 Entity::getSize() const
{
    return this->size;
}

EntityState Entity::getState() const
{
    return this->state;
}
Color Entity::getColor() const
{
    return color;
}
Vector2 Entity::getVelocity() const
{
    return this->velocity;
}
Direction Entity::getFacingDirection() const
{
    return this->facingDirection;
}

int Entity::getCurrFrame() const
{
    return this->currFrame;
}



//Full constructor
Entity::Entity(Vector2 pos, Vector2 size, Vector2 velocity, Color color, 
    float frameTime, int maxFrame, Direction facingDirection) :
sprite(nullptr),
pos(pos),
size(size),
velocity(velocity),
state(ENTITY_STATE_ON_GROUD),
color(color),
frameTime(frameTime),
frameAcum(0),
currFrame(0),
maxFrame(maxFrame),
facingDirection(facingDirection),
NorthHb(Vector2{pos.x + size.x/2 - 5, pos.y}, Vector2{size.x, 5}, color),
SouthHb(Vector2{pos.x + size.x/2 - 5, pos.y + size.y - 5}, Vector2{size.x, 5}, color),
WestHb(Vector2{pos.x + size.x - 5, pos.y + size.y/2 - 5}, Vector2{5, size.y}, color),
EastHb(Vector2{pos.x, pos.y + size.y/2 - 5}, Vector2{5, size.y}, color) {
    rect = { pos.x, pos.y, size.x, size.y };
}


// Basic constructor with default values
Entity::Entity() :
    Entity(Vector2{0, 0}, Vector2{0, 0}, Vector2{0, 0}, BLACK, 0, 0, DIRECTION_RIGHT) {
}


// Convenience constructor with just position, size and color
Entity::Entity(Vector2 pos, Vector2 size, Color color) :
    Entity(pos, size, Vector2{0, 0}, color, 0, 0, DIRECTION_RIGHT) {
}

// Constructor with animation parameters
Entity::Entity(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) :
    Entity(pos, size, Vector2{0, 0}, color, frameTime, maxFrame, DIRECTION_RIGHT) {

}

Entity::~Entity() {
    sprite = nullptr;
}
void Entity::updateStateAndPhysic() {
    // Update position based on velocity
    pos.x += velocity.x * GameClock::getInstance().DeltaTime;
    pos.y += velocity.y * GameClock::getInstance().DeltaTime;

    // The rectangle is used on the other object
    // The hitbox is used on the current object to check the direction of the collision
    rect.width = size.x;
    rect.height = size.y;
    rect.x = pos.x;
    rect.y = pos.y;
    updateHitboxes();
}
Rectangle Entity::getRect() const {
    return Rectangle{ pos.x, pos.y, size.x, size.y };
}
void Entity::updateHitboxes() {
    // Update hitbox positions based on entity position
    NorthHb.SetPosition(Vector2{
        pos.x + size.x/2 - NorthHb.GetSize().x/2,
        pos.y
    });
    SouthHb.SetPosition(Vector2{
        pos.x + size.x/2 - SouthHb.GetSize().x/2,
        pos.y + size.y - SouthHb.GetSize().y
    });
    
    WestHb.SetPosition(Vector2{
       pos.x,
        pos.y + size.y/2 - WestHb.GetSize().y/2
    });

    EastHb.SetPosition(Vector2{
        pos.x + size.x - WestHb.GetSize().x,
        pos.y + size.y/2 - EastHb.GetSize().y/2
    });
}

CollisionInfo Entity::CheckCollisionType(const Entity& other) const{
    if(NorthHb.CheckCollision(other.getRect()))
        return COLLISION_NORTH;
    if(SouthHb.CheckCollision(other.getRect()))
        return COLLISION_SOUTH;
    if(EastHb.CheckCollision(other.getRect()))
        return COLLISION_EAST;
    if(WestHb.CheckCollision(other.getRect()))
        return COLLISION_WEST;
    return COLLISION_NONE;
}