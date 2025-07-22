#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"
#include "GameClock.h"
#include "Tile.h"
#include "CollisionInfo.h"
#include "FloatingScore.h"
#include <vector>
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
    FloatingScore* floatingScore;

public:
    Monster(Vector2 pos, Vector2 size, Color color, float speed);
    virtual ~Monster();
    
    virtual void updateStateAndPhysic();
    virtual void Draw();
    virtual void handleCollision(const Tile& tile, CollisionInfo type) = 0; // Pure virtual
    virtual void die(); //New method to trigger death

    bool getIsActive() const;
    void setIsActive(bool active);
    virtual bool isLethalToPlayer() const { return false; }
};

#endif // MONSTER_H