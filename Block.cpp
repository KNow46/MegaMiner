#pragma once
#include "Block.h"
#include "InterfaceManager.h"
#include <iostream>
std::string Block::getBlockTexturePath(BlockType blockType) {
    switch (blockType) {
    case BlockType::STONE:
        return "stone.png";
    case BlockType::GOLD:
        return "goldOre.png";
    case BlockType::DIAMOND:
        return "diamondOre.png";
    case BlockType::EMERALD:
        return "emeraldOre.png";
    case BlockType::IRON:
        return "ironOre.png";
    case BlockType::MYSTIC:
        return "mysticOre.png";
    case BlockType::RUBY:
        return "rubyOre.png";

    default:
        return "stone.png";
    }
}

int getBlockInitialHp(BlockType blockType) {
    switch (blockType) {
    case BlockType::STONE:
        return 50;

    default:
        return 50;
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
        int destructionStage = (1.0 - static_cast<float>(hp) /getBlockInitialHp(blockType)) * 5;
  /*      float test = (static_cast<float>(hp) / getBlockInitialHp(blockType));

        std::cout << hp << std::endl;
        std::cout << getBlockInitialHp(blockType) << std::endl;
        std::cout << test << std::endl;*/

        if (destructionStage > 0)
        {
            aggregatedObjects.clear();
            aggregatedObjects.push_back(std::make_shared<InterfaceObject>(x, y, width, height, "res/textures/crack/" +
                std::to_string(destructionStage) + ".png"));
        }

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
            if (blockType == BlockType::RUBY)
                InterfaceManager::getInstance().getStorage()->addItem(Item(Item::ItemType::RUBY));

        }
    }
}

int Block::getHp()
{
    return hp;
}
