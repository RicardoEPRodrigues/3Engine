/*
 * File CameraController.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CAMERACONTROLLER_H
#define THREEENGINE_CAMERACONTROLLER_H

#include "../Engine.h"

namespace ThreeEngine {

    class CameraController {
        private:
            Engine* engine;

            bool inPerspective;

            Vector2 previousMouseLocation, yawPitch;

            Matrix translation, rotation;

        public:

            CameraController();

            virtual ~CameraController();

            void Update();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERACONTROLLER_H
