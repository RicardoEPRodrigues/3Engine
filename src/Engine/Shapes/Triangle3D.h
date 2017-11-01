/*
 * File Triangle.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TRIANGLE3D_H
#define THREEENGINE_TRIANGLE3D_H

#include <GL/glew.h>
#include "../IActor.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"

namespace ThreeEngine {

    class Triangle3D : public IActor {

        public:

            std::shared_ptr<ShaderProgram> shaderProgram;

            GLfloat color[4];

            Triangle3D();

            explicit Triangle3D(GLfloat RGBA[3][4]);

            ~Triangle3D() override;

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId;

            Vertex Vertices[24];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TRIANGLE3D_H
