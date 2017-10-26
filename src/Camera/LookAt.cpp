/*
 * File LookAt.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "LookAt.h"

namespace ThreeEngine {

    LookAt::LookAt(Vector eye, Vector center, Vector up) {
        Set(eye, center, up);
    }

    void LookAt::Set(Vector eye, Vector center, Vector up) {
        this->eye = eye;
        this->center = center;
        this->up = up;

        view = center - eye;
        v = view / view.Dist();
        side = v ^up;
        s = side / side.Dist();
        u = s ^v;
        Matrix::Set(
                s.X, s.Y, s.Z, -(s | eye),
                u.X, u.Y, u.Z, -(u | eye),
                -v.X, -v.Y, -v.Z, v | eye,
                0, 0, 0, 1
        );
    }

} /* namespace Divisaction */