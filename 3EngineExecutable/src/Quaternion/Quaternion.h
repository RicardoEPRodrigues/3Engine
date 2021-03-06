/*
 * File Tangram.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_QUATERNION_H
#define THREEENGINE_QUATERNION_H

#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderProgram.h"
#include "../../Engine/Controllers/SphereCameraController.h"

namespace ThreeEngine {

    class Quaternion : public Engine {
        public:
            Quaternion();

            ~Quaternion() override;

            Camera* camera;

            enum ShapeType3D {
                CUBE
            };

            ShapeType3D shapeToShow;

            SphereCameraController controller;

        protected:

            void OnInit() override;

            void CubeScene();

            void OnReshape(int w, int h) override;

            void PreDraw() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_QUATERNION_H
