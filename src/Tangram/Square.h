/*
 * File Square.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_SQUARE_H
#define THREEENGINE_SQUARE_H

#include <GL/glew.h>
#include "../IActor.h"
#include "../Shader/ShaderProgram.h"
#include "../Math/Matrix.h"

namespace ThreeEngine {

    class Square : public IActor {

        public:

            typedef struct {
                GLfloat XYZW[4];
                GLfloat RGBA[4];
            } Vertex;
            Matrix transform;

            std::shared_ptr<ShaderProgram> shaderProgram;

            Square();

            Square(Vertex vertices[6]);

            virtual ~Square();

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId[1];

            Vertex Vertices[6];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_SQUARE_H
