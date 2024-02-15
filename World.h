#pragma once

#include "GameObject.h"
#include "Machine.h"
#include "Block.h"

#include <vector>
#include <memory>


class World {

    World() {
        machine = std::make_shared<Machine>(100, 150, 90, 60);
        addObject(machine);

        generateBlocks();

    };
    ~World() {};


public:

    static World& getInstance()
    {
        static World instance;
        return instance;
    }

    void addObject(std::shared_ptr<GameObject> object) 
    {
        objects.emplace_back(object);

        std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(object);

        if (block) 
        {
            blocks.emplace_back(block);
        }

    }

 
    void removeObject(std::shared_ptr<GameObject> object) 
    {
        std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(object);

        if (block)
        {
            blocks.erase(std::remove(blocks.begin(), blocks.end(), block), blocks.end());
        }
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

 
    void update() 
    {
        for (const auto& object : objects) 
        {
            if(object != nullptr)
            {
                if (object->getIsDestroyed() == true)
                {
                    removeObject(object);
                }
                else
                {
                    object->update();
                }
            }
        }
    }

    std::vector<std::shared_ptr<GameObject>> &getAllObjects()
    {
        return objects;
    }
    std::vector<std::shared_ptr<Block>>& getAllBlocks()
    {
        return blocks;
    }
   
  /*  void draw() {
        for (const auto& object : objects_) {
            object->draw();
        }
    }*/
    std::shared_ptr<Machine> getMachine()
    {
        return machine;
    }
private:
    void generateBlocks()
    {
        for (int i = 0; i < 50; i++)
        {
            block = std::make_shared<Block>(i * 100, 100, 100, 100, BlockType::STONE);
            addObject(block);
        }


        for (int i = 0; i < 50; i++)
        {
            block = std::make_shared<Block>(200 + i * 100, 400, 100, 100, BlockType::STONE);
            addObject(block);
        }
        for (int i = 0; i < 30; i++)
        {
            block = std::make_shared<Block>(1400 + i * 100, 300, 100, 100, BlockType::DIAMOND);
            addObject(block);
        }
        for (int i = 0; i < 30; i++)
        {
            block = std::make_shared<Block>(1400 + i * 100, 500, 100, 100, BlockType::EMERALD);
            addObject(block);
        }
        for (int i = 0; i < 30; i++)
        {
            block = std::make_shared<Block>(1400 + i * 100, 600, 100, 100, BlockType::IRON);
            addObject(block);
        }
        for (int i = 0; i < 30; i++)
        {
            block = std::make_shared<Block>(1400 + i * 100, 700, 100, 100, BlockType::IRON);
            addObject(block);
        }
        for (int i = 0; i < 30; i++)
        {
            block = std::make_shared<Block>(1400 + i * 100, 0, 100, 100, BlockType::MYSTIC);
            addObject(block);
        }


        block = std::make_shared<Block>(800, 300, 100, 100, BlockType::STONE);
        addObject(block);

        block = std::make_shared<Block>(900, 300, 100, 100, BlockType::GOLD);
        addObject(block);
        block = std::make_shared<Block>(1000, 300, 100, 100, BlockType::GOLD);
        addObject(block);
        block = std::make_shared<Block>(1100, 300, 100, 100, BlockType::GOLD);
        addObject(block);

        block = std::make_shared<Block>(600, 300, 100, 100, BlockType::DIAMOND);
        addObject(block);
        block = std::make_shared<Block>(1200, 300, 100, 100, BlockType::DIAMOND);
        addObject(block);
        block = std::make_shared<Block>(1300, 300, 100, 100, BlockType::DIAMOND);
        addObject(block);

    }

    std::vector<std::shared_ptr<GameObject>> objects;
    std::vector<std::shared_ptr<Block>> blocks;
    std::shared_ptr<Machine> machine;
    std::shared_ptr<Block> block;
};