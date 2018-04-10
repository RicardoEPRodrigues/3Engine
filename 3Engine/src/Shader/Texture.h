/*
 * File Texture.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TEXTURE_H
#define THREEENGINE_TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include "ITexture.h"

namespace ThreeEngine {

    class Texture : public ITexture {
        private:
            GLuint id;
        public:
            GLenum texUnit = GL_TEXTURE0;
            ImageData imageData{};

            Texture();

            virtual ~Texture();

            void Init() override;

            void Draw() override;

            void Unbind() override;

            void UpdateTexture() const override;
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_TEXTURE_H
