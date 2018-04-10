/*
 * File MoveController.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MOVECONTROLLER_H
#define THREEENGINE_MOVECONTROLLER_H

#include "../../Engine/Actor.h"
#include "../../Engine/Utilities/Simulation.h"

namespace ThreeEngine {

    class MoveController : public IUpdatable {
        public:
            number angle;
            Vector front;

            Actor* actor;

            MoveController();

            virtual ~MoveController();

            void Update(milliseconds delta) override;
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_MOVECONTROLLER_H
