/*
 * File Cube.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CUBE_H
#define THREEENGINE_CUBE_H

#include <GL/glew.h>
#include "../Actor.h"
#include "../Shader/ShaderProgram.h"
#include "../OpenGLUtils.h"
#include "../Shapes/Mesh.h"

namespace ThreeEngine {

    class Cube : public Actor {
        private:
            void ColorUpdate();

        public:

            GLfloat color[4];

            Cube();

            ~Cube() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CUBE_H
