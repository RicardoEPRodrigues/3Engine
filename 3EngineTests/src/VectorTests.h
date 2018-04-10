//
// Created by ricardo on 10/8/17.
//

#ifndef THREEENGINE_VECTORTESTS_H
#define THREEENGINE_VECTORTESTS_H

#include "../../3Engine/src/Math/Vector.h"
#include "../../3Engine/src/Math/Vector2.h"
#include "../../3Engine/src/Math/Vector4.h"
#include "catch.hpp"

SCENARIO("vectors arithmetic testing", "[vector]") {

    // TODO Test constructors

    GIVEN("Vector 2D One (1,1)") {

        ThreeEngine::Vector2 v1 = ThreeEngine::Vector2::OneVector;

        REQUIRE((v1.X == 1 && v1.Y == 1));
        REQUIRE(v1.DistSquared() == 2);
        REQUIRE(v1.Dist() == sqrtf(2));

        ThreeEngine::Vector2 v2(2);

        WHEN("using Unary arithmetic functions") {
            CHECK((-v1) == ThreeEngine::Vector2(-1, -1));
        }

        WHEN("using binaries arithmetic functions") {
            CHECK((++v1) == v2);
            CHECK((--v1) == ThreeEngine::Vector2::OneVector);
        }

        WHEN("using arithmetic functions on numbers") {

            THEN("vector +-*/ number") {

                CHECK((v1 + 1.0f) == v2);
                CHECK((v1 - 1.0f) == ThreeEngine::Vector2::ZeroVector);
                CHECK((v1 * 2.0f) == v2);
                CHECK((v1 / 2.0f) == ThreeEngine::Vector2(.5f));
            }

            THEN("number +-*/ vector") {

                CHECK((1.0f + v1) == v2);
                CHECK((1.0f - v1) == ThreeEngine::Vector2::ZeroVector);
                CHECK((2.0f * v1) == v2);
                CHECK((2.0f / v1) == v2);
            }

            THEN("vector =+-*/ number") {
                CHECK((v1 += 1.0f) == v2);
                CHECK((v1 -= 1.0f) == ThreeEngine::Vector2::OneVector);
                CHECK((v1 *= 2.0f) == v2);
                CHECK((v1 /= 2.0f) == ThreeEngine::Vector2::OneVector);
            }
        }

        WHEN("using arithmetic functions on other vectors") {

            THEN("vector +-*/ vector") {
                CHECK((v1 + v2) == ThreeEngine::Vector2(3));
                CHECK((v1 - v2) == -v1);
                CHECK((v1 * v2) == v2);
                CHECK((v1 / v2) == ThreeEngine::Vector2(.5f));
                CHECK((v1 | v2) == 4.0f);
            }

            THEN("vector =+-*/ vector") {
                CHECK((v1 += v2) == ThreeEngine::Vector2(3));
                CHECK((v1 -= v2) == ThreeEngine::Vector2::OneVector);
                CHECK((v1 *= v2) == v2);
                CHECK((v1 /= v2) == ThreeEngine::Vector2::OneVector);
            }
        }

        WHEN("normalizing and testing") {
            Vector2 vector = Vector2(2, 4);
            CHECK(vector.Normalize());
            CHECK(vector.IsNormalized());
            vector = Vector2::ZeroVector;
            CHECK(!vector.Normalize());
            CHECK(!vector.IsNormalized());
        }
    }

    GIVEN("Vector One (1,1,1)") {

        ThreeEngine::Vector v1 = ThreeEngine::Vector::OneVector;

        REQUIRE((v1.X == 1 && v1.Y == 1 && v1.Z == 1));
        REQUIRE(v1.DistSquared() == 3);
        REQUIRE(v1.Dist() == sqrtf(3));

        ThreeEngine::Vector v2(2);

        WHEN("using Unary arithmetic functions") {
            CHECK((-v1) == ThreeEngine::Vector(-1, -1, -1));
        }

        WHEN("using binaries arithmetic functions") {
            CHECK((++v1) == v2);
            CHECK((--v1) == ThreeEngine::Vector::OneVector);
        }

        WHEN("using arithmetic functions on numbers") {

            THEN("vector +-*/ number") {

                CHECK((v1 + 1.0f) == v2);
                CHECK((v1 - 1.0f) == ThreeEngine::Vector::ZeroVector);
                CHECK((v1 * 2.0f) == v2);
                CHECK((v1 / 2.0f) == ThreeEngine::Vector(.5f));
            }

            THEN("number +-*/ vector") {

                CHECK((1.0f + v1) == v2);
                CHECK((1.0f - v1) == ThreeEngine::Vector::ZeroVector);
                CHECK((2.0f * v1) == v2);
                CHECK((2.0f / v1) == v2);
            }

            THEN("vector =+-*/ number") {
                CHECK((v1 += 1.0f) == v2);
                CHECK((v1 -= 1.0f) == ThreeEngine::Vector::OneVector);
                CHECK((v1 *= 2.0f) == v2);
                CHECK((v1 /= 2.0f) == ThreeEngine::Vector::OneVector);
            }
        }

        WHEN("using arithmetic functions on other vectors") {

            THEN("vector +-*/ vector") {
                CHECK((v1 + v2) == ThreeEngine::Vector(3));
                CHECK((v1 - v2) == -v1);
                CHECK((v1 * v2) == v2);
                CHECK((v1 / v2) == ThreeEngine::Vector(.5f));
                CHECK((v1 | v2) == 6.0f);
                CHECK((ThreeEngine::Vector::ForwardVector ^ ThreeEngine::Vector::LeftVector) ==
                      ThreeEngine::Vector::UpVector);
            }

            THEN("vector =+-*/ vector") {
                CHECK((v1 += v2) == ThreeEngine::Vector(3));
                CHECK((v1 -= v2) == ThreeEngine::Vector::OneVector);
                CHECK((v1 *= v2) == v2);
                CHECK((v1 /= v2) == ThreeEngine::Vector::OneVector);
            }
        }

        WHEN("normalizing and testing") {
            Vector vector = Vector(2, 4, 2);
            CHECK(vector.Normalize());
            CHECK(vector.IsNormalized());
            vector = Vector::ZeroVector;
            CHECK(!vector.Normalize());
            CHECK(!vector.IsNormalized());
        }
    }

    GIVEN("Vector with random numbers") {
        srand(static_cast <unsigned> (time(0)));

        WHEN("using triple product") {
            THEN("Vector component values = 1") {
                ThreeEngine::number max = 1;
                for (int w = 0; w < 10; w++) {
                    ThreeEngine::Vector i = ThreeEngine::Vector::GetRandom(max);
                    ThreeEngine::Vector j = ThreeEngine::Vector::GetRandom(max);
                    ThreeEngine::Vector k = ThreeEngine::Vector::GetRandom(max);
                    ThreeEngine::Vector rightSide = i ^(j ^ k);
                    ThreeEngine::Vector leftSide = (j * (i | k)) - (k * (i | j));
                    CHECK(rightSide == leftSide);
                }
            }
            THEN("Vector component values = 1000") {
                ThreeEngine::number max = 1000;
                for (int w = 0; w < 10; w++) {
                    ThreeEngine::Vector i = ThreeEngine::Vector::GetRandom(max);
                    ThreeEngine::Vector j = ThreeEngine::Vector::GetRandom(max);
                    ThreeEngine::Vector k = ThreeEngine::Vector::GetRandom(max);
                    ThreeEngine::Vector rightSide = i ^(j ^ k);
                    ThreeEngine::Vector leftSide = (j * (i | k)) - (k * (i | j));
                    CHECK(rightSide == leftSide);
                }
            }
        }
    }

    GIVEN("Vector4 One (1,1,1,1)") {

        ThreeEngine::Vector4 v1 = ThreeEngine::Vector4::OneVector;

        REQUIRE((v1.X == 1 && v1.Y == 1 && v1.Z == 1));
        REQUIRE(v1.DistSquared3() == 3);
        REQUIRE(v1.Dist3() == sqrtf(3));
        REQUIRE(v1.DistSquared() == 4);
        REQUIRE(v1.Dist() == sqrtf(4));

        ThreeEngine::Vector4 v2(2);

        WHEN("using Unary arithmetic functions") {
            CHECK((-v1) == ThreeEngine::Vector4(-1, -1, -1, -1));
        }

        WHEN("using binaries arithmetic functions") {
            CHECK((++v1) == v2);
            CHECK((--v1) == ThreeEngine::Vector4::OneVector);
        }

        WHEN("using arithmetic functions on numbers") {

            THEN("vector +-*/ number") {

                CHECK((v1 + 1.0f) == v2);
                CHECK((v1 - 1.0f) == ThreeEngine::Vector4::ZeroVector);
                CHECK((v1 * 2.0f) == v2);
                CHECK((v1 / 2.0f) == ThreeEngine::Vector4(.5f));
            }

            THEN("number +-*/ vector") {

                CHECK((1.0f + v1) == v2);
                CHECK((1.0f - v1) == ThreeEngine::Vector4::ZeroVector);
                CHECK((2.0f * v1) == v2);
                CHECK((2.0f / v1) == v2);
            }

            THEN("vector =+-*/ number") {
                CHECK((v1 += 1.0f) == v2);
                CHECK((v1 -= 1.0f) == ThreeEngine::Vector4::OneVector);
                CHECK((v1 *= 2.0f) == v2);
                CHECK((v1 /= 2.0f) == ThreeEngine::Vector4::OneVector);
            }
        }

        WHEN("using arithmetic functions on other vectors") {

            THEN("vector +-*/ vector") {
                CHECK((v1 + v2) == ThreeEngine::Vector4(3));
                CHECK((v1 - v2) == -v1);
                CHECK((v1 * v2) == v2);
                CHECK((v1 / v2) == ThreeEngine::Vector4(.5f));
                CHECK((v1 | v2) == 8.0f);
                CHECK((ThreeEngine::Vector4::DotProduct3(v1, v2)) == 6.0f);
                CHECK((ThreeEngine::Vector::ForwardVector ^ ThreeEngine::Vector::LeftVector) ==
                      ThreeEngine::Vector::UpVector);
            }

            THEN("vector =+-*/ vector") {
                CHECK((v1 += v2) == ThreeEngine::Vector4(3));
                CHECK((v1 -= v2) == ThreeEngine::Vector4::OneVector);
                CHECK((v1 *= v2) == v2);
                CHECK((v1 /= v2) == ThreeEngine::Vector4::OneVector);
            }
        }

        WHEN("normalizing and testing") {
            Vector4 vector = Vector4(2, 4, 2);
            CHECK(vector.Normalize());
            CHECK(vector.IsNormalized());
            vector = Vector4::ZeroVector;
            CHECK(!vector.Normalize());
            CHECK(!vector.IsNormalized());
        }
    }
}

#endif //THREEENGINE_VECTORTESTS_H
