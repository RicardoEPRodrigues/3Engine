/*
 * File Parallelogram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_PARALLELOGRAM_H
#define THREEENGINE_PARALLELOGRAM_H

#include <GL/glew.h>
#include "../IActor.h"
#include "../Shader/ShaderProgram.h"
#include "../Math/Matrix.h"

namespace ThreeEngine {

    class Parallelogram : public IActor {

        public:

            typedef struct {
                GLfloat XYZW[4];
                GLfloat RGBA[4];
            } Vertex;
            Matrix transform;

            std::shared_ptr<ShaderProgram> shaderProgram;

            Parallelogram();

            Parallelogram(Vertex vertices[6]);

            virtual ~Parallelogram();

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId[1];

            Vertex Vertices[6];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_PARALLELOGRAM_H
