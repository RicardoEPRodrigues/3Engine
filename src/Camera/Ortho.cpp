/*
 * File Ortho.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Ortho.h"

namespace ThreeEngine {

    Ortho::Ortho(number left, number right, number bottom, number top, number near, number far) {
        Set(
                2.0f / (right - left), 0, 0, (left + right) / (left - right),
                0, 2.0f / (top - bottom), 0, (bottom + top) / (bottom - top),
                0, 0, 2.0f / (near - far), (near + far) / (near - far),
                0, 0, 0, 1
        );
    }

} /* namespace Divisaction */