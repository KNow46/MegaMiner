#pragma once

#include "GameObject.h"
#include "Machine.h"
#include "Block.h"

#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

class World {

    World()
    {
        shop = std::make_shared<GameObject>(0, -500,500, 500, "res/textures/shop.png");

        machine = std::make_shared<Machine>(100, -150, 90, 60);
        addObject(machine);

        int numVerticalSectors = mapHeight / sectorSize;
        int numHorizontalSectors = mapWidth / sectorSize;
        sectors.resize(numVerticalSectors, std::vector<std::vector<std::shared_ptr<Block>>>(numHorizontalSectors));
        
        
        generateBlocks();
        
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                visibleBlocks.push_back(blocks[i + j * mapWidth]);
            }
        }

        setAdjacentBlocks();
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
            adjacentBlocks.erase(std::remove(adjacentBlocks.begin(), adjacentBlocks.end(), block), adjacentBlocks.end());
        }
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

 
    void update() 
    {
        machine->update();
        for (const auto& object : visibleBlocks) 
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
        if (time % 3 == 0)
       {
            updateVisibleBlocks();
             setAdjacentBlocks();
              time = 0;
  

        }  
    }

    void updateVisibleBlocks() {
       
        visibleBlocks.clear();
        int horizontalVision = 6;
        int verticalVision = 4;

        int machineX = machine->getX() / blocksSize;
        int machineY = machine->getY() / blocksSize;

        for (const auto& block : adjacentBlocks) {
            int blockX = block->getX() / blocksSize;
            int blockY = block->getY() / blocksSize;

            if (blockX >= machineX - horizontalVision && blockX <= machineX + horizontalVision &&
                blockY >= machineY - verticalVision && blockY <= machineY + verticalVision) {
                visibleBlocks.push_back(block);
            }
        }
    }


    std::pair<int, int> getMachineSector() const {
        int machineX = machine->getX() / blocksSize; 
        int machineY = machine->getY() / blocksSize;

       
        int sectorRow = machineY / sectorSize;
        int sectorCol = machineX / sectorSize;

        return std::make_pair(sectorRow, sectorCol);
    }

   void setAdjacentBlocks()
   {
       adjacentBlocks.clear();

        std::pair<int, int> machineSector = getMachineSector();
        int machineSectorRow = machineSector.first;
        int machineSectorCol = machineSector.second;


        for (int i = machineSectorRow - 1; i <= machineSectorRow + 1; ++i) 
        {
            for (int j = machineSectorCol - 1; j <= machineSectorCol + 1; ++j) 
            {
                 if (i >= 0 && i < sectors.size() && j >= 0 && j < sectors[0].size()) 
                 {
                  
                     for(auto & block: sectors[i][j])
                     {
                         if (block->getIsDestroyed() == false)
                            adjacentBlocks.push_back(block);
                      
                         
                     }
                    
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
    std::vector<std::shared_ptr<Block>>& getVisibleBlocks()
    {
        return visibleBlocks;
    }
   
    std::shared_ptr<Machine> getMachine()
    {
        return machine;
    }
    std::shared_ptr<GameObject> getShop()
    {
        return shop;
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

                block = std::make_shared<Block>(j * blocksSize, i * blocksSize, blocksSize, blocksSize, blockType);
                addObject(block);

                int sectorRow = i / sectorSize;
                int sectorCol = j / sectorSize;

                
                int blockX = j % sectorSize;
                int blockY = i % sectorSize;

                std::shared_ptr<Block> block = std::make_shared<Block>(j * blocksSize, i * blocksSize, blocksSize, blocksSize, blockType);

                
                sectors[sectorRow][sectorCol].push_back(block);
 
            }
        }


    }

    std::vector<std::shared_ptr<GameObject>> objects;
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::shared_ptr<Block>> visibleBlocks;
    std::vector<std::vector<std::shared_ptr<Block>>> blocks2d;
    std::shared_ptr<Machine> machine;
    std::shared_ptr<GameObject> shop;
    std::shared_ptr<Block> block;
    std::vector<std::vector<std::vector<std::shared_ptr<Block>>>> sectors;
    std::vector<std::shared_ptr<Block>> adjacentBlocks;

    int sectorSize = 6;
    int mapWidth = sectorSize * 40;
    int mapHeight = sectorSize * 40;
    int blocksSize = 120;
    int time = 0;
};