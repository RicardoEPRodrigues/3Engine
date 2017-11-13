/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TANGRAM3D_H
#define THREEENGINE_TANGRAM3D_H

#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderProgram.h"
#include "../../Engine/Controllers/FreeCameraController.h"

namespace ThreeEngine {

    class Tangram3D : public Engine {
        public:
            Tangram3D();

            ~Tangram3D() override;

            enum ShapeType3D {
                CUBE
            };

            ShapeType3D shapeToShow;

            FreeCameraController controller;

        protected:

            void OnInit() override;

            void CubeScene();

            void OnReshape(int w, int h) override;

            void PreDraw() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TANGRAM3D_H
