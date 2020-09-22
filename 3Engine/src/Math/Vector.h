/*
 * File Vector.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_VECTOR_H
#define THREEENGINE_VECTOR_H

#include <string>
#include <sstream>
#include <iostream>
#include "Maths.h"
#include "Vector2.h"

namespace ThreeEngine {

    struct Vector {
        number X, Y, Z;


        /** A zero vector (0,0,0) */
        static const Vector ZeroVector;

        /** One vector (1,1,1) */
        static const Vector OneVector;

        /** OpenGL up vector (0,1,0) (INUSE) */
        /** Unreal up vector (0,0,1) */
        static const Vector UpVector;

        /** OpenGL up vector (0,-1,0) (INUSE) */
        /** Unreal up vector (0,0,-1) */
        static const Vector DownVector;

        /** OpenGL forward vector (0,0,-1) (INUSE) */
        /** Unreal forward vector (1,0,0) */
        static const Vector ForwardVector;

        /** OpenGL forward vector (0,0,1) (INUSE) */
        /** Unreal forward vector (-1,0,0) */
        static const Vector BackVector;

        /** OpenGL left vector (-1,0,0) (INUSE) */
        /** Unreal left vector (0,1,0) */
        static const Vector LeftVector;

        /** OpenGL right vector (1,0,0) (INUSE) */
        /** Unreal right vector (0,-1,0) */
        static const Vector RightVector;

        Vector();

        explicit Vector(number in);

        Vector(number inX, number inY, number inZ);

        explicit Vector(const Vector2& other, number inZ = 0);

        Vector(const Vector& other);

        Vector& operator=(const Vector& other);

        static Vector GetRandom(const number& max);

        /**
         * Calculate cross product between this and another vector.
         *
         * @param V The other vector.
         * @return The cross product.
         */
        Vector operator^(const Vector& V) const;

        /**
         * Calculate the cross product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The cross product.
         */
        static Vector CrossProduct(const Vector& A, const Vector& B);

        /**
         * Calculate the dot product between this and another vector.
         *
         * @param V The other vector.
         * @return The dot product.
         */
        number operator|(const Vector& V) const;

        /**
         * Calculate the dot product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The dot product.
         */
        static number DotProduct(const Vector& A, const Vector& B);

        /**
         * Gets the result of component-wise addition of this and another vector.
         *
         * @param V The vector to add to this.
         * @return The result of vector addition.
         */
        Vector operator+(const Vector& V) const;

        /**
         * Gets the result of component-wise subtraction of this by another vector.
         *
         * @param V The vector to subtract from this.
         * @return The result of vector subtraction.
         */
        Vector operator-(const Vector& V) const;

        /**
         * Gets the result of subtracting from each component of the vector.
         *
         * @param value How much to subtract from each component.
         * @return The result of subtraction.
         */
        Vector operator-(number value) const;

        /**
         * Gets the result of adding to each component of the vector.
         *
         * @param value How much to add to each component.
         * @return The result of addition.
         */
        Vector operator+(number value) const;

        /**
         * Gets the result of scaling the vector (multiplying each component by a value).
         *
         * @param scale What to multiply each component by.
         * @return The result of multiplication.
         */
        Vector operator*(number scale) const;

        /**
         * Gets the result of dividing each component of the vector by a value.
         *
         * @param scale What to divide each component by.
         * @return The result of division.
         */
        Vector operator/(number scale) const;

        /**
         * Gets the result of component-wise multiplication of this vector by another.
         *
         * @param V The vector to multiply with.
         * @return The result of multiplication.
         */
        Vector operator*(const Vector& V) const;

        /**
         * Gets the result of component-wise division of this vector by another.
         *
         * @param V The vector to divide by.
         * @return The result of division.
         */
        Vector operator/(const Vector& V) const;

        /**
         * Check against another vector for equality.
         *
         * @param V The vector to check against.
         * @return true if the vectors are equal, false otherwise.
         */
        bool operator==(const Vector& V) const;

        /**
         * Check against another vector for inequality.
         *
         * @param V The vector to check against.
         * @return true if the vectors are not equal, false otherwise.
         */
        bool operator!=(const Vector& V) const;

        /**
         * Get a negated copy of the vector.
         *
         * @return A negated copy of the vector.
         */
        Vector operator-() const;

        /**
         * Adds another vector to this.
         *
         * @param V Vector to add to this.
         * @return Copy of the vector after addition.
         */
        Vector operator+=(const Vector& V);

        /**
         * Adds a scalar to this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the vector after addition.
         */
        Vector operator+=(number in);

        /**
         * Subtracts another vector from this.
         *
         * @param V Vector to subtract from this.
         * @return Copy of the vector after subtraction.
         */
        Vector operator-=(const Vector& V);

        /**
         * Subtracts a scalar from this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the vector after subtraction.
         */
        Vector operator-=(number in);

        /**
         * Scales the vector.
         *
         * @param in Amount to scale this vector by.
         * @return Copy of the vector after scaling.
         */
        Vector operator*=(number in);

        /**
         * Divides the vector by a number.
         *
         * @param in What to divide this vector by.
         * @return Copy of the vector after division.
         */
        Vector operator/=(number in);

        /**
         * Multiplies the vector with another vector, using component-wise multiplication.
         *
         * @param V What to multiply this vector with.
         * @return Copy of the vector after multiplication.
         */
        Vector operator*=(const Vector& V);

        /**
         * Divides the vector by another vector, using component-wise division.
         *
         * @param V What to divide vector by.
         * @return Copy of the vector after division.
         */
        Vector operator/=(const Vector& V);

        /**
         * Adds one to the vector.
         *
         * @return Reference to this vector after addition.
         */
        Vector& operator++();

        /**
         * Subtract one to the vector.
         *
         * @return Reference to this vector after subtraction.
         */
        Vector& operator--();

        /**
         * Results in a vector where each element is the value subtracted with the vector's component.
         * @param value to subtract from.
         * @param vector to subtract with.
         * @return returns a vector after subtraction.
         */
        friend Vector operator-(const number& value, const Vector& vector);

        /**
         * Results in a vector where each element is the value added with the vector's component.
         * @param value to add to.
         * @param vector to add with.
         * @return returns a vector after addition.
         */
        friend Vector operator+(const number& value, const Vector& vector);


        /**
         * Results in a vector where each element is the value multiplied with the vector's component.
         * @param value to multiply to.
         * @param vector to multiply with.
         * @return returns a vector after multiplying.
         */
        friend Vector operator*(const number& value, const Vector& vector);

        /**
         * Results in a vector where each element is the value divided with the vector's component.
         * @param value to divide to.
         * @param vector to divide with.
         * @return returns a vector after division.
         */
        friend Vector operator/(const number& value, const Vector& vector);

        /**
         * Normalize this vector in-place if it is large enough.
         *
         * @return true if the vector was normalized correctly, false otherwise.
         */
        bool Normalize();

        /**
         * Checks whether vector is normalized.
         *
         * @return true if Normalized, false otherwise.
         */
        bool IsNormalized() const;

        /**
         * Normalize this vector in-place if it is large enough.
         *
         * @return true if the vector was normalized correctly, false otherwise.
         */
        static Vector Normalize(Vector v);

        /**
         * Gets specific component of the vector.
         *
         * @param Index the index of vector component
         * @return reference to component.
         */
        float& operator[](int Index);

        /**
         * Gets specific component of the vector.
         *
         * @param Index the index of vector component
         * @return reference to component.
         */
        float operator[](int Index) const;

        void Set(const number& inX, const number& inY, const number& inZ);

        friend std::ostream&
        operator<<(std::ostream& os, const Vector& vector) {
            os << "{ " << vector.X << ", " << vector.Y << ", " << vector.Z
               << " }" << std::endl;
            return os;
        };

        friend std::istream& operator>>(std::istream& is, Vector& vector) {
            is >> vector.X >> vector.Y >> vector.Z;
            return is;
        };

        operator std::string() const {
            return std::string(
                    "{ " + std::to_string(X) + ", " + std::to_string(Y) + ", " +
                    std::to_string(Z) + " }");
        }

        operator Vector2() const {
            return Vector2(X, Y);
        }

        /**
         * Calculates the distance value of this vector
         * @return Distance
         */
        number Dist() const;

        /**
         * Calculates the square of the distance value of this vector
         * @return Square of the distance
         */
        number DistSquared() const;

        /**
         * Calculates the projection of this vector onto the given one.
         * @param A vector to project onto.
         * @return Vector that resulted from the projection.
         */
        Vector ProjectOnTo(const Vector& A) const;

        static Vector Lerp(const Vector& v0, const Vector& v1, number time);
    };

} /* namespace Divisaction */

#endif //THREEENGINE_VECTOR_H
