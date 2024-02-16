#include "Block.h"
#include "InterfaceManager.h"

std::string Block::getBlockTexturePath(BlockType blockType) {
    switch (blockType) {
    case BlockType::STONE:
        return "stone.jpg";
    case BlockType::GOLD:
        return "goldOre.png";
    case BlockType::DIAMOND:
        return "diamondOre.jpg";
    case BlockType::EMERALD:
        return "emeraldOre.png";
    case BlockType::IRON:
        return "ironOre.jpg";
    case BlockType::MYSTIC:
        return "mysticOre.png";

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
    if(!isDestroyed)
    {
        hp -= damage;
        if (hp <= 0)
        {
            hp = 0;
            isDestroyed = true;

            if (blockType == BlockType::GOLD)
                InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::GOLD));
            if (blockType == BlockType::DIAMOND)
                InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::DIAMOND));
            if (blockType == BlockType::IRON)
                InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::IRON));
            if (blockType == BlockType::EMERALD)
                InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::EMERALD));
            if (blockType == BlockType::MYSTIC)
                InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::MYSTIC));

        }
    }
}

int Block::getHp()
{
    return hp;
}
