/*
 * File Time.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TIME_H
#define THREEENGINE_TIME_H

namespace ThreeEngine {

    typedef float milliseconds;

    class TimeCalculator {
        public:
            TimeCalculator() = default;

            virtual ~TimeCalculator() = default;

            virtual void update() = 0;

            virtual milliseconds startTime() = 0;

            virtual milliseconds now() = 0;

            virtual milliseconds delta() = 0;
    };

    class Time {
        public:
            Time();

            virtual ~Time();

            static TimeCalculator* _timeCalculator;
        public:

            static void SetTimeCalculator(TimeCalculator* timeCalculator);

            static void Update();

            static milliseconds StartTime();

            static milliseconds Now();

            static milliseconds Delta();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TIME_H
