/*
 * File TMatrix.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_TMATRIX_H
#define THREEENGINE_TMATRIX_H

#include <ostream>
#include "Maths.h"

namespace ThreeEngine {


    template<int lines, int columns>
    struct TMatrix {
        number M[lines][columns];

        TMatrix() {
            Reset();
        }

        TMatrix(const number& in) {
            Reset(in);
        }

        explicit TMatrix(const number (& m)[lines * columns]) {
            Set(m);
        }

        void Reset(const float& value = 0) {
            for (int i = 0; i < lines; ++i) {
                std::fill(std::begin(M[i]), std::end(M[i]), value);
            }
        }

        void Set(const number (& m)[lines * columns]) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] = m[(i * columns) + j];
                }
            }
        }

        static TMatrix<lines, columns> Identity() {
            TMatrix<lines, columns> m;
            m.SetIdentity();
            return m;
        }

        /**
         * Set this to the identity matrix
         */
        void SetIdentity() {
            Reset(0);
            for (int i = 0; i < lines && i < columns; ++i) {
                M[i][i] = 1;
            }
        }

        /**
         * Transforms the matrix to a uni-dimensional array column major format.
         * @return uni-dimensional version of the matrix.
         */
        void ToArray(number (& array)[lines * columns]) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    array[(i * columns) + j] = M[j][i];
                }
            }
        }

        /**
         * Gets the result of component-wise addition of this and another matrix.
         *
         * @param V The matrix to add to this.
         * @return The result of matrix addition.
         */
        TMatrix<lines, columns> operator+(const TMatrix<lines, columns>& V) const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = M[i][j] + V.M[i][j];
                }
            }
            return m;
        };

        /**
         * Gets the result of component-wise subtraction of this by another matrix.
         *
         * @param V The matrix to subtract from this.
         * @return The result of matrix subtraction.
         */
        TMatrix<lines, columns> operator-(const TMatrix<lines, columns>& V) const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = M[i][j] - V.M[i][j];
                }
            }
            return m;
        };

        /**
         * Gets the result of adding to each component of the matrix.
         *
         * @param value How much to add to each component.
         * @return The result of addition.
         */
        TMatrix<lines, columns> operator+(number value) const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = M[i][j] + value;
                }
            }
            return m;
        };

        /**
         * Gets the result of subtracting from each component of the matrix.
         *
         * @param value How much to subtract from each component.
         * @return The result of subtraction.
         */
        TMatrix<lines, columns> operator-(number value) const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = M[i][j] - value;
                }
            }
            return m;
        };

        /**
         * Gets the result of scaling the matrix (multiplying each component by a value).
         *
         * @param scale What to multiply each component by.
         * @return The result of multiplication.
         */
        TMatrix<lines, columns> operator*(number scale) const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = M[i][j] * scale;
                }
            }
            return m;
        };

        /**
         * Gets the result of dividing each component of the matrix by a value.
         *
         * @param scale What to divide each component by.
         * @return The result of division.
         */
        TMatrix<lines, columns> operator/(number scale) const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = M[i][j] / scale;
                }
            }
            return m;
        };

        /**
         * Gets the result of multiplying a TMatrix to this.
         *
         * @param V The matrix to multiply with.
         * @return The result of multiplication.
         */
        template<int otherColumns>
        TMatrix<lines, otherColumns> operator*(const TMatrix<columns, otherColumns>& V) const {
            TMatrix<lines, otherColumns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < otherColumns; ++j) {
                    for (int k = 0; k < columns; ++k) {
                        m.M[i][j] += M[i][k] * V.M[k][j];
                    }
                }
            }
            return m;
        }

        /**
         * Check against another matrix for equality.
         *
         * @param V The matrix to check against.
         * @return true if the matrixs are equal, false otherwise.
         */
        bool operator==(const TMatrix<lines, columns>& V) const {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if (std::abs(M[i][j] - V.M[i][j]) >
                        Epsilon + Epsilon * std::abs(M[i][j] + V.M[i][j]) * ULP) {
                        return false;
                    }
                }
            }
            return true;
        };

        /**
         * Check against another matrix for inequality.
         *
         * @param V The matrix to check against.
         * @return true if the matrixs are not equal, false otherwise.
         */
        bool operator!=(const TMatrix<lines, columns>& V) const {
            return !(*this == V);
        }

        /**
         * Get a negated copy of the matrix.
         *
         * @return A negated copy of the matrix.
         */
        TMatrix<lines, columns> operator-() const {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = -M[i][j];
                }
            }
            return m;
        };

        /**
         * Adds another matrix to this.
         *
         * @param V TMatrix to add to this.
         * @return Copy of the matrix after addition.
         */
        TMatrix<lines, columns> operator+=(const TMatrix<lines, columns>& V) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] += V.M[i][j];
                }
            }
            return *this;
        }

        /**
         * Adds a scalar to this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the matrix after addition.
         */
        TMatrix<lines, columns> operator+=(number in) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] += in;
                }
            }
            return *this;
        }

        /**
         * Subtracts another matrix from this.
         *
         * @param V TMatrix to subtract from this.
         * @return Copy of the matrix after subtraction.
         */
        TMatrix<lines, columns> operator-=(const TMatrix<lines, columns>& V) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] -= V.M[i][j];
                }
            }
            return *this;
        }

        /**
         * Subtracts a scalar from this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the matrix after subtraction.
         */
        TMatrix<lines, columns> operator-=(number in) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] -= in;
                }
            }
            return *this;
        }

        /**
         * Scales the matrix.
         *
         * @param in Amount to scale this matrix by.
         * @return Copy of the matrix after scaling.
         */
        TMatrix<lines, columns> operator*=(number in) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] *= in;
                }
            }
            return *this;
        }

        /**
         * Divides the matrix by a number.
         *
         * @param in What to divide this matrix by.
         * @return Copy of the matrix after division.
         */
        TMatrix<lines, columns> operator/=(number in) {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    M[i][j] /= in;
                }
            }
            return *this;
        }

        /**
         * Adds one to the matrix.
         *
         * @return Reference to this matrix after addition.
         */
        TMatrix<lines, columns>& operator++() {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    ++M[i][j];
                }
            }
            return *this;
        }

        /**
         * Subtract one to the matrix.
         *
         * @return Reference to this matrix after subtraction.
         */
        TMatrix<lines, columns>& operator--() {
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    --M[i][j];
                }
            }
            return *this;
        }

        /**
         * Results in a matrix where each element is the value subtracted with the matrix's component.
         * @param value to subtract from.
         * @param matrix to subtract with.
         * @return returns a matrix after subtraction.
         */
        friend TMatrix<lines, columns>
        operator-(const number& value, const TMatrix<lines, columns>& matrix) {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = value - matrix.M[i][j];
                }
            }
            return m;
        }

        /**
         * Results in a matrix where each element is the value added with the matrix's component.
         * @param value to add to.
         * @param matrix to add with.
         * @return returns a matrix after addition.
         */
        friend TMatrix<lines, columns>
        operator+(const number& value, const TMatrix<lines, columns>& matrix) {
            return matrix + value;
        }


        /**
         * Results in a matrix where each element is the value multiplied with the matrix's component.
         * @param value to multiply to.
         * @param matrix to multiply with.
         * @return returns a matrix after multiplying.
         */
        friend TMatrix<lines, columns>
        operator*(const number& value, const TMatrix<lines, columns>& matrix) {
            return matrix * value;
        }

        /**
         * Results in a matrix where each element is the value divided with the matrix's component.
         * @param value to divide to.
         * @param matrix to divide with.
         * @return returns a matrix after division.
         */
        friend TMatrix<lines, columns>
        operator/(const number& value, const TMatrix<lines, columns>& matrix) {
            TMatrix<lines, columns> m;
            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[i][j] = value / matrix.M[i][j];
                }
            }
            return m;
        }

        /**
         * Results in a transposed matrix of this.
         * @return transposed matrix.
         */
        TMatrix<columns, lines> GetTransposed() {
            TMatrix<columns, lines> m;

            for (int i = 0; i < lines; ++i) {
                for (int j = 0; j < columns; ++j) {
                    m.M[j][i] = M[i][j];
                }
            }

            return m;
        }

        friend std::ostream& operator<<(std::ostream& os, const TMatrix& matrix) {
            for (int i = 0; i < lines; ++i) {
                os << "[ ";
                for (int j = 0; j < columns; ++j) {
                    os << matrix.M[i][j];
                    if (j < (columns - 1)) {
                        os << " , ";
                    }
                }
                os << " ]" << std::endl;
            }
            return os;
        };

        friend std::istream& operator>>(std::istream& is, const TMatrix&) {
            // TODO Implement in stream
            return is;
        };

        operator std::string() const {
            std::string message = "\n";
            for (int i = 0; i < lines; ++i) {
                message += "[ ";
                for (int j = 0; j < columns; ++j) {
                    message += std::to_string(M[i][j]);
                    if (j < (columns - 1)) {
                        message += " , ";
                    }
                }
                message += " ]\n";
            }
            return message;
        }
    };

} /* namespace Divisaction */

#endif //THREEENGINE_TMATRIX_H
