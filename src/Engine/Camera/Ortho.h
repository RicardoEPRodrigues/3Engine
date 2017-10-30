/*
 * File Ortho.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_ORTHO_H
#define THREEENGINE_ORTHO_H

#include "../Math/Matrix.h"

namespace ThreeEngine {

    class Ortho : public Matrix {
        public:
            Ortho(number left, number right,  number bottom, number top, number near, number far);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_ORTHO_H
