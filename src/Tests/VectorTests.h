//
// Created by ricardo on 10/8/17.
//

#ifndef THREEENGINE_VECTORTESTS_H
#define THREEENGINE_VECTORTESTS_H

#include "../Math/Vector.h"
#include "catch.hpp"

SCENARIO("vectors arithmetic testing", "[vector]") {

    GIVEN( "Vector One (1,1,1)" ) {

        ThreeEngine::Vector vector = ThreeEngine::Vector::OneVector;

        REQUIRE((vector.X == 1 && vector.Z == 1 && vector.Z == 1));
        REQUIRE(vector.DistSquared() == 3);
        REQUIRE(vector.Dist() == sqrtf(3));

        WHEN("arithmetic functions: vector +-*/ number") {
            ThreeEngine::Vector v2(2);

            THEN("the vector should behave like") {

                CHECK((vector + 1.0f) == v2);
                CHECK((vector - 1.0f) == ThreeEngine::Vector::ZeroVector);
                CHECK((vector * 2.0f) == v2);
                CHECK((vector / 2.0f) == ThreeEngine::Vector(.5f));
            }
        }
    }
//    SECTION("reserving smaller does not change size or capacity") {
//        v.reserve(0);
//
//        REQUIRE(v.size() == 5);
//        REQUIRE(v.capacity() >= 5);
//    }
}

#endif //THREEENGINE_VECTORTESTS_H
