/*
 * File SkySphere.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "SkySphere.h"

namespace ThreeEngine {

    SkySphere::SkySphere() : Actor() {
        preDraw = [this]() {
            glCullFace(GL_FRONT);
        };
        postDraw = [this]() {
            glCullFace(GL_BACK);
        };
    }

    SkySphere::~SkySphere() = default;

} /* namespace ThreeEngine */