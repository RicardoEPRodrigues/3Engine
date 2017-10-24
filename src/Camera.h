/*
 * File Camera.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_CAMERA_H
#define THREEENGINE_CAMERA_H

#include <GL/glew.h>
#include "IActor.h"

namespace ThreeEngine {

    class Camera : public IActor {
        private:
            GLuint vaoId, vboId;
        public:
            GLuint uniformBlockBidingID;

            Camera();

            virtual ~Camera();

            void Init() override;

            void Draw() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_CAMERA_H
