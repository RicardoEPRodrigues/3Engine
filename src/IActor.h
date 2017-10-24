/*
 * File Actor.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ACTOR_H
#define THREEENGINE_ACTOR_H

#include "Math/Matrix.h"

namespace ThreeEngine {

    class IActor {
        public:
            Matrix transform;

            virtual ~IActor() = default;

            virtual void Init() = 0;

            virtual void Draw() =0;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_ACTOR_H
