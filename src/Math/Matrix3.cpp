/*
 * File Matrix3.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include "Matrix3.h"

using namespace std;

namespace ThreeEngine {
    Matrix3::Matrix3() : TMatrix() {}

    Matrix3::Matrix3(TMatrix<3, 3> m) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                M[i][j] = m.M[i][j];
            }
        }
    }

    Matrix3::Matrix3(Matrix2 m) : Matrix3(m.M[0][0], m.M[0][1], 0,
                                          m.M[1][0], m.M[1][1], 0,
                                          0, 0, 1) {}

    Matrix3::Matrix3(number in0, number in1, number in2, number in3, number in4, number in5,
                     number in6, number in7, number in8) {
        M[0][0] = in0;
        M[0][1] = in1;
        M[0][2] = in2;
        M[1][0] = in3;
        M[1][1] = in4;
        M[1][2] = in5;
        M[2][0] = in6;
        M[2][1] = in7;
        M[2][2] = in8;
    }

    Matrix3 Matrix3::DualMatrix(const Vector& v) {
        return {0, -v.Z, v.Y,
                v.Z, 0, -v.X,
                -v.Y, v.X, 0};
    }

    Matrix3 Matrix3::ScaleMatrix(const number& inX, const number& inY, const number& inZ) {
        return {inX, 0, 0,
                0, inY, 0,
                0, 0, inZ};
    }

    Matrix3
    Matrix3::ScaleMatrixInverted(const number& inX, const number& inY, const number& inZ) {
        return {1.0f / inX, 0, 0,
                0, 1.0f / inY, 0,
                0, 0, 1.0f / inZ};
    }

    Matrix3 Matrix3::RotationMatrix(Maths::Axis axis, const number& angle) {
        switch (axis) {
            case Maths::Axis::X:
                return {1, 0, 0,
                        0, cos(angle), -sin(angle),
                        0, -sin(angle), cos(angle)};
            case Maths::Axis::Y:
                return {cos(angle), 0, -sin(angle),
                        0, 1, 0,
                        -sin(angle), 0, cos(angle)};
            case Maths::Axis::Z:
            default:
                return {cos(angle), -sin(angle), 0,
                        -sin(angle), cos(angle), 0,
                        0, 0, 1};
        }
    }

    Vector Matrix3::operator*(const Vector& v) {
        Vector vector;
        for (int i = 0; i < 3; ++i) {
            vector.X += M[0][i] * v[i];
            vector.Y += M[1][i] * v[i];
            vector.Z += M[2][i] * v[i];
        }
        return vector;
    }

    Vector operator*(const Vector& v, const Matrix3& m) {
        Vector vector;
        for (int i = 0; i < 3; ++i) {
            vector.X += m.M[i][0] * v[i];
            vector.Y += m.M[i][1] * v[i];
            vector.Z += m.M[i][2] * v[i];
        }
        return vector;
    }

    float Matrix3::Determinant() const {
        return M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
               - M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0])
               + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
    }

    Matrix3 Matrix3::Inverse() const {
        return Matrix3();
    }

} /* namespace Divisaction */