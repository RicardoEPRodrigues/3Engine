/*
 * File Cube.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CUBE_H
#define THREEENGINE_CUBE_H

#include <GL/glew.h>
#include "../IDrawable.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"
#include "Mesh.h"

namespace ThreeEngine {

    class Cube : public IDrawable {

        public:

            Mesh mesh;

            std::shared_ptr<ShaderProgram> shaderProgram;

            GLfloat color[4];

            Cube();

            ~Cube() override;

            void Init() override;

            void Draw() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CUBE_H
