/*
 * File Parallelogram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_PARALLELOGRAM3D_H
#define THREEENGINE_PARALLELOGRAM3D_H

#include <GL/glew.h>
#include "../IDrawable.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"

namespace ThreeEngine {

    class Parallelogram3D : public IDrawable {

        public:

            std::shared_ptr<ShaderProgram> shaderProgram;

            GLfloat color[4];

            Parallelogram3D();

            explicit Parallelogram3D(GLfloat RGBA[6][4]);

            ~Parallelogram3D() override;

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId;

            Vertex Vertices[36];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_PARALLELOGRAM3D_H
