/*
 * File ColoredActor.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_COLOREDACTOR_H
#define THREEENGINE_COLOREDACTOR_H

#include "../../Engine/Actor.h"

namespace ThreeEngine {

    class ColoredActor : public Actor {
        private:
            void ColorUpdate();

        public:
            Vector4 color;

            ColoredActor();
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_COLOREDACTOR_H
