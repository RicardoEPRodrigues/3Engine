/*
 * File CameraController.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CAMERACONTROLLERROT_H
#define THREEENGINE_CAMERACONTROLLERROT_H

#include "../Math/Quat.h"
#include "../Camera/Camera.h"

namespace ThreeEngine {

    class SphereCameraController {
        private:
            class Engine* engine;

            bool inPerspective;

            Vector2 previousMouseLocation, yawPitch;

            Quat quat;

            Vector translation;


            Vector2 LockMouse();

            void UnlockMouse();

        public:

            Camera* camera;

            explicit SphereCameraController(class Engine* engine);

            virtual ~SphereCameraController();

            void Update();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERACONTROLLERROT_H
