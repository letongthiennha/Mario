#include "Monster.h"
#include "raylib.h"

class Rex : public Monster {
private:
    float hitCooldown;
    Vector2 posOnDying;
    float squashDuration; // Duration of squashed state
public:
    Rex(Vector2 pos, float speed);
    void updateStateAndPhysic() override;
    void updateSprite() override;
    void handleCollision(const Tile& tile, CollisionInfo type) override;
    void onHit();
    void Draw() override;
};