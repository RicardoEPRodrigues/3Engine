/*
 * File Matrix3.h in project ThreeEngine
 *
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MATRIX3_H
#define THREEENGINE_MATRIX3_H

#include "TMatrix.h"
#include "Vector.h"
#include "Matrix2.h"

namespace ThreeEngine {

    struct Matrix3 : public TMatrix<3, 3> {

        Matrix3();

        Matrix3(const TMatrix<3, 3>& m);

        Matrix3(const struct Matrix& m);

        Matrix3(const struct Matrix2& m);

        Matrix3(number in0, number in1, number in2,
                number in3, number in4, number in5,
                number in6, number in7, number in8);

        static Matrix3 DualMatrix(const Vector& v);

        static Matrix3 ScaleMatrix(const number& inX, const number& inY, const number& inZ);

        static Matrix3 ScaleMatrixInverted(const number& inX, const number& inY, const number& inZ);

        static Matrix3 RotationMatrix(Maths::Axis axis, const number& angle);

        static Matrix3 RotationMatrix(const Vector& vector, const number& angle);

        /**
         * Results in the multiplication of this matrix with a Vector.
         * @param v
         * @return multiplication vector
         */
        Vector operator*(const Vector& v);

        /**
         * Results in the multiplication of a vector with this matrix.
         * @param v
         * @return multiplication vector
         */
        friend Vector operator*(const Vector& v, const Matrix3& m);

        explicit operator Matrix2() const {
            Matrix2 m;
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                    m.M[i][j] = M[i][j];
                }
            }
            return m;
        }

        float Determinant() const;

        Matrix3 Inverse() const;

        Matrix3 Minors() const;

        Matrix3 Cofactor() const;

        Matrix3 Adjugate() const;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_MATRIX3_H
