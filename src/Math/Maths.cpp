#include "Maths.h"

namespace ThreeEngine {
    number Maths::GetRandom(const number& lowLimit, const number& HighLimit) {
        return (static_cast <number> (rand()) / (static_cast <number> (RAND_MAX / HighLimit))) + lowLimit;
    }
}