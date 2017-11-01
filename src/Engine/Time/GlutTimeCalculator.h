/*
 * File GlutTimeCalculator.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_GLUTTIMECALCULATOR_H
#define THREEENGINE_GLUTTIMECALCULATOR_H

#include "Time.h"

namespace ThreeEngine {

    class GlutTimeCalculator : public TimeCalculator {
        private:
            milliseconds _startTime;

            milliseconds nowTime;

            milliseconds deltaTime;
        public:
            GlutTimeCalculator();

            ~GlutTimeCalculator() override;

            void update() override;

            milliseconds startTime() override;

            milliseconds now() override;

            milliseconds delta() override;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_GLUTTIMECALCULATOR_H
