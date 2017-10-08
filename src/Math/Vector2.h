/*
 * File Vector2.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_VECTOR2_H
#define THREEENGINE_VECTOR2_H

#include <string>
#include <iostream>
#include "Maths.h"

namespace ThreeEngine {

    struct Vector2 {
        number X, Y;


        /** A zero vector (0,0) */
        static const Vector2 ZeroVector;

        /** One vector (1,1) */
        static const Vector2 OneVector;

        /** World up vector (0,1) */
        static const Vector2 UpVector;

        /** Unreal right vector (1,0) */
        static const Vector2 RightVector;

        Vector2();

        explicit Vector2(number in);

        Vector2(number inX, number inY);

        Vector2(const Vector2& other);

        Vector2& operator=(const Vector2& other);

        Vector2 GetRandom(const number& max);

        /**
         * Calculate the dot product between this and another vector.
         *
         * @param V The other vector.
         * @return The dot product.
         */
        number operator|(const Vector2& V) const;

        /**
         * Calculate the dot product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The dot product.
         */
        static number DotProduct(const Vector2& A, const Vector2& B);

        /**
         * Gets the result of component-wise addition of this and another vector.
         *
         * @param V The vector to add to this.
         * @return The result of vector addition.
         */
        Vector2 operator+(const Vector2& V) const;

        /**
         * Gets the result of component-wise subtraction of this by another vector.
         *
         * @param V The vector to subtract from this.
         * @return The result of vector subtraction.
         */
        Vector2 operator-(const Vector2& V) const;

        /**
         * Gets the result of subtracting from each component of the vector.
         *
         * @param value How much to subtract from each component.
         * @return The result of subtraction.
         */
        Vector2 operator-(number value) const;

        /**
         * Gets the result of adding to each component of the vector.
         *
         * @param value How much to add to each component.
         * @return The result of addition.
         */
        Vector2 operator+(number value) const;

        /**
         * Gets the result of scaling the vector (multiplying each component by a value).
         *
         * @param scale What to multiply each component by.
         * @return The result of multiplication.
         */
        Vector2 operator*(number scale) const;

        /**
         * Gets the result of dividing each component of the vector by a value.
         *
         * @param scale What to divide each component by.
         * @return The result of division.
         */
        Vector2 operator/(number scale) const;

        /**
         * Gets the result of component-wise multiplication of this vector by another.
         *
         * @param V The vector to multiply with.
         * @return The result of multiplication.
         */
        Vector2 operator*(const Vector2& V) const;

        /**
         * Gets the result of component-wise division of this vector by another.
         *
         * @param V The vector to divide by.
         * @return The result of division.
         */
        Vector2 operator/(const Vector2& V) const;

        /**
         * Check against another vector for equality.
         *
         * @param V The vector to check against.
         * @return true if the vectors are equal, false otherwise.
         */
        bool operator==(const Vector2& V) const;

        /**
         * Check against another vector for inequality.
         *
         * @param V The vector to check against.
         * @return true if the vectors are not equal, false otherwise.
         */
        bool operator!=(const Vector2& V) const;

        /**
         * Get a negated copy of the vector.
         *
         * @return A negated copy of the vector.
         */
        Vector2 operator-() const;

        /**
         * Adds another vector to this.
         *
         * @param V Vector to add to this.
         * @return Copy of the vector after addition.
         */
        Vector2 operator+=(const Vector2& V);

        /**
         * Adds a scalar to this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the vector after addition.
         */
        Vector2 operator+=(number in);

        /**
         * Subtracts another vector from this.
         *
         * @param V Vector to subtract from this.
         * @return Copy of the vector after subtraction.
         */
        Vector2 operator-=(const Vector2& V);

        /**
         * Subtracts a scalar from this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the vector after subtraction.
         */
        Vector2 operator-=(number in);

        /**
         * Scales the vector.
         *
         * @param in Amount to scale this vector by.
         * @return Copy of the vector after scaling.
         */
        Vector2 operator*=(number in);

        /**
         * Divides the vector by a number.
         *
         * @param in What to divide this vector by.
         * @return Copy of the vector after division.
         */
        Vector2 operator/=(number in);

        /**
         * Multiplies the vector with another vector, using component-wise multiplication.
         *
         * @param V What to multiply this vector with.
         * @return Copy of the vector after multiplication.
         */
        Vector2 operator*=(const Vector2& V);

        /**
         * Divides the vector by another vector, using component-wise division.
         *
         * @param V What to divide vector by.
         * @return Copy of the vector after division.
         */
        Vector2 operator/=(const Vector2& V);

        /**
         * Results in a vector where each element is the value subtracted with the vector's component.
         * @param value to subtract from.
         * @param vector to subtract with.
         * @return returns a vector after subtraction.
         */
        friend Vector2 operator-(const number& value, const Vector2& vector);

        /**
         * Results in a vector where each element is the value added with the vector's component.
         * @param value to add to.
         * @param vector to add with.
         * @return returns a vector after addition.
         */
        friend Vector2 operator+(const number& value, const Vector2& vector);


        /**
         * Results in a vector where each element is the value multiplied with the vector's component.
         * @param value to multiply to.
         * @param vector to multiply with.
         * @return returns a vector after multiplying.
         */
        friend Vector2 operator*(const number& value, const Vector2& vector);

        /**
         * Results in a vector where each element is the value divided with the vector's component.
         * @param value to divide to.
         * @param vector to divide with.
         * @return returns a vector after division.
         */
        friend Vector2 operator/(const number& value, const Vector2& vector);

        void Set(const number& inX, const number& inY);

        friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
            os << "{ " << vector.X << ", " << vector.Y << " }" << std::endl;
            return os;
        };

        friend std::istream& operator>>(std::istream& is, const Vector2&) {
            // TODO Implement in stream
            return is;
        };

        operator std::string() const {
            return std::string("{ " + std::to_string(X) + ", " + std::to_string(Y) + " }");
        }

        number Dist() const;

        number DistSquared() const;

        Vector2 ProjectOnTo(const Vector2& A) const;
    };

} /* namespace Divisaction */

#endif //THREEENGINE_VECTOR2_H
