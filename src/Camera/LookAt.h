/*
 * File LookAt.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_LOOKAT_H
#define THREEENGINE_LOOKAT_H

#include "../Math/Matrix.h"

namespace ThreeEngine {

    class LookAt : public Matrix{
        public:
            Vector eye, center, up, view, v, side, s, u;

            LookAt(Vector eye, Vector center, Vector up);

            void Set(Vector eye, Vector center, Vector up);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_LOOKAT_H
