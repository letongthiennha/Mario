#pragma once
#include "DrawalbeObj.h"
#include "Direction.h"
#include "Hitbox.h"
#include "EnityState.h"
#include "CollisionInfo.h"
class Entity: public virtual DrawableObj{
protected:
    //Properties
    Vector2 pos;
    Vector2 size;
    Rectangle rect; //Used for collision detection
    EntityState state;
    Color color;
    const Texture2D *sprite;

    //Moving
    Vector2 velocity;
    Direction facingDirection;

    //Hitbox
    Hitbox NorthHb;
    Hitbox SouthHb;
    Hitbox WestHb;
    Hitbox EastHb;
    //Frame control
    float frameTime;
    float frameAcum;
    int currFrame;
    int maxFrame;
    //Call right before the draw function
    virtual void updateSprite()=0;


public:
    //Setter
    //Properties
    void setPosition(Vector2 pos);
    void setSize(Vector2 size);
    void setAngle(float angle);
    void setState(EntityState state);
    void setColor(Color color);
    //Moving
    void setVelocity(Vector2 velocity);
    void setFacingDirection(Direction direction);
    //Frame control
    void setFrameTime(float frameTime);
    void setFrameAcum(float frameAcum);
    void setCurrFrame(int currFrame);
    void setMaxFrame(int maxFrame);
    //Hitbox
    void setTopHb(Hitbox topHb);
    void setBotHb(Hitbox botHb);
    void setRightHb(Hitbox rightHb);
    void setLeftHb(Hitbox leftHb);

    //Getter
    Vector2 getPosition() const;
    Vector2 getSize() const;
    float getAngle() const;
    EntityState getState() const;
    Color getColor() const;
    Rectangle getRect() const;
    //Moving
    Vector2 getVelocity() const;
    Direction getFacingDirection() const;
    //Frame control
    float getFrameTime() const;
    float getFrameAcum() const;
    int getCurrFrame() const;
    int getMaxFrame() const;

    //Constructor
    Entity();
    Entity(Vector2 pos, Vector2 size, Vector2 velocity, Color color, 
           float frameTime, int maxFrame, Direction facingDirection);
    Entity(Vector2 pos, Vector2 size, Color color);
    Entity(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
    virtual ~Entity() override;
    ;

    //Call every frame draw happen in GetFrameTime()
    virtual void Draw() override = 0;

    //Call in an update loop
    //Update the position and physic of the entity happen in FIXED_TIME_STEP
    virtual void updateStateAndPhysic();

    //Update 
    virtual void updateHitboxes();
    //Collision
    CollisionInfo CheckCollisionType(const Entity& other) const;
    
};