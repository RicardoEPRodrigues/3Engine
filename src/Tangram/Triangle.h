/*
 * File Triangle.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TRIANGLE_H
#define THREEENGINE_TRIANGLE_H

#include <GL/glew.h>
#include "../IActor.h"
#include "../Shader/ShaderProgram.h"
#include "../Math/Matrix.h"

namespace ThreeEngine {

    class Triangle : public IActor {

        public:

            typedef struct {
                GLfloat XYZW[4];
                GLfloat RGBA[4];
            } Vertex;
            Matrix transform;

            ShaderProgram* shaderProgram;

            Triangle();

            Triangle(Vertex vertices[3]);

            virtual ~Triangle();

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId[2];

            GLint matrixUniformId;

            Vertex Vertices[3];

            GLubyte Indices[3];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TRIANGLE_H
