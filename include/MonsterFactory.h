#pragma once
#include "Goomba.h"
#include "KoopaTroopa.h"
#include "FlyingGoomba.h"
#include <vector>
#include "Monster.h"
#include "raylib.h"
class MonsterFactory {
public:
    static Monster *createMonster(const std::string &type, Vector2 pos, float speed);
};