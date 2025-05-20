#pragma once
#include "raylib.h"

class DrawableObj{
    protected:
    virtual~DrawableObj() = default;
    virtual void Draw() = 0;
};