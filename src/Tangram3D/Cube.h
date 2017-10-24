/*
 * File Cube.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CUBE_H
#define THREEENGINE_CUBE_H

#include <GL/glew.h>
#include "../IActor.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"

namespace ThreeEngine {

    class Cube : public IActor {

        public:

            std::shared_ptr<ShaderProgram> shaderProgram;

            Cube();

            ~Cube() override;

            void Init() override;

            void Draw() override;

        private:

            GLuint vaoId, vboId[2];

            Vertex Vertices[6 * 6];
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CUBE_H
