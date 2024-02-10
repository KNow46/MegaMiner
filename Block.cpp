#include "Block.h"

std::string getBlockTexturePath(BlockType blockType) {
    switch (blockType) {
    case BlockType::stone:
        return "stone.jpg";

    default:
        return "stone.jpg";
    }
}

int getBlockInitialHp(BlockType blockType) {
    switch (blockType) {
    case BlockType::stone:
        return 20;

    default:
        return 20;
    }
}

Block::Block(int x, int y, int width, int height, BlockType blockType)
    : GameObject(x, y, width, height, "res/textures/"+ getBlockTexturePath(blockType)), hp(getBlockInitialHp(blockType)), blockType(blockType)
{
}

void Block::hit(int damage)
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
