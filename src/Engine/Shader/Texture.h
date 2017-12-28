/*
 * File Texture.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TEXTURE_H
#define THREEENGINE_TEXTURE_H

#include <GL/glew.h>
#include <vector>
#include "../IDrawable.h"

namespace ThreeEngine {

    class Texture : public IDrawable {
        private:
            GLuint id;
        public:
            GLenum texUnit = GL_TEXTURE0;
//            std::vector<Vector4> Colors;
            unsigned char* data;
            int width, height;

            Texture();

            virtual ~Texture();

            void Init() override;

            void Draw() override;

            void Unbind();

            void UpdateTexture() const;
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_TEXTURE_H
