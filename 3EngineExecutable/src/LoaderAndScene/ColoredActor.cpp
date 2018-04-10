/*
 * File ColoredActor.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "ColoredActor.h"

namespace ThreeEngine {

    ColoredActor::ColoredActor() : Actor(), color(.5f) {
        preDraw = std::bind(&ColoredActor::ColorUpdate, this);
    }

    void ColoredActor::ColorUpdate() {
        glUniform4f(GetShaderProgram()->GetUniformLocationId("ModelColor"),
                    color[0], color[1], color[2], color[3]);
    }

} /* namespace ThreeEngine */