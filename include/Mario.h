#pragma once
#include "Entity.h"
#include "MarioState.h"
#include "Fireball.h"
#include "ResourceManager.h"
#include "Tile.h"
#include <list>
class Mario: public Entity{
    private:
    //Image
        // Properties
        int lives;
        bool isDucking;
        MarioState form;
        std::list<Fireball*>fireballs;

    // Special effects
    // Invincibility when hit
        // The player is invincible for a short time after being hit
    //     bool isInvincible;
    //     float invincibleFrameTime;
    //     float invincibleAcum;
    //     int invincibleFrame;
    //     int invincibleMaxFrame;
    // // Immortal when eating immortal star
    //     // In this state it can kill any thing
    //     bool isImmortal;
    //     float immortalFrameTime;
    //     float immortalAcum;
    //     int immortalFrame;
    //     int immortalMaxFrame;
    //Timing Event
        // Accelerating
        int normalSpeedX;
        int accelerationX;
        // Jumping
        float jumpInitSpeed;
        void updateSprite() override;

    public:
        // Constructor
        //Full constructor
        Mario(Vector2 pos, int lives,
              MarioState form);
        Mario();
        // Destructor
        ~Mario() override;

        // Setter
        void setSprite(Texture2D sprite);
        void setLives(int lives);
        void setState(EntityState state);
        
        // Getter
        int getLives() const;
        bool getIsDucking() const;
        std::list<Fireball*>* getFireballs() ;
        // Methods
        void jump();
        void moveLeft();
        void moveRight();
        void moveNoWhere();

        void Duck();
        void fire();

        void changeToBig();
        void changeToFire();
        void changeToSmall();

        // Game loop
        void HandleInput();
        void updateStateAndPhysic() override;
        void updateHitboxes() override;
        void Draw() override;
};