/*
 * File Simulation.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Simulation.h"

namespace ThreeEngine {
    SINGLETON_IMPLEMENTATION(Simulation)

    void Simulation::Add(IUpdatable* updatable) {
        updatables.push_back(std::unique_ptr<IUpdatable>(updatable));
    }

    void Simulation::Update() {
        for (std::unique_ptr<IUpdatable>& updatable : updatables) {
            updatable->Update(Time::Delta());
        }
    }
} /* namespace ThreeEngine */