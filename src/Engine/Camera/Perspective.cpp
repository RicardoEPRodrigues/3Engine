/*
 * File Perspective.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Perspective.h"

namespace ThreeEngine {

    Perspective::Perspective(number FOVy, number aspect, number zNear, number zFar) {
        angle = Maths::ToRadians(FOVy / 2.0f);
        d = 1.0f / tanf(angle);
        Set(
                d / aspect, 0, 0, 0,
                0, d, 0, 0,
                0, 0, (zNear + zFar) / (zNear - zFar), (2 * zFar * zNear) / (zNear - zFar),
                0, 0, -1.0f, 0
        );
    }

} /* namespace Divisaction */