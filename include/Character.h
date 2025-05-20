#include "Entity.h"

class Character: public Entity{
    private:
    //Image
        Texture2D spriteSheet;
        int drawIndex;
        Rectangle drawBorder;
        // Properties
        int lives;
        bool isDucking;

        int getPictureIndex();
    public:
        //Constructor
        Character();

        void fire();
        void moveLeft();
        void moveRight();
        void jump();
        void HandleInput();
        void update();
        void Draw() override;
};