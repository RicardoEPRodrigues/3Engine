/*
 * File TextureLoader.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "../SOIL/SOIL.h"
#include "TextureLoader.h"

namespace ThreeEngine {

    SINGLETON_IMPLEMENTATION(TextureLoader)

    std::shared_ptr<Texture>
    TextureLoader::LoadImage(std::string const& filepath) {
        auto texture = std::make_shared<Texture>();
        texture->data = SOIL_load_image(filepath.c_str(), &(texture->width),
                                        &(texture->height), 0, SOIL_LOAD_RGBA);
        return texture;
    }

} /* namespace ThreeEngine */