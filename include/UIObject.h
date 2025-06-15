#pragma once
#include "DrawalbeObj.h"

class UIObject : public DrawableObj {
protected:
    virtual ~UIObject() = default;
    virtual void Draw() override = 0;
    virtual void update() = 0;
};