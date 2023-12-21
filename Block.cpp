#include "Block.h"

Block::Block(int x, int y, int width, int height, int initialHp, std::string texturePath)
    : GameObject(x, y, width, height, "res/textures/board.png"), hp(initialHp)
{
}

void Block::getHit(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        hp = 0;
        isDestroyed = true;
    }
}

int Block::getHp()
{
    return hp;
}
