/*
 * File Matrix.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_MATRIX_H
#define THREEENGINE_MATRIX_H

#include <ostream>
#include <string>
#include "Maths.h"
#include "Vector4.h"
#include "Matrix3.h"

namespace ThreeEngine {

    struct Matrix {

        number M[4][4];

        Matrix();

        explicit Matrix(number in);

        explicit Matrix(Matrix3 m);

        Matrix(number in0, number in1, number in2, number in3,
               number in4, number in5, number in6, number in7,
               number in8, number in9, number in10, number in11,
               number in12, number in13, number in14, number in15
        );

        Matrix(const Matrix& other);

        Matrix& operator=(const Matrix& other);

        static Matrix GetRandom(const number& max);

        void Set(number in0, number in1, number in2, number in3,
                 number in4, number in5, number in6, number in7,
                 number in8, number in9, number in10, number in11,
                 number in12, number in13, number in14, number in15
        );


        /**
         * Set this to the identity matrix
         */
        void SetIdentity();

        /**
         * Set this to the identity matrix
         */
        void SetMatrix3(const Matrix3& m);

        /**
         * Set all values in this to given value
         *
         * @param value Value to fill all fields. Default is 0.
         */
        void Reset(const float& value = 0.0f);

        /**
         * Transforms the matrix to a uni-dimensional array column major format.
         * @return uni-dimensional version of the matrix.
         */
        void ToArray(number (& array)[16]);

        /**
         * Gets the result of component-wise addition of this and another matrix.
         *
         * @param V The matrix to add to this.
         * @return The result of matrix addition.
         */
        Matrix operator+(const Matrix& V) const;

        /**
         * Gets the result of component-wise subtraction of this by another matrix.
         *
         * @param V The matrix to subtract from this.
         * @return The result of matrix subtraction.
         */
        Matrix operator-(const Matrix& V) const;

        /**
         * Gets the result of adding to each component of the matrix.
         *
         * @param value How much to add to each component.
         * @return The result of addition.
         */
        Matrix operator+(number value) const;

        /**
         * Gets the result of subtracting from each component of the matrix.
         *
         * @param value How much to subtract from each component.
         * @return The result of subtraction.
         */
        Matrix operator-(number value) const;

        /**
         * Gets the result of scaling the matrix (multiplying each component by a value).
         *
         * @param scale What to multiply each component by.
         * @return The result of multiplication.
         */
        Matrix operator*(number scale) const;

        /**
         * Gets the result of dividing each component of the matrix by a value.
         *
         * @param scale What to divide each component by.
         * @return The result of division.
         */
        Matrix operator/(number scale) const;

        /**
         * Gets the result of multiplying a Matrix to this.
         *
         * @param V The matrix to multiply with.
         * @return The result of multiplication.
         */
        Matrix operator*(const Matrix& V) const;

        /**
         * Results in the multiplication of this matrix with a Vector.
         * @param v
         * @return multiplication vector
         */
        Vector4 operator*(const Vector4& v);

        /**
         * Results in the multiplication of a vector with this matrix.
         * @param v
         * @return multiplication vector
         */
        friend Vector4 operator*(const Vector4& v, const Matrix& m);

        /**
         * Check against another matrix for equality.
         *
         * @param V The matrix to check against.
         * @return true if the matrixs are equal, false otherwise.
         */
        bool operator==(const Matrix& V) const;

        /**
         * Check against another matrix for inequality.
         *
         * @param V The matrix to check against.
         * @return true if the matrixs are not equal, false otherwise.
         */
        bool operator!=(const Matrix& V) const;

        /**
         * Get a negated copy of the matrix.
         *
         * @return A negated copy of the matrix.
         */
        Matrix operator-() const;

        /**
         * Adds another matrix to this.
         *
         * @param V Matrix to add to this.
         * @return Copy of the matrix after addition.
         */
        Matrix operator+=(const Matrix& V);

        /**
         * Adds a scalar to this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the matrix after addition.
         */
        Matrix operator+=(number in);

        /**
         * Subtracts another matrix from this.
         *
         * @param V Matrix to subtract from this.
         * @return Copy of the matrix after subtraction.
         */
        Matrix operator-=(const Matrix& V);

        /**
         * Subtracts a scalar from this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the matrix after subtraction.
         */
        Matrix operator-=(number in);

        /**
         * Scales the matrix.
         *
         * @param in Amount to scale this matrix by.
         * @return Copy of the matrix after scaling.
         */
        Matrix operator*=(number in);

        /**
         * Divides the matrix by a number.
         *
         * @param in What to divide this matrix by.
         * @return Copy of the matrix after division.
         */
        Matrix operator/=(number in);

        /**
         * Adds one to the matrix.
         *
         * @return Reference to this matrix after addition.
         */
        Matrix& operator++();

        /**
         * Subtract one to the matrix.
         *
         * @return Reference to this matrix after subtraction.
         */
        Matrix& operator--();

        /**
         * Results in a matrix where each element is the value subtracted with the matrix's component.
         * @param value to subtract from.
         * @param matrix to subtract with.
         * @return returns a matrix after subtraction.
         */
        friend Matrix operator-(const number& value, const Matrix& matrix);

        /**
         * Results in a matrix where each element is the value added with the matrix's component.
         * @param value to add to.
         * @param matrix to add with.
         * @return returns a matrix after addition.
         */
        friend Matrix operator+(const number& value, const Matrix& matrix);


        /**
         * Results in a matrix where each element is the value multiplied with the matrix's component.
         * @param value to multiply to.
         * @param matrix to multiply with.
         * @return returns a matrix after multiplying.
         */
        friend Matrix operator*(const number& value, const Matrix& matrix);

        /**
         * Results in a matrix where each element is the value divided with the matrix's component.
         * @param value to divide to.
         * @param matrix to divide with.
         * @return returns a matrix after division.
         */
        friend Matrix operator/(const number& value, const Matrix& matrix);

        /**
         * Allows access to the matrix in a more direct way. Equivalent to matrix.M[].
         * @param idx line index.
         * @return array of all the elements of the given line.
         */
        const number* operator[](std::size_t idx) const;

        /**
         * Results in a transposed matrix of this.
         * @return transposed matrix.
         */
        Matrix GetTransposed();

        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
            for (int i = 0; i < 4; ++i) {
                os << "[ ";
                for (int j = 0; j < 4; ++j) {
                    os << matrix.M[i][j];
                    if (j < 3) {
                        os << " , ";
                    }
                }
                os << " ]" << std::endl;
            }
            return os;
        };

        friend std::istream& operator>>(std::istream& is, const Matrix&) {
            // TODO Implement in stream
            return is;
        };

        operator std::string() const {
            std::string message = "\n";
            for (int i = 0; i < 4; ++i) {
                message += "[ ";
                for (int j = 0; j < 4; ++j) {
                    message += std::to_string(M[i][j]);
                    if (j < 3) {
                        message += " , ";
                    }
                }
                message += " ]\n";
            }
            return message;
        }

        operator Matrix3() const {
            Matrix3 m;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    m.M[i][j] = M[i][j];
                }
            }
            return m;
        }

        /** Identity Matrix */
        static Matrix IdentityMatrix();

        static Matrix
        ScaleMatrix(const number& inX, const number& inY, const number& inZ, const number& inW);

        static Matrix ScaleMatrixInverted(const number& inX, const number& inY, const number& inZ,
                                           const number& inW);

        static Matrix RotationMatrix(Maths::Axis axis, const number& angle);

        static Matrix TranslationMatrix(const Vector& vector);

        static Matrix TranslationMatrix(const Vector4& vector);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_MATRIX_H
