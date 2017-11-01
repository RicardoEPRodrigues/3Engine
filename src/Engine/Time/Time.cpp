/*
 * File Time.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Time.h"

namespace ThreeEngine {

    TimeCalculator* Time::_timeCalculator = nullptr;

    Time::Time() = default;

    Time::~Time() {
        delete _timeCalculator;
    }

    void Time::Update() {
        if (_timeCalculator) {
            _timeCalculator->update();
        }
    }

    milliseconds Time::StartTime() {
        return _timeCalculator ? _timeCalculator->startTime() : -1;
    }

    milliseconds Time::Now() {
        return _timeCalculator ? _timeCalculator->now() : -1;
    }

    milliseconds Time::Delta() {
        return _timeCalculator ? _timeCalculator->delta() : -1;
    }

    void Time::SetTimeCalculator(TimeCalculator* timeCalculator) {
        _timeCalculator = timeCalculator;
    }

} /* namespace Divisaction */