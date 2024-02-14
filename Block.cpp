#include "Block.h"
#include "InterfaceManager.h"

std::string getBlockTexturePath(BlockType blockType) {
    switch (blockType) {
    case BlockType::STONE:
        return "stone.jpg";
    case BlockType::GOLD:
        return "goldOre.png";
    case BlockType::DIAMOND:
        return "diamondOre.jpg";

    default:
        return "stone.jpg";
    }
}

int getBlockInitialHp(BlockType blockType) {
    switch (blockType) {
    case BlockType::STONE:
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
        
        if(blockType == BlockType::GOLD)
            InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::GOLD));
        if (blockType == BlockType::DIAMOND)
            InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::DIAMOND));

    }
}

int Block::getHp()
{
    return hp;
}
