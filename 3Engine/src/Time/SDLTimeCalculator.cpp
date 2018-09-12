/*
 * File SDLTimeCalculator.cpp in project 3EngineGlobal
 * 
 * Copyright (C) Ricardo Rodrigues 2018 - All Rights Reserved
 */
#include <SDL2/SDL_timer.h>
#include "SDLTimeCalculator.h"

namespace ThreeEngine {

    SDLTimeCalculator::SDLTimeCalculator() : _startTime((milliseconds) SDL_GetTicks()),
                                             nowTime((milliseconds) SDL_GetTicks()), deltaTime(0) {}

    SDLTimeCalculator::~SDLTimeCalculator() = default;

    void SDLTimeCalculator::update() {
        auto nowT = (milliseconds) SDL_GetTicks();
        deltaTime = nowT - nowTime;
        nowTime = nowT;
    }

    milliseconds SDLTimeCalculator::startTime() {
        return _startTime;
    }

    milliseconds SDLTimeCalculator::now() {
        return nowTime;
    }

    milliseconds SDLTimeCalculator::delta() {
        return deltaTime;
    }

} /* namespace 3EngineGlobal */