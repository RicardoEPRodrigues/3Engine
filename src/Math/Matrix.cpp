/*
 * File Matrix.cpp in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#include <algorithm>
#include "Matrix.h"
#include "../Debug.h"

namespace ThreeEngine {
    Matrix::Matrix() {
        Reset(0.0f);
    }

    Matrix::Matrix(number in) {
        Reset(in);
    }

    Matrix::Matrix(number in0, number in1, number in2, number in3,
                   number in4, number in5, number in6, number in7,
                   number in8, number in9, number in10, number in11,
                   number in12, number in13, number in14, number in15) {
        Set(in0, in1, in2, in3,
            in4, in5, in6, in7,
            in8, in9, in10, in11,
            in12, in13, in14, in15);
    }

    Matrix::Matrix(const Matrix& other) {
        operator=(other);
    }

    Matrix& Matrix::operator=(const Matrix& other) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] = other.M[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::GetRandom(const number& max) {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = Maths::GetRandom(-max, 2 * max);
            }
        }
        return m;
    }

    void Matrix::Set(number in0, number in1, number in2, number in3,
                     number in4, number in5, number in6, number in7,
                     number in8, number in9, number in10, number in11,
                     number in12, number in13, number in14, number in15) {

        M[0][0] = in0;
        M[0][1] = in1;
        M[0][2] = in2;
        M[0][3] = in3;
        M[1][0] = in4;
        M[1][1] = in5;
        M[1][2] = in6;
        M[1][3] = in7;
        M[2][0] = in8;
        M[2][1] = in9;
        M[2][2] = in10;
        M[2][3] = in11;
        M[3][0] = in12;
        M[3][1] = in13;
        M[3][2] = in14;
        M[3][3] = in15;
    }

    void Matrix::SetIdentity() {
        Set(1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    void Matrix::Reset(const float& value) {
        for (int i = 0; i < 4; ++i) {
            std::fill(std::begin(M[i]), std::end(M[i]), value);
        }
    }

    void Matrix::ToArray(number (& array)[16]) {
        for (int i = 0; i < 16; ++i) {
            // (i / 4) returns the line from 0 to 3
            // (i % 4) returns the column from 0 to 3
            array[i] = M[i % 4][i / 4];
        }
    }

    Matrix Matrix::operator+(const Matrix& V) const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = M[i][j] + V.M[i][j];
            }
        }
        return m;
    }

    Matrix Matrix::operator-(const Matrix& V) const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = M[i][j] - V.M[i][j];
            }
        }
        return m;
    }

    Matrix Matrix::operator+(number value) const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = M[i][j] + value;
            }
        }
        return m;
    }

    Matrix Matrix::operator-(number value) const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = M[i][j] - value;
            }
        }
        return m;
    }

    Matrix Matrix::operator*(number scale) const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = M[i][j] * scale;
            }
        }
        return m;
    }

    Matrix Matrix::operator/(number scale) const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = M[i][j] / scale;
            }
        }
        return m;
    }

    Matrix Matrix::operator*(const Matrix& V) const {
        Matrix m;
//        for (int i = 0; i < 16; ++i) {
//            for (int j = 0; j < 4; ++j) {
//                // (i / 4) returns the line from 0 to 3
//                // (i % 4) returns the column from 0 to 3
//                m.M[i / 4][i % 4] += M[i / 4][j] * V.M[j][i % 4];
//            }
//        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    m.M[i][j] += M[i][k] * V.M[k][j];
                }
            }
        }
        return m;
    }

    bool Matrix::operator==(const Matrix& V) const {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (std::abs(M[i][j] - V.M[i][j]) >
                    Epsilon + Epsilon * std::abs(M[i][j] + V.M[i][j]) * ULP) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& V) const {
        return !(*this == V);
    }

    Matrix Matrix::operator-() const {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = -M[i][j];
            }
        }
        return m;
    }

    Matrix Matrix::operator+=(const Matrix& V) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] += V.M[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator+=(number in) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] += in;
            }
        }
        return *this;
    }

    Matrix Matrix::operator-=(const Matrix& V) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] -= V.M[i][j];
            }
        }
        return *this;
    }

    Matrix Matrix::operator-=(number in) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] -= in;
            }
        }
        return *this;
    }

    Matrix Matrix::operator*=(number in) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] *= in;
            }
        }
        return *this;
    }

    Matrix Matrix::operator/=(number in) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                M[i][j] /= in;
            }
        }
        return *this;
    }

    Matrix& Matrix::operator++() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ++M[i][j];
            }
        }
        return *this;
    }

    Matrix& Matrix::operator--() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                --M[i][j];
            }
        }
        return *this;
    }

    Matrix operator-(const number& value, const Matrix& matrix) {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = value - matrix.M[i][j];
            }
        }
        return m;
    }

    Matrix operator+(const number& value, const Matrix& matrix) {
        return matrix + value;
    }

    Matrix operator*(const number& value, const Matrix& matrix) {
        return matrix * value;
    }

    Matrix operator/(const number& value, const Matrix& matrix) {
        Matrix m;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                m.M[i][j] = value / matrix.M[i][j];
            }
        }
        return m;
    }

    const number* Matrix::operator[](std::size_t idx) const {
        return M[idx];
    }

    Matrix Matrix::GetTransposed() {
        Matrix m;

        m.M[0][0] = M[0][0];
        m.M[0][1] = M[1][0];
        m.M[0][2] = M[2][0];
        m.M[0][3] = M[3][0];

        m.M[1][0] = M[0][1];
        m.M[1][1] = M[1][1];
        m.M[1][2] = M[2][1];
        m.M[1][3] = M[3][1];

        m.M[2][0] = M[0][2];
        m.M[2][1] = M[1][2];
        m.M[2][2] = M[2][2];
        m.M[2][3] = M[3][2];

        m.M[3][0] = M[0][3];
        m.M[3][1] = M[1][3];
        m.M[3][2] = M[2][3];
        m.M[3][3] = M[3][3];

        return m;
    }
} /* namespace Divisaction */