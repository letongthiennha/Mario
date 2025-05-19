#pragma once
#include "raylib.h"
#include "DrawalbeObj.h"

class Hitbox: public virtual DrawableObj{
    public:
        Hitbox(Vector2 pos, Vector2 size);

        // Logic
        bool CheckCollision(Hitbox &another);
        // Update
        void Draw() override;

        // Setter
        void SetPosition(Vector2 pos);
        void SetSize(Vector2 size);
        void SetColor(Color color);
        // Getter
        Vector2 GetPosition();
        Vector2 GetSize();
        
        Color getColor();

        Rectangle GetRect();

    private:
        Vector2 position;
        Vector2 size;

        Rectangle Rect;

        Color color;
};
