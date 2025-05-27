#pragma once
#include "raylib.h"
#include "DrawalbeObj.h"

class Hitbox: public virtual DrawableObj{
    public:
        // Constructor
        Hitbox();
        Hitbox(Vector2 pos, Vector2 size, Color color);

        // Logic
        bool CheckCollision(const Rectangle &rect) const;
        // Update
        void Draw() override;

        // Setter
        void SetPosition(Vector2 pos);
        void SetSize(Vector2 size);
        void SetColor(Color color);
        // Getter
        Vector2 GetPosition() const;
        Vector2 GetSize() const;
        
        Color GetColor() const;

        Rectangle GetRect() const;

    private:
        Vector2 position;
        Vector2 size;

        Rectangle Rect;

        Color color;
};
