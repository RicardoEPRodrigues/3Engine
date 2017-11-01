/*
 * File GlutTimeCalculator.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <GL/freeglut.h>
#include "GlutTimeCalculator.h"

namespace ThreeEngine {

    GlutTimeCalculator::GlutTimeCalculator() : _startTime(glutGet(GLUT_ELAPSED_TIME)),
                                               nowTime(glutGet(GLUT_ELAPSED_TIME)), deltaTime(0) { }

    GlutTimeCalculator::~GlutTimeCalculator() = default;

    void GlutTimeCalculator::update() {
        milliseconds nowT = glutGet(GLUT_ELAPSED_TIME);
        deltaTime = nowT - nowTime;
        nowTime = nowT;
    }

    milliseconds GlutTimeCalculator::startTime() {
        return _startTime;
    }

    milliseconds GlutTimeCalculator::now() {
        return nowTime;
    }

    milliseconds GlutTimeCalculator::delta() {
        return deltaTime;
    }

} /* namespace Divisaction */