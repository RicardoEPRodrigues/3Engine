/*
 * File TangramAnimation.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TANGRAMANIMATION_H
#define THREEENGINE_TANGRAMANIMATION_H

#include "../../Engine/Actor.h"
#include "../../Engine/Utilities/Simulation.h"

namespace ThreeEngine {

    class TangramAnimation : public IUpdatable {
        private:
            bool toogle{false};
            std::vector<Actor::Transform> initialTransform;

        public:
            number speed = 0.005f;

            std::vector<Actor*> actors;
            std::vector<Actor::Transform> finalTransform;

            TangramAnimation();

            virtual ~TangramAnimation();

            void Init();

            void Update(milliseconds delta) override;
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_TANGRAMANIMATION_H
