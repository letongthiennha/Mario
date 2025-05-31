#pragma once
#include "Entity.h"
#include "Tile.h"
class Fireball: public Entity{
private:
    Texture2D *sprite;
    static const float MAX_DISTANCE;
    float distanceLeft;
    static const float FIREBALL_SPEEDX;
    void updateSprite() override;

public:
    
    Fireball(Vector2 pos, Direction direction);
    void updateStateAndPhysic() override;
    bool isOutOfDistance() const;
    void Draw() override;
    void setSpeed(float speedX, float speedY);
    void setDirection(Direction direction);
};