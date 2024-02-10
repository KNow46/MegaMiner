#include "Block.h"

std::string getBlockTexturePath(BlockType blockType) {
    switch (blockType) {
    case BlockType::stone:
        return "stone.jpg";

    default:
        return "stone.jpg";
    }
}

Block::Block(int x, int y, int width, int height, int initialHp, BlockType blockType)
    : GameObject(x, y, width, height, "res/textures/"+ getBlockTexturePath(blockType)), hp(initialHp), blockType(blockType)
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
