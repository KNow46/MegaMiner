#include "Animation.h"
#include <filesystem>

namespace fs = std::filesystem;

Animation::Animation(int x, int y, int width, int height, std::string folderPath) :
	GameObject(x, y, width, height, "res/textures/empty.png"), currentFrame(-1)
{
    framesCount = 0;

    std::string fileName;

    for (const auto& entry : fs::directory_iterator(folderPath))
    {
        if (fs::is_regular_file(entry.path())) 
        {
           
            fileName = entry.path().filename().string();
            if(entry.path().extension().string() == ".png" || entry.path().extension().string() == ".jpg")
            {
                std::string framePath = folderPath + "/" + fileName;
                animationFrames.emplace_back(TextureManager::getInstance().getTexture(framePath));

                framesCount++;
            }
        }
    }
    

}

const Texture& Animation::getTexture()
{
    currentFrame++;
    if (currentFrame >= framesCount)
        currentFrame = 0;
    return animationFrames[currentFrame];
}
