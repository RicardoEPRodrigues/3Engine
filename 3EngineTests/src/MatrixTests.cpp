//
// Created by ricardo on 10/9/17.
//

#ifndef THREEENGINE_MATRIXTESTS_H
#define THREEENGINE_MATRIXTESTS_H

#include "tests.h"

#include "../../3Engine/src/Math/Matrix.h"
#include "../../3Engine/src/Math/TMatrix.h"
#include "../../3Engine/src/Math/Matrix3.h"
#include "../../3Engine/src/Math/Matrix2.h"

using namespace ThreeEngine;

SCENARIO("matrix arithmetic testing", "[matrix]") {

    // TODO Test constructors

    GIVEN("Template Matrix with different sizes") {
        TMatrix<3, 2> m0 = TMatrix<3, 2>(0);
        TMatrix<3, 2> m1 = TMatrix<3, 2>(1);
        TMatrix<3, 2> mm1 = TMatrix<3, 2>(-1);
        TMatrix<3, 2> m2 = TMatrix<3, 2>(2);
        TMatrix<3, 2> m3 = TMatrix<3, 2>(3);
        TMatrix<3, 2> m5 = TMatrix<3, 2>(0.5f);

        WHEN("using Unary arithmetic functions") {
            TMatrix<3, 2> m = m1;
            CHECK((-m) == mm1);
        }

        WHEN("using binaries arithmetic functions") {
            TMatrix<3, 2> m = m1;
            CHECK((++m) == m2);
            CHECK((--m) == m1);
        }

        WHEN("using arithmetic functions on numbers") {
            TMatrix<3, 2> m = m1;

            THEN("vector +-*/ number") {

                CHECK((m + 1.0f) == m2);
                CHECK((m - 1.0f) == m0);
                CHECK((m * 2.0f) == m2);
                CHECK((m / 2.0f) == m5);
            }

            THEN("number +-*/ vector") {
                CHECK((1.0f + m) == m2);
                CHECK((1.0f - m) == m0);
                CHECK((2.0f * m) == m2);
                CHECK((2.0f / m) == m2);
            }

            THEN("vector =+-*/ number") {
                CHECK((m += 1.0f) == m2);
                CHECK((m -= 1.0f) == m1);
                CHECK((m *= 2.0f) == m2);
                CHECK((m /= 2.0f) == m1);
            }
        }

        WHEN("using arithmetic functions on other vectors") {
            TMatrix<3, 2> m = m1;

            THEN("vector +- vector") {
                CHECK((m + m2) == m3);
                CHECK((m - m2) == -m);
            }

            THEN("vector =+- vector") {
                CHECK((m += m2) == m3);
                CHECK((m -= m2) == m1);
            }

            THEN("vector * vector") {

                const number m1a[] = {
                        1, 3,
                        5, 2,
                        0, 4
                };
                TMatrix<3, 2> M1 = TMatrix<3, 2>(m1a);

                const number m2a[] = {
                        3, 6, 9, 4,
                        2, 7, 8, 3
                };
                TMatrix<2, 4> M2 = TMatrix<2, 4>(m2a);

                const number m3a[] = {
                        9, 27, 33, 13,
                        19, 44, 61, 26,
                        8, 28, 32, 12
                };
                TMatrix<3, 4> M3 = TMatrix<3, 4>(m3a);

                CHECK((M1 * M2) == M3);
            }
        }

        WHEN("applying transformations") {
            THEN("Transposing") {
                const number ma[] = {
                        1, 3,
                        5, 2,
                        0, 4
                };
                TMatrix<3, 2> m = TMatrix<3, 2>(ma);

                const number m2a[] = {
                        1, 5, 0,
                        3, 2, 4
                };
                TMatrix<2, 3> m2 = TMatrix<2, 3>(m2a);

                CHECK(m.GetTransposed() == m2);
            }
        }

        WHEN("Matrix 3x3") {
            THEN("multiplication with vector") {
                Matrix3 m31 = Matrix3(0, 0, 0,
                                      0, 1, 0,
                                      0, 1, 0);

                Vector v = Vector::OneVector,
                        vResult1 = Vector(0, 1, 1),
                        vResult2 = Vector(0, 2, 0);

                CHECK((m31 * v) == vResult1);
                CHECK((v * m31) == vResult2);
            }

            THEN("converting to array with column major format") {
                Matrix3 m31 = Matrix3(0, 1, 2,
                                      3, 4, 5,
                                      6, 7, 8);
                number a[9];
                number aResult[9] = {0, 3, 6,
                                     1, 4, 7,
                                     2, 5, 8};

                m31.ToArray(a);
                CHECK(std::equal(std::begin(a), std::end(a), std::begin(aResult)));
            }

            THEN("converting to Matrix 2x2") {
                Matrix3 m31 = Matrix3(1, 2, 2,
                                      0, 1, 5,
                                      6, 7, 8);
                Matrix2 m21 = Matrix2(m31);
                Matrix2 m21Result = Matrix2(1, 2,
                                            0, 1);

                CHECK(m21 == m21Result);
            }

            // TODO Test Inverse and other methods

            THEN("Invert") {
                Matrix3 m31 = Matrix3(1, 2, 3,
                                      0, 1, 4,
                                      5, 6, 0);

                Matrix3 m31Result = Matrix3(-24, 18, 5,
                                            20, -15, -4,
                                            -5, 4, 1);

                CHECK(m31.Inverse() == m31Result);
            }

            THEN("applying rotations") {

                Vector v1 = {1, 0, 0};
                Vector v2 = {0, 2, 0};
                Vector v3 = {0, 0, 3};

                Matrix3 v1Rot = Matrix3::RotationMatrix(v1, 90.0f);
                Matrix3 v2Rot = Matrix3::RotationMatrix(v2, 90.0f);
                Matrix3 v3Rot = Matrix3::RotationMatrix(v3, 90.0f);

                Vector vResult = Vector(1, 0, 0);
                CHECK((v1Rot * v1) == vResult);
                vResult = Vector(0, 0, -1);
                CHECK((v2Rot * v1) == vResult);
                vResult = Vector(0, 1, 0);
                CHECK((v3Rot * v1) == vResult);
                vResult = Vector(0, 0, 2);
                CHECK((v1Rot * v2) == vResult);
                vResult = Vector(0, 2, 0);
                CHECK((v2Rot * v2) == vResult);
                vResult = Vector(-2, 0, 0);
                CHECK((v3Rot * v2) == vResult);
                vResult = Vector(0, -3, 0);
                CHECK((v1Rot * v3) == vResult);
                vResult = Vector(3, 0, 0);
                CHECK((v2Rot * v3) == vResult);
                vResult = Vector(0, 0, 3);
                CHECK((v3Rot * v3) == vResult);
            }
        }

        WHEN("Matrix 2x2") {
            THEN("multiplication with vector") {
                Matrix2 m21 = Matrix2(1, 2,
                                      0, 1);

                Vector2 v = Vector2(5, 6),
                        vResult1 = Vector2(17, 6),
                        vResult2 = Vector2(5, 16);

                CHECK((m21 * v) == vResult1);
                CHECK((v * m21) == vResult2);
            }

            THEN("converting to array with column major format") {
                Matrix2 m21 = Matrix2(0, 1,
                                      2, 3);
                number a[4];
                number aResult[4] = {0, 2,
                                     1, 3};

                m21.ToArray(a);
                CHECK(std::equal(std::begin(a), std::end(a), std::begin(aResult)));
            }
        }
    }

    GIVEN("Matrix 4x4") {

        WHEN("using Unary arithmetic functions") {
            Matrix m = Matrix(1);
            CHECK((-m) == Matrix(-1));
        }

        WHEN("using binaries arithmetic functions") {
            Matrix m = Matrix(1);
            CHECK((++m) == Matrix(2));
            CHECK((--m) == Matrix(1));
        }

        WHEN("using arithmetic functions on numbers") {
            Matrix m = Matrix(1);

            THEN("vector +-*/ number") {

                CHECK((m + 1.0f) == Matrix(2));
                CHECK((m - 1.0f) == Matrix((number) 0));
                CHECK((m * 2.0f) == Matrix(2));
                CHECK((m / 2.0f) == Matrix(.5f));
            }

            THEN("number +-*/ vector") {
                CHECK((1.0f + m) == Matrix(2));
                CHECK((1.0f - m) == Matrix((number) 0));
                CHECK((2.0f * m) == Matrix(2));
                CHECK((2.0f / m) == Matrix(2));
            }

            THEN("vector =+-*/ number") {
                CHECK((m += 1.0f) == Matrix(2));
                CHECK((m -= 1.0f) == Matrix(1));
                CHECK((m *= 2.0f) == Matrix(2));
                CHECK((m /= 2.0f) == Matrix(1));
            }
        }

        WHEN("using arithmetic functions on other vectors") {
            Matrix m = Matrix(1);
            Matrix m2 = Matrix(2);

            THEN("vector +- vector") {
                CHECK((m + m2) == Matrix(3));
                CHECK((m - m2) == -m);
            }

            THEN("vector =+- vector") {
                CHECK((m += m2) == Matrix(3));
                CHECK((m -= m2) == Matrix(1));
            }

            THEN("vector * vector") {

                m = Matrix(5, 2, 6, 1,
                           0, 6, 2, 0,
                           3, 8, 1, 4,
                           1, 8, 5, 6);

                m2 = Matrix(7, 5, 8, 0,
                            1, 8, 2, 6,
                            9, 4, 3, 8,
                            5, 3, 7, 9);

                Matrix mResult = Matrix(96, 68, 69, 69,
                                        24, 56, 18, 52,
                                        58, 95, 71, 92,
                                        90, 107, 81, 142);

                CHECK((m * m2) == mResult);
            }
        }

        WHEN("converting to OpenGL array") {
            Matrix m = Matrix(5, 2, 6, 1,
                              0, 6, 2, 0,
                              3, 8, 1, 4,
                              1, 8, 5, 6);

            number array[16];
            m.ToArray(array);

            number result[] = {5, 0, 3, 1,
                               2, 6, 8, 8,
                               6, 2, 1, 5,
                               1, 0, 4, 6};

            CHECK(std::equal(std::begin(array), std::end(array), std::begin(result)));
        }

        WHEN("applying transformations") {
            THEN("Transposing") {
                Matrix m = Matrix(5, 2, 6, 1,
                                  0, 6, 2, 0,
                                  3, 8, 1, 4,
                                  1, 8, 5, 6);

                Matrix m2 = Matrix(5, 0, 3, 1,
                                   2, 6, 8, 8,
                                   6, 2, 1, 5,
                                   1, 0, 4, 6);

                CHECK(m.GetTransposed() == m2);
            }
        }


        WHEN("multiplication with vector") {
            Matrix m = Matrix(0, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 0, 0);

            Vector4 v = Vector4::OneVector,
                    vResult1 = Vector4(0, 1, 1, 0),
                    vResult2 = Vector4(0, 2, 0, 0);

            CHECK((m * v) == vResult1);
            CHECK((v * m) == vResult2);

        }


        WHEN("converting to Matrix 3x3") {
            Matrix m = Matrix(5, 2, 6, 1,
                              0, 6, 2, 0,
                              3, 8, 1, 4,
                              1, 8, 5, 6);
            Matrix3 m3 = Matrix3(m);
            Matrix3 m3Result = Matrix3(5, 2, 6,
                                       0, 6, 2,
                                       3, 8, 1);
            CHECK(m3 == m3Result);
        }
    }
}

#endif //THREEENGINE_MATRIXTESTS_H