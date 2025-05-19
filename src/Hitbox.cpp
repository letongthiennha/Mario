#include "Hitbox.h"

Hitbox::Hitbox(Vector2 pos, Vector2 size)
{
    SetPosition(pos);
    SetSize(size);
}

bool Hitbox::CheckCollision(Hitbox &another)
{
    if(CheckCollisionRecs(this->Rect,another.Rect))
        return true;
    return false;
}

void Hitbox::Draw()
{
    return;
}

void Hitbox::SetPosition(Vector2 pos)
{
    this->Rect.x = pos.x;
    this->Rect.y = pos.y;
    this->position = pos;
}

void Hitbox::SetSize(Vector2 size)
{
    this->Rect.width = size.x;
    this->Rect.height = size.y;
    this->size = size;

}

void Hitbox::SetColor(Color color)
{
    this->color = color;
}

Vector2 Hitbox::GetPosition()
{
    return position;
}

Vector2 Hitbox::GetSize()
{
    return size;
}

Rectangle Hitbox::GetRect()
{
    return Rect;
}
