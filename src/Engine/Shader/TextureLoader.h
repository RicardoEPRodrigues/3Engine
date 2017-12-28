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
#include "Cubemap.h"

namespace ThreeEngine {

    class TextureLoader {
        SINGLETON_HEADER(TextureLoader)

        public:
            void
            LoadImageData(std::string const& filepath, ImageData& imageData);

            std::shared_ptr<Texture> LoadTexture(std::string const& filepath);

            std::shared_ptr<Cubemap> LoadCubemap(std::string const& front,
                                                 std::string const& back,
                                                 std::string const& top,
                                                 std::string const& bottom,
                                                 std::string const& left,
                                                 std::string const& right);
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_TEXTURELOADER_H
