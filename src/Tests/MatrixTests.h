//
// Created by ricardo on 10/9/17.
//

#ifndef THREEENGINE_MATRIXTESTS_H
#define THREEENGINE_MATRIXTESTS_H

#include "../Math/Matrix.h"
#include "../Math/TMatrix.h"

SCENARIO("matrix arithmetic testing", "[matrix]") {

    // TODO Test constructors

    GIVEN("Template Matrix with different sizes") {

        WHEN("using Unary arithmetic functions") {
            TMatrix<3, 2> m = TMatrix<3, 2>(1);
            CHECK((-m) == TMatrix<3, 2>(-1));
        }

        WHEN("using binaries arithmetic functions") {
            TMatrix<3, 2> m = TMatrix<3, 2>(1);
            CHECK((++m) == TMatrix<3, 2>(2));
            CHECK((--m) == TMatrix<3, 2>(1));
        }

        WHEN("using arithmetic functions on numbers") {
            TMatrix<3, 2> m = TMatrix<3, 2>(1);

            THEN("vector +-*/ number") {

                CHECK((m + 1.0f) == TMatrix<3, 2>(2));
                CHECK((m - 1.0f) == TMatrix<3, 2>(0));
                CHECK((m * 2.0f) == TMatrix<3, 2>(2));
                CHECK((m / 2.0f) == TMatrix<3, 2>(.5f));
            }

            THEN("number +-*/ vector") {
                CHECK((1.0f + m) == TMatrix<3, 2>(2));
                CHECK((1.0f - m) == TMatrix<3, 2>(0));
                CHECK((2.0f * m) == TMatrix<3, 2>(2));
                CHECK((2.0f / m) == TMatrix<3, 2>(2));
            }

            THEN("vector =+-*/ number") {
                CHECK((m += 1.0f) == TMatrix<3, 2>(2));
                CHECK((m -= 1.0f) == TMatrix<3, 2>(1));
                CHECK((m *= 2.0f) == TMatrix<3, 2>(2));
                CHECK((m /= 2.0f) == TMatrix<3, 2>(1));
            }
        }

        WHEN("using arithmetic functions on other vectors") {
            TMatrix<3, 2> m = TMatrix<3, 2>(1);
            TMatrix<3, 2> m2 = TMatrix<3, 2>(2);

            THEN("vector +- vector") {
                CHECK((m + m2) == TMatrix<3, 2>(3));
                CHECK((m - m2) == -m);
            }

            THEN("vector =+- vector") {
                CHECK((m += m2) == TMatrix<3, 2>(3));
                CHECK((m -= m2) == TMatrix<3, 2>(1));
            }

            THEN("vector * vector") {

                const number m1a[] = {
                        1, 3,
                        5, 2,
                        0, 4
                };
                TMatrix<3, 2> m1 = TMatrix<3, 2>(m1a);

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
                TMatrix<3, 4> m3 = TMatrix<3, 4>(m3a);

                CHECK((m1 * M2) == m3);
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
                CHECK((m - 1.0f) == Matrix(0));
                CHECK((m * 2.0f) == Matrix(2));
                CHECK((m / 2.0f) == Matrix(.5f));
            }

            THEN("number +-*/ vector") {
                CHECK((1.0f + m) == Matrix(2));
                CHECK((1.0f - m) == Matrix(0));
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
    }
}

#endif //THREEENGINE_MATRIXTESTS_H