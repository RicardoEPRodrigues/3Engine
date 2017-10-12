/*
 * File Matrix2.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Matrix2.h"

using namespace std;

namespace ThreeEngine {

    Matrix2::Matrix2() : TMatrix() {}

    Matrix2::Matrix2(TMatrix<2, 2> m) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                M[i][j] = m.M[i][j];
            }
        }
    }

    Matrix2::Matrix2(number in0, number in1,
                     number in2, number in3) {

        M[0][0] = in0;
        M[0][1] = in1;
        M[1][0] = in2;
        M[1][1] = in3;
    }

    Matrix2 Matrix2::ScaleMatrix(const number& inX, const number& inY) {
        return {inX, 0,
                0, inY};
    }

    Matrix2 Matrix2::ScaleMatrixInverted(const number& inX, const number& inY) {
        return {1.0f / inX, 0,
                0, 1.0f / inY};
    }

    Matrix2 Matrix2::RotationMatrix(const number& angle) {
        return Matrix2(cos(angle), sin(angle),
                       -sin(angle), cos(angle));
    }

    Matrix2 Matrix2::RotationMatrixInverted(const number& angle) {
        return Matrix2(cos(angle), -sin(angle),
                       sin(angle), cos(angle));
    }

    Vector2 Matrix2::operator*(const Vector2& v) {
        Vector2 vector;
        for (int i = 0; i < 2; ++i) {
            vector.X += M[0][i] * v[i];
            vector.Y += M[1][i] * v[i];
        }
        return vector;
    }

    Vector2 operator*(const Vector2& v, const Matrix2& m) {
        Vector2 vector;
        for (int i = 0; i < 2; ++i) {
            vector.X += m.M[i][0] * v[i];
            vector.Y += m.M[i][1] * v[i];
        }
        return vector;
    }

    float Matrix2::Determinant() const {
        return (M[0][0] * M[1][1]) - (M[0][1] * M[1][0]);
    }

    Matrix2 Matrix2::Inverse() const {
        Matrix2 inverse = {
                M[1][1], -M[0][1],
                -M[1][0], M[0][0]
        };
        return {(1.0f / Determinant()) * inverse};
    }

} /* namespace Divisaction */