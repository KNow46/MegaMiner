#pragma once

#include "GameObject.h"
#include "Machine.h"
#include "Block.h"

#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

class World {

    World() {
        machine = std::make_shared<Machine>(100, -150, 90, 60);
        addObject(machine);

        generateBlocks();

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                visibleBlocks.push_back(blocks[i + j * mapWidth]);
            }
        }
        
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
          
            visibleBlocks.erase(std::remove(visibleBlocks.begin(), visibleBlocks.end(), block), visibleBlocks.end());
        
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
        time++;
        if (time > 10)
        {
            updateVisibleBlocks();
            time = 0;
        }
    }

    void updateVisibleBlocks() {
        visibleBlocks.clear();
        int horizontalVision = 5;
        int verticalVision = 4;

        int machineX = machine->getX() / 150; // Za³ó¿my, ¿e szerokoœæ bloku to 150
        int machineY = machine->getY() / 150; // Za³ó¿my, ¿e wysokoœæ bloku to 150

        for (const auto& block : blocks) {
            int blockX = block->getX() / 150; // Za³ó¿my, ¿e szerokoœæ bloku to 150
            int blockY = block->getY() / 150; // Za³ó¿my, ¿e wysokoœæ bloku to 150

            // Sprawdzenie, czy blok jest w obszarze widocznym wokó³ maszyny
            if (blockX >= machineX - horizontalVision && blockX <= machineX + horizontalVision &&
                blockY >= machineY - verticalVision && blockY <= machineY + verticalVision) {
                visibleBlocks.push_back(block);
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
    std::vector<std::shared_ptr<Block>>& getVisibleBlocks()
    {
        return visibleBlocks;
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
        std::srand(std::time(nullptr));

        for (int i = 0; i < mapHeight; i++)
        {
            for (int j = 0; j < mapWidth; j++)
            { 
                BlockType blockType;
                int random = std::rand() % 100;
                if (random <= 75)
                {
                    blockType = BlockType::STONE;
                }
                else if (random <= 80)
                {
                    blockType = BlockType::GOLD;
                }
                else if (random <= 85)
                {
                    blockType = BlockType::EMERALD;
                }
                else if (random <= 90)
                {
                    blockType = BlockType::DIAMOND;
                }
                else  if (random <= 95)
                {
                    blockType = BlockType::MYSTIC;
                }
                else
                {
                    blockType = BlockType::IRON;
                }

                block = std::make_shared<Block>(j * 150, i * 150, 150, 150, blockType);
                addObject(block);
            }
        }

    }

    std::vector<std::shared_ptr<GameObject>> objects;
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::shared_ptr<Block>> visibleBlocks;
    std::vector<std::vector<std::shared_ptr<Block>>> blocks2d;
    std::shared_ptr<Machine> machine;
    std::shared_ptr<Block> block;
    int mapWidth = 100;
    int mapHeight = 100;
    int time = 0;
};