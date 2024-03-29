#pragma once

#include "GameObject.h"
#include "Machine.h"
#include "Block.h"
#include "Shop.h"
#include "GasStation.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "Timer.h"

class World {


    std::vector<std::shared_ptr<GameObject>> objects;
    std::vector<std::shared_ptr<Block>> blocks;
    std::vector<std::shared_ptr<Block>> visibleBlocks;
    std::shared_ptr<Machine> machine;
    std::shared_ptr<Shop> shop;
    std::shared_ptr<GasStation> gasStation;
    std::shared_ptr<Block> block;
    std::vector<std::vector<std::vector<std::shared_ptr<Block>>>> sectors;
    std::vector<std::shared_ptr<Block>> adjacentBlocks;

    int sectorSize = 6;
    int mapWidth = sectorSize * 20;
    int mapHeight = sectorSize * 20;
    int blocksSize = 130;
    int time = 0;

    World()
    {
        

        objects.reserve(mapWidth * mapHeight * 1.1);

        shop = std::make_shared<Shop>(0, -500,500, 500);
        gasStation = std::make_shared<GasStation>(1000, -500, 500, 500);

        machine = std::make_shared<Machine>(100, 0, 110, 90);
        addObject(machine);

        int numVerticalSectors = mapHeight / sectorSize;
        int numHorizontalSectors = mapWidth / sectorSize;
        sectors.resize(numVerticalSectors, std::vector<std::vector<std::shared_ptr<Block>>>(numHorizontalSectors));
        
        
        generateBlocks();
        
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                visibleBlocks.emplace_back(blocks[i + j * mapWidth]);
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
   
        shop->update();
       
        machine->update();
        gasStation->update();
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
                visibleBlocks.emplace_back(block);
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
                            adjacentBlocks.emplace_back(block);
                      
                         
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
    std::shared_ptr<Shop> getShop()
    {
        return shop;
    }
    std::shared_ptr<GasStation> getGasStation()
    {
        return gasStation;
    }
    void reset()
    {
        objects.clear();
        blocks.clear();
        visibleBlocks.clear();
        sectors.clear();

        int numVerticalSectors = mapHeight / sectorSize;
        int numHorizontalSectors = mapWidth / sectorSize;
        sectors.resize(numVerticalSectors, std::vector<std::vector<std::shared_ptr<Block>>>(numHorizontalSectors));

        machine->setX(0);
        machine->setY(-150);
        machine->getDrill().resetLevel();
        
        generateBlocks();

        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                visibleBlocks.emplace_back(blocks[i + j * mapWidth]);
            }
        }

        setAdjacentBlocks();

    }
private:

    void generateBlocks()
    {
        std::srand(std::time(nullptr));

        for (int i = 0; i < mapHeight; i++)
        {
            for (int j = 0; j < mapWidth; j++)
            { 

                BlockType blockType = drawBlockType(i/10);

                /*int random = std::rand() % 100;
                if (random <= 70)
                {
                    blockType = BlockType::STONE;
                }
                else if (random <= 75)
                {
                    blockType = BlockType::RUBY;
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
                }*/

                block = std::make_shared<Block>(j * blocksSize, i * blocksSize, blocksSize, blocksSize, blockType);
                addObject(block);

                int sectorRow = i / sectorSize;
                int sectorCol = j / sectorSize;

                
                int blockX = j % sectorSize;
                int blockY = i % sectorSize;

                std::shared_ptr<Block> block = std::make_shared<Block>(j * blocksSize, i * blocksSize, blocksSize, blocksSize, blockType);

                
                sectors[sectorRow][sectorCol].emplace_back(block);
 
            }
        }


    }

    BlockType drawBlockType(int depthLevel)
    {
        int random = std::rand() % 100;

        if (depthLevel == 0)
        {
            if (random < 20)
                return BlockType::IRON;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 1)
        {
            if (random < 20)
                return BlockType::IRON;
            else if (random < 30)
                return BlockType::GOLD;
            else 
                return BlockType::STONE;
        }
        else if (depthLevel == 2)
        {
            if (random < 15)
                return BlockType::IRON;
            else if (random < 30)
                return BlockType::GOLD;
            else if (random < 35)
                return BlockType::DIAMOND;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 3)
        {
            if (random < 15)
                return BlockType::IRON;
            else if (random < 30)
                return BlockType::GOLD;
            else if (random < 35)
                return BlockType::DIAMOND;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 3)
        {
            if (random < 10)
                return BlockType::IRON;
            else if (random < 25)
                return BlockType::GOLD;
            else if (random < 35)
                return BlockType::DIAMOND;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 4)
        {
            if (random < 10)
                return BlockType::IRON;
            else if (random < 20)
                return BlockType::GOLD;
            else if (random < 30)
                return BlockType::DIAMOND;
            else if (random < 35)
                return BlockType::EMERALD;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 5)
        {
            if (random < 10)
                return BlockType::IRON;
            else if (random < 20)
                return BlockType::GOLD;
            else if (random < 30)
                return BlockType::DIAMOND;
            else if (random < 40)
                return BlockType::EMERALD;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 6)
        {
            if (random < 10)
                return BlockType::IRON;
            else if (random < 15)
                return BlockType::GOLD;
            else if (random < 20)
                return BlockType::DIAMOND;
            else if (random < 30)
                return BlockType::EMERALD;
            else if (random < 35)
                return BlockType::MYSTIC;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 7)
        {
            if (random < 5)
                return BlockType::IRON;
            else if (random < 10)
                return BlockType::GOLD;
            else if (random < 20)
                return BlockType::DIAMOND;
            else if (random < 30)
                return BlockType::EMERALD;
            else if (random < 40)
                return BlockType::MYSTIC;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 8)
        {
            if (random < 5)
                return BlockType::IRON;
            else if (random < 10)
                return BlockType::GOLD;
            else if (random < 20)
                return BlockType::DIAMOND;
            else if (random < 30)
                return BlockType::EMERALD;
            else if (random < 35)
                return BlockType::MYSTIC;
            else if (random < 40)
                return BlockType::RUBY;
            else
                return BlockType::STONE;
        }
        else if (depthLevel == 9)
        {
            if (random < 5)
                return BlockType::IRON;
            else if (random < 10)
                return BlockType::GOLD;
            else if (random < 20)
                return BlockType::DIAMOND;
            else if (random < 30)
                return BlockType::EMERALD;
            else if (random < 40)
                return BlockType::MYSTIC;
            else if (random < 50)
                return BlockType::RUBY;
            else
                return BlockType::STONE;
         }



        return BlockType::STONE;
    }
  
};