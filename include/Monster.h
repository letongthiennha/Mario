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
    float blinkAcum;
    float blinkTime;
    float deathAcum;
    float deathDuration;
    float frameTime;
    bool isVisible;
    FloatingScore* floatingScore;
    int hitsToDie;
    int currFrame;
    int maxFrame;
    float frameAcum;
public:
    Monster(Vector2 pos, Vector2 size, Color color, float speed);
    virtual ~Monster();
    virtual void die();
    virtual void updateStateAndPhysic();
    virtual void Draw();
    virtual void handleCollision(const Tile& tile, CollisionInfo type) = 0; // Pure virtual

    bool getIsActive() const;
    void setIsActive(bool active);
};

#endif // MONSTER_H