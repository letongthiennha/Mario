#include "MonsterFactory.h"
#include <iostream>
Monster *MonsterFactory::createMonster(const std::string &type, Vector2 pos, float speed)
{
    if (type == "Goomba") {
        return new Goomba(pos, speed);
    } else if (type == "KoopaTroopa") {
        return new KoopaTroopa(pos, speed);
    } else if (type == "FlyingGoomba") {
        return new FlyingGoomba(pos, speed);
    }else if (type == "BanzaiBill") {
        return new BanzaiBill(pos, speed);
    } else if (type == "PiranhaPlant") {
        return new PiranhaPlant(pos, speed); // 👈 Add this
    } else if (type == "Rex") {
        std::cout << "Creating Rex at " << pos.x << ", " << pos.y << std::endl;
        return new Rex(pos, speed);
    }
    return nullptr; // Invalid type
}