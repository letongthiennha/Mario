#include "Hitbox.h"
#include "Entity.h"

Hitbox::Hitbox():
    position({0,0}),
    size({0,0}),
    Rect({0,0,0,0}),
    color(WHITE)
{
}

Hitbox::Hitbox(Vector2 pos, Vector2 size, Color color)
{
    SetPosition(pos);
    SetSize(size);
    SetColor(color);
}

bool Hitbox::CheckCollision(const Hitbox &another) const
{
    if(CheckCollisionRecs(this->GetRect(),another.GetRect()))
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

Vector2 Hitbox::GetPosition() const
{
    return position;
}

Vector2 Hitbox::GetSize() const
{
    return size;
}

Color Hitbox::GetColor() const
{
    return color;
}

Rectangle Hitbox::GetRect() const
{
    return Rect;
}
