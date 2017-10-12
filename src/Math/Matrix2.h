/*
 * File Matrix2.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MATRIX2_H
#define THREEENGINE_MATRIX2_H

#include "TMatrix.h"
#include "Vector2.h"

namespace ThreeEngine {

    struct Matrix2 : public TMatrix<2, 2> {

        Matrix2();

        Matrix2(TMatrix<2, 2>);

        Matrix2(number in0, number in1,
                number in2, number in3);

        static Matrix2 ScaleMatrix(const number& inX, const number& inY);

        static Matrix2 ScaleMatrixInverted(const number& inX, const number& inY);

        static Matrix2 RotationMatrix(const number& angle);

        static Matrix2 RotationMatrixInverted(const number& angle);

        /**
         * Results in the multiplication of this matrix with a Vector.
         * @param v
         * @return multiplication vector
         */
        Vector2 operator*(const Vector2& v);

        /**
         * Results in the multiplication of a vector with this matrix.
         * @param v
         * @return multiplication vector
         */
        friend Vector2 operator*(const Vector2& v, const Matrix2& m);

        float Determinant() const;
        Matrix2 Inverse() const;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_MATRIX2_H
