/*
* File Math.h in project ThreeEngine
*
* Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
*/
#ifndef THREEENGINE_MATHS_H
#define THREEENGINE_MATHS_H

#include <cmath>

// Only needed for the std::numeric_limits
//#include <limits>

namespace ThreeEngine {


    typedef float number;

    /// Epsilon is the difference between 1.0 and the next value representable by the floating-point.
    const float Epsilon = static_cast<number>(1.0e-5);
    //const float Epsilon = std::numeric_limits<number>::epsilon();

    /// Units in the Last Place to take into account in a floating-point type.
    const float ULP = 3.0f;

    struct Maths {
            enum Axis { X, Y, Z, W };

            static number GetRandom(const number& lowLimit, const number& HighLimit);

        private:
            Maths() = default;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_MATHS_H