/*
 * File TextureLoader.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../Debug.h"
#include "../SOIL/SOIL.h"
#include "TextureLoader.h"

namespace ThreeEngine {

    SINGLETON_IMPLEMENTATION(TextureLoader)

    void TextureLoader::LoadImageData(std::string const& filepath,
                                      ImageData& imageData) {
        imageData.data = SOIL_load_image(filepath.c_str(), &(imageData.width),
                                         &(imageData.height), nullptr,
                                         SOIL_LOAD_RGBA);
    }

    std::shared_ptr<Texture>
    TextureLoader::LoadTexture(std::string const& filepath) {
        auto texture = std::make_shared<Texture>();
        LoadImageData(filepath, texture->imageData);
        if (!texture->imageData.data) {
            Debug::Log("Image file could not be loaded");
        }
        return texture;
    }

    std::shared_ptr<Cubemap>
    TextureLoader::LoadCubemap(std::string const& front,
                               std::string const& back,
                               std::string const& top,
                               std::string const& bottom,
                               std::string const& left,
                               std::string const& right) {
        auto cubemap = std::make_shared<Cubemap>();
        LoadImageData(front, cubemap->imagesData[0]);
        LoadImageData(back, cubemap->imagesData[1]);
        LoadImageData(top, cubemap->imagesData[2]);
        LoadImageData(bottom, cubemap->imagesData[3]);
        LoadImageData(left, cubemap->imagesData[4]);
        LoadImageData(right, cubemap->imagesData[5]);

        for (auto&& data : cubemap->imagesData) {
            if (!data.data) {
                Debug::Warn("A Cubemap Image file could not be loaded");
            }
        }
        return cubemap;
    }

} /* namespace ThreeEngine */