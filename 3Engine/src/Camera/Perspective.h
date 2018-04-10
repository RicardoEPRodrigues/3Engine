/*
 * File Perspective.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_PERSPECTIVE_H
#define THREEENGINE_PERSPECTIVE_H

#include "../Math/Matrix.h"

namespace ThreeEngine {

    class Perspective : public Matrix {
        public:
            number angle, d;
            Perspective(number FOVy, number aspect, number zNear, number zFar);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_PERSPECTIVE_H
