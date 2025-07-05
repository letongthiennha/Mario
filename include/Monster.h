#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"
#include "GameClock.h"
#include "World.h"

class Monster : public Entity {
protected:
    float speed;
    bool isActive;
    // Blinking animation variables
    float blinkAcum;
    float blinkTime;
    float deathDuration;
    float deathAcum;  // Total time since die() was triggered
    bool isVisible;
public:
    Monster(Vector2 pos, Vector2 size, Color color, float speed);
    virtual ~Monster();
    
    virtual void updateStateAndPhysic();
    virtual void Draw();
    virtual void handleCollision(const Tile& tile, CollisionInfo type) = 0; // Pure virtual
    virtual void die(); //New method to trigger death

    bool getIsActive() const;
    void setIsActive(bool active);
};

#endif // MONSTER_H