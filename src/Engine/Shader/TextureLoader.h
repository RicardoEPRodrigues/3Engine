/*
 * File TextureLoader.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TEXTURELOADER_H
#define THREEENGINE_TEXTURELOADER_H

#include <memory>
#include "../Utilities/singleton.h"
#include "Texture.h"

namespace ThreeEngine {

    class TextureLoader {
            SINGLETON_HEADER(TextureLoader)
        public:
            std::shared_ptr<Texture> LoadImage(std::string const& filepath);
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_TEXTURELOADER_H
