/*
 * File CameraController.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CAMERACONTROLLERROT_H
#define THREEENGINE_CAMERACONTROLLERROT_H

#include "../../Engine/Engine.h"
#include "../../Engine/Math/Quat.h"

namespace ThreeEngine {

    class CameraControllerRot {
        private:
            Engine* engine;

            bool inPerspective, useQuat;

            Vector2 previousMouseLocation, yawPitch;

            Matrix translation, rotation;

            Quat quat;

        public:

            CameraControllerRot();

            virtual ~CameraControllerRot();

            void Update();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERACONTROLLERROT_H
