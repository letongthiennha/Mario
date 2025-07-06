#include "MonsterFactory.h"

Monster *MonsterFactory::createMonster(const std::string &type, Vector2 pos, float speed)
{
    if (type == "Goomba") {
        return new Goomba(pos, speed);
    } else if (type == "KoopaTroopa") {
        return new KoopaTroopa(pos, speed);
    } else if (type == "FlyingGoomba") {
        return new FlyingGoomba(pos, speed);
    }
    return nullptr; // Invalid type
}