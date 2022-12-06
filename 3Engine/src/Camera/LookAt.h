/*
 * File LookAt.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_LOOKAT_H
#define THREEENGINE_LOOKAT_H

#include "../Math/Matrix.h"
#include "Camera.h"

namespace ThreeEngine {

    class LookAt : public CameraMatrix {
        public:
            Vector eye, center, up, view, v, side, s, u;

            LookAt(Vector eye, Vector center, Vector up);

            explicit LookAt(Matrix other);

            void Set(Vector eye, Vector center, Vector up);

            void SetM(Vector eye, Vector v, Vector s, Vector u);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_LOOKAT_H
