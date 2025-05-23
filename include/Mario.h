#pragma once
#include "Entity.h"
#include "MarioState.h"
#include "Fireball.h"
#include "ResourceManager.h"
#include <vector>
class Mario: public Entity{
    private:
    //Image
        Texture2D sprite;
        // Properties
        int lives;
        bool isDucking;
        MarioState form;
        std::vector<Fireball*>fireballs;

    // Special effects
    // Invincibility when hit
        // The player is invincible for a short time after being hit
        bool isInvincible;
        float invincibleFrameTime;
        float invincibleAcum;
        int invincibleFrame;
        int invincibleMaxFrame;
    // Immortal when eating immortal star
        // In this state it can kill any thing
        bool isImmortal;
        float immortalFrameTime;
        float immortalAcum;
        int immortalFrame;
        int immortalMaxFrame;
    //Timing Event
        // Accelerating
        int normalSpeedX;
        int accelerationX;
        // Jumping
        float gravity;
        float jumpInitSpeed;

    public:
        // Constructor
        Mario();
        Mario(Vector2 pos, Vector2 size, MarioState state, Color color, int lives,
              MarioState state1);
        // Destructor
        ~Mario() override;
        // Setter
        void setSprite(Texture2D sprite);
        void setLives(int lives);
        void Duck();
        void setState(MarioState state);
        void setGravity(float gravity);
        void setFireballs(std::vector<Fireball *> fireballs);
        // Getter
        Texture2D getSprite() const;
        int getLives() const;
        bool getIsDucking() const;
        MarioState getState() const;
        float getGravity() const;
        std::vector<Fireball *> getFireballs() const;
        // Methods
        void jump();
        void duck();
        void fire();
        void moveLeft();
        void moveRight();
        void moveNoWhere();
        // Game loop
        void HandleInput();
        void updateSprite();
        void update();
        void Draw() override;
};