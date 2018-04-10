/*
 * File Simulation.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_SIMULATION_H
#define THREEENGINE_SIMULATION_H

#include "../Time/Time.h"
#include <vector>
#include <memory>
#include "singleton.h"

namespace ThreeEngine {

    class IUpdatable {
        public:
            virtual ~IUpdatable() = default;

            virtual void Update(milliseconds delta) = 0;
    };

    class Simulation {
        SINGLETON_HEADER(Simulation)

        private:
            std::vector<std::unique_ptr<IUpdatable>> updatables{};
        public:
            void Add(IUpdatable* updatable);

            void Update();
    };

} /* namespace ThreeEngine */

#endif //THREEENGINE_SIMULATION_H
