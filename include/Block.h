#include "raylib.h"
#include "Entity.h"
#include "Mario.h"
#include "Map.h"

class Block : public Entity {
    protected:
        bool hit;
        int hitToDie = 0; // Number of hits to destroy the block
    public:
        Block();
        Block(Vector2 pos, Vector2 size, Color color);
        Block(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame);
        Block(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, int earnPoints);
        ~Block() override;

        void updateStateAndPhysic() override = 0;
        void Draw() override = 0;
        virtual void doHit(Mario& mario, Map &map);
        void resetHit();
};