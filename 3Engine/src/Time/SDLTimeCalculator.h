/*
 * File SDLTimeCalculator.h in project 3EngineGlobal
 * 
 * Copyright (C) Ricardo Rodrigues 2018 - All Rights Reserved
 */
#ifndef INC_3ENGINEGLOBAL_SDLTIMECALCULATOR_H
#define INC_3ENGINEGLOBAL_SDLTIMECALCULATOR_H

#include "Time.h"

namespace ThreeEngine {

    class SDLTimeCalculator : public TimeCalculator {
        private:
            milliseconds _startTime;

            milliseconds nowTime;

            milliseconds deltaTime;
        public:
            SDLTimeCalculator();

            ~SDLTimeCalculator() override;

            void update() override;

            milliseconds startTime() override;

            milliseconds now() override;

            milliseconds delta() override;
    };

} /* namespace 3EngineGlobal */

#endif //INC_3ENGINEGLOBAL_SDLTIMECALCULATOR_H
