#pragma once
#include "Entity.h"
#include "MarioState.h"
#include "Fireball.h"
#include "ResourceManager.h"
#include "Tile.h" 
#include "Subject.h"
#include "PlayerData.h"
#include <memory>
#include <list>
class PlayerData;
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
        int score;

         const int TRANSFORM_SMALL_TO_BIG_ORDER[11] = { 0, 1, 0, 1, 0, 1, 2, 1, 2, 1, 2 };
         const int TRANSFORM_BIG_TO_SMALL_ORDER[11] = { 2, 1, 2, 1, 2, 1, 0, 1, 0, 1, 0 };
         const int TRANSFORM_BIG_TO_FIRE_ORDER[11] = { 0, 1, 0, 1, 0, 1, 0, 1,0,1,0 };
         const int TRANSFORM_FIRE_TO_BIG_ORDER[11] = { 1,0,1,0,1,1,0,1,0,1,0 };
        // Special effects
        // Invincibility when hit
        // The player is invincible for a short time after being hit
            bool isInvincible;
            const float invincibleFrameTime;
            float invincibleFrameAcum;
            int invincibleFrame;
            float invincibleAcum;
           const float invincibleTime;
            // // Immortal when eating immortal star
            //     // In this state it can kill any thing
            //     bool isImmortal;
            //     float immortalFrameTime;
            //     float immortalAcum;
            //     int immortalFrame;
            //     int immortalMaxFrame;
            // Timing Event
            // Accelerating
            const int normalSpeedX;
            const int accelerationX;
            // Jumping
            const float jumpInitSpeed;
            void updateSprite() override;

            void jump();
            void moveLeft();
            void moveRight();
            void moveNoWhere();

            void Duck();
            void fire();

            void ChangeFromSmallToBig();
            void ChangeFromBigToFire();
            void ChangeFromFireToBig();
            void ChangeFromBigToSmall();
            void ChangeFromSmallToFire();   
            void startInvincible();

            void startTransformingFireToBig();
            void startTransformingBigToSmall();
            void startWatingForReset();

            bool winState = false;
        public:
            // Constructor
            // Full constructor
            Mario(Vector2 pos, int lives=3,
                  MarioState form = MARIO_STATE_SMALL);
            Mario(Vector2 pos, const PlayerData& playerData);
            Mario();
            // Destructor
            ~Mario() override;

            // Setter

            void addLives(int lives);
            void setState(EntityState state);
            MarioState getForm() const;
            void addCoin(int coin);
            void addScore(int score);
            // Getter
            int getLives() const;
            int getCoin() const;
            std::list<Fireball *> *getFireballs();
            // Methods

            void startTransformingSmallToBig();
            void startTransformingBigToFire();
            void startTransformingSmallToFire();

            void die();
            void startVictoryDance(); 

            void reactOnBeingHit();
            // Game loop
            void HandleInput();
            void updateStateAndPhysic() override;
            void updateHitboxes() override;
            void Draw() override;

            void changeWinState(bool state);
			bool getWinState() const;

            std::unique_ptr<PlayerData> createMemento() const;
};