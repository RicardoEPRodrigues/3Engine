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
        number angleInRadian = angle * Maths::PI / 180.0f;
        switch (axis) {
            case Maths::Axis::X:
                return {1, 0, 0,
                        0, cos(angleInRadian), -sin(angleInRadian),
                        0, sin(angleInRadian), cos(angleInRadian)};
            case Maths::Axis::Y:
                return {cos(angleInRadian), 0, -sin(angleInRadian),
                        0, 1, 0,
                        sin(angleInRadian), 0, cos(angleInRadian)};
            case Maths::Axis::Z:
            default:
                return {cos(angleInRadian), -sin(angleInRadian), 0,
                        sin(angleInRadian), cos(angleInRadian), 0,
                        0, 0, 1};
        }
    }

    Matrix3 Matrix3::RotationMatrix(const Vector& vector, const number& angle) {
        number angleInRadian = Maths::ToRadians(angle);

        // Rodrigues Formula
        Vector vNorm = vector;
        vNorm.Normalize();
        Matrix3 dualM = DualMatrix(vNorm);
        Matrix3 dualMSqr = (TMatrix) dualM * dualM;
        return Identity() + (TMatrix) dualM * sin(angleInRadian) +
               (1.0f - cos(angleInRadian)) * dualMSqr;
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
        return (1 / Determinant()) * Adjugate();
    }

    Matrix3 Matrix3::Minors() const {
        static const Matrix2 m00 = {M[1][1], M[1][2],
                                    M[2][1], M[2][2]};
        static const Matrix2 m01 = {M[1][0], M[1][2],
                                    M[2][0], M[2][2]};
        static const Matrix2 m02 = {M[1][0], M[1][1],
                                    M[2][0], M[2][1]};

        static const Matrix2 m10 = {M[0][1], M[0][2],
                                    M[2][1], M[2][2]};
        static const Matrix2 m11 = {M[0][0], M[0][2],
                                    M[2][0], M[2][2]};
        static const Matrix2 m12 = {M[0][0], M[0][1],
                                    M[2][0], M[2][1]};

        static const Matrix2 m20 = {M[0][1], M[0][2],
                                    M[1][1], M[1][2]};
        static const Matrix2 m21 = {M[0][0], M[0][2],
                                    M[1][0], M[1][2]};
        static const Matrix2 m22 = {M[0][0], M[0][1],
                                    M[1][0], M[1][1]};

        return {
                m00.Determinant(), m01.Determinant(), m02.Determinant(),
                m10.Determinant(), m11.Determinant(), m12.Determinant(),
                m20.Determinant(), m21.Determinant(), m22.Determinant()
        };
    }

    Matrix3 Matrix3::Cofactor() const {
        Matrix3 m = Minors();
        m.M[0][1] *= (-1);
        m.M[1][0] *= (-1);
        m.M[1][2] *= (-1);
        m.M[2][1] *= (-1);
        return m;
    }

    Matrix3 Matrix3::Adjugate() const {
        return Cofactor().GetTransposed();
    }

} /* namespace Divisaction */