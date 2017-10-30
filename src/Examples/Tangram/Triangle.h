/*
 * File Triangle.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TRIANGLE_H
#define THREEENGINE_TRIANGLE_H

#include <GL/glew.h>
#include "../../Engine/IActor.h"
#include "../../Engine/Shader/ShaderProgram.h"
#include "../../Engine/OpenGLUtils.h"

namespace ThreeEngine {

    class Triangle : public IActor {

        public:

            std::shared_ptr<ShaderProgram> shaderProgram;

            Triangle();

            explicit Triangle(GLfloat RGBA[3][4]);

            ~Triangle() override;

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId[2];

            Vertex Vertices[3];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TRIANGLE_H
