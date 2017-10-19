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
