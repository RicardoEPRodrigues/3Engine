/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TANGRAM3D_H
#define THREEENGINE_TANGRAM3D_H

#include "../Engine.h"
#include "../Shader/ShaderProgram.h"
#include "../IActor.h"

namespace ThreeEngine {

    class Tangram3D : public Engine {
        public:
            Tangram3D();

            ~Tangram3D() override;

            enum ShapeType3D {
                CUBE
            };

            ShapeType3D shapeToShow;

        protected:

            void OnInit() override;

            void CubeScene();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TANGRAM3D_H
