#ifndef MONSTER_H
#define MONSTER_H
#include "Entity.h"
#include "GameClock.h"
#include "World.h"

class Monster : public Entity {
protected:
    float speed;
    bool isActive;
public:
    Monster(Vector2 pos, Vector2 size, Color color, float speed);
    virtual ~Monster();
    
    virtual void updateStateAndPhysic();
    virtual void Draw();
    
    bool getIsActive() const;
    void setIsActive(bool active);
};

#endif // MONSTER_H