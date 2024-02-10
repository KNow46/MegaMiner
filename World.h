#pragma once

#include "GameObject.h"
#include "Machine.h"
#include "Block.h"

#include <vector>
#include <memory>


class World {

    World() {
        machine = std::make_shared<Machine>(100, 150, 150, 100);
        addObject(machine);

        for (int i = 0; i < 10; i++)
        {
            block = std::make_shared<Block>(i*100, 100, 100, 100,  BlockType::stone);
            addObject(block);
        }

        for (int i = 0; i < 10; i++)
        {
            block = std::make_shared<Block>(200+i * 100, 400, 100, 100, BlockType::stone);
            addObject(block);
        }

        block = std::make_shared<Block>(800, 300, 100, 100, BlockType::stone);
        addObject(block);

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
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

 
    void update() 
    {
        for (const auto& object : objects) 
        {
            object->update();
            if (object->getIsDestroyed() == true)
            {
                removeObject(object);
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

    std::vector<std::shared_ptr<GameObject>> objects;
    std::vector<std::shared_ptr<Block>> blocks;
    std::shared_ptr<Machine> machine;
    std::shared_ptr<Block> block;
};