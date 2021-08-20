/*
 * File CubemapTexture.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CUBEMAPTEXTURE_H
#define THREEENGINE_CUBEMAPTEXTURE_H

#include <GL/glew.h>
#include "ITexture.h"

namespace ThreeEngine {

    class Cubemap : public ITexture {
        private:
            GLuint id;

            static void LoadMapSide(GLenum sideTarget, const ImageData& imageData) ;
        public:
            GLenum texUnit = GL_TEXTURE0;
            ImageData imagesData[6]{{}};

            Cubemap();

            virtual ~Cubemap();

            void Init() override;

            void Draw() override;

            void Unbind() override;

            void UpdateTexture() const override;
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_CUBEMAPTEXTURE_H
