#pragma once
#include "Entity.h"
#include "MarioState.h"
#include "Fireball.h"
#include "ResourceManager.h"
#include "Tile.h" 
#include "Subject.h"
#include <list>
class Subject;
class Mario: public Entity, public Subject {
    private:
    //Image
        // Properties
        int lives;
        bool isDucking;
        MarioState form;
        std::list<Fireball*>fireballs;
        int coin;
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
        // Timing Event
        // Accelerating
        int normalSpeedX;
        int accelerationX;
        // Jumping
        float jumpInitSpeed;
        void updateSprite() override;

        void jump();
        void moveLeft();
        void moveRight();
        void moveNoWhere();

        void Duck();
        void fire();
    public:
        // Constructor
        //Full constructor
        Mario(Vector2 pos, int lives,
              MarioState form);
        Mario();
        // Destructor
        ~Mario() override;

        // Setter
        void addLives(int lives);
        void setState(EntityState state);
        void addCoin(int coin);
        // Getter
        int getLives() const;
        int getCoin() const;
        std::list<Fireball*>* getFireballs() ;
        // Methods


        void changeToBig();
        void changeToFire();
        void changeToSmall();

        // Game loop
        void HandleInput();
        void updateStateAndPhysic() override;
        void updateHitboxes() override;
        void Draw() override;
};