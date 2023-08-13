#pragma once
#include <iostream>
#include <map>
#include "Texture.h"

class TextureManager 
{
private:
    std::map<std::string, Texture> textures;

public:
    static TextureManager& getInstance()
    {
        static TextureManager instance;
        return instance;
    }

    Texture& getTexture(const std::string& path) 
    {
        if (textures.count(path) == 0)
        {
            textures.insert(std::pair<std::string, Texture>(path, Texture(path)));
        }
        return textures[path];
    }
private:
    TextureManager() {}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
};