#pragma once
#include "UIObject.h"

class Slider : public UIObject {
public:
    Slider(Vector2 position, float width, float minValue, float maxValue, float initialValue);

    void update() override;
    void Draw() override;

    float getValue() const;
    float getRatio() const;
    void setRatio(float ratio);
    Rectangle getTrackRect() const;

private:
    float minValue, maxValue;
    float ratio;
    float width;
    bool dragging = false;
    Rectangle handle;
    Rectangle track;
};