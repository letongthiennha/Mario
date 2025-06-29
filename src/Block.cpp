#include "raylib.h"
#include "Block.h"

Block::Block() : Block( Vector2{0,0}, Vector2{0,0}, BLACK, 0 , 0){
}

Block::Block(Vector2 pos, Vector2 size, Color color) : Block(pos,size, color, 0 ,1){
}

Block::Block(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame) : 
    Block(pos, size, color, frameTime, maxFrame, 0){

}

Block::Block(Vector2 pos, Vector2 size, Color color, float frameTime, int maxFrame, int earnPoints) :
    Entity(pos, size,Vector2{0,0}, color, frameTime, maxFrame, DIRECTION_RIGHT), hit(false) {
    this->hitToDie = 1; // Default number of hits to destroy the block
    this->updateHitboxes();
}

Block::~Block() = default;



void Block::doHit(Mario& mario, Map &map) {
}

void Block::resetHit() {
    this->hit = false;
}