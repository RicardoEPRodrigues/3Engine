/*
 * File Vector4.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_VECTOR4_H
#define THREEENGINE_VECTOR4_H

#include "Maths.h"
#include "Vector.h"

namespace ThreeEngine {

    struct Vector4 {
        number X, Y, Z, W;


        /** A zero vector (0,0,0) */
        static const Vector4 ZeroVector;

        /** One vector (1,1,1) */
        static const Vector4 OneVector;

        /** World up vector (0,0,1) */
        static const Vector4 UpVector;

        /** Unreal forward vector (1,0,0) */
        static const Vector4 ForwardVector;

        /** Unreal right vector (0,1,0) */
        static const Vector4 LeftVector;

        Vector4();

        explicit Vector4(number in);

        Vector4(number inX, number inY, number inZ, number inW = 1.0f);

        explicit Vector4(const Vector2& other, number inZ = 0,
                         number inW = 1.0f);

        explicit Vector4(const Vector& other, number inW = 1.0f);

        Vector4(const Vector4& other);

        Vector4& operator=(const Vector4& other);

        static Vector4 GetRandom(const number& max);

        /**
         * Calculate the cross product between this and another vector.
         *
         * @param V The other vector.
         * @return The cross product.
         */
        Vector4 operator^(const Vector4& V) const;

        /**
         * Calculate the cross product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The cross product.
         */
        static Vector4 CrossProduct(const Vector4& A, const Vector4& B);

        /**
         * Calculate the dot product between this and another vector.
         *
         * @param V The other vector.
         * @return The dot product.
         */
        number operator|(const Vector4& V) const;

        /**
         * Calculate the dot product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The dot product.
         */
        static number DotProduct(const Vector4& A, const Vector4& B);

        /**
         * Calculate the 3D vector dot product of two vectors.
         *
         * @param A The first vector.
         * @param B The second vector.
         * @return The dot product.
         */
        static number DotProduct3(const Vector4& A, const Vector4& B);

        /**
         * Gets the result of component-wise addition of this and another vector.
         *
         * @param V The vector to add to this.
         * @return The result of vector addition.
         */
        Vector4 operator+(const Vector4& V) const;

        /**
         * Gets the result of component-wise subtraction of this by another vector.
         *
         * @param V The vector to subtract from this.
         * @return The result of vector subtraction.
         */
        Vector4 operator-(const Vector4& V) const;

        /**
         * Gets the result of subtracting from each component of the vector.
         *
         * @param value How much to subtract from each component.
         * @return The result of subtraction.
         */
        Vector4 operator-(number value) const;

        /**
         * Gets the result of adding to each component of the vector.
         *
         * @param value How much to add to each component.
         * @return The result of addition.
         */
        Vector4 operator+(number value) const;

        /**
         * Gets the result of scaling the vector (multiplying each component by a value).
         *
         * @param scale What to multiply each component by.
         * @return The result of multiplication.
         */
        Vector4 operator*(number scale) const;

        /**
         * Gets the result of dividing each component of the vector by a value.
         *
         * @param scale What to divide each component by.
         * @return The result of division.
         */
        Vector4 operator/(number scale) const;

        /**
         * Gets the result of component-wise multiplication of this vector by another.
         *
         * @param V The vector to multiply with.
         * @return The result of multiplication.
         */
        Vector4 operator*(const Vector4& V) const;

        /**
         * Gets the result of component-wise division of this vector by another.
         *
         * @param V The vector to divide by.
         * @return The result of division.
         */
        Vector4 operator/(const Vector4& V) const;

        /**
         * Check against another vector for equality.
         *
         * @param V The vector to check against.
         * @return true if the vectors are equal, false otherwise.
         */
        bool operator==(const Vector4& V) const;

        /**
         * Check against another vector for inequality.
         *
         * @param V The vector to check against.
         * @return true if the vectors are not equal, false otherwise.
         */
        bool operator!=(const Vector4& V) const;

        /**
         * Get a negated copy of the vector.
         *
         * @return A negated copy of the vector.
         */
        Vector4 operator-() const;

        /**
         * Adds another vector to this.
         *
         * @param V Vector to add to this.
         * @return Copy of the vector after addition.
         */
        Vector4 operator+=(const Vector4& V);

        /**
         * Adds a scalar to this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the vector after addition.
         */
        Vector4 operator+=(number in);

        /**
         * Subtracts another vector from this.
         *
         * @param V Vector to subtract from this.
         * @return Copy of the vector after subtraction.
         */
        Vector4 operator-=(const Vector4& V);

        /**
         * Subtracts a scalar from this.
         *
         * @param in Scalar to add to this.
         * @return Copy of the vector after subtraction.
         */
        Vector4 operator-=(number in);

        /**
         * Scales the vector.
         *
         * @param in Amount to scale this vector by.
         * @return Copy of the vector after scaling.
         */
        Vector4 operator*=(number in);

        /**
         * Divides the vector by a number.
         *
         * @param in What to divide this vector by.
         * @return Copy of the vector after division.
         */
        Vector4 operator/=(number in);

        /**
         * Multiplies the vector with another vector, using component-wise multiplication.
         *
         * @param V What to multiply this vector with.
         * @return Copy of the vector after multiplication.
         */
        Vector4 operator*=(const Vector4& V);

        /**
         * Divides the vector by another vector, using component-wise division.
         *
         * @param V What to divide vector by.
         * @return Copy of the vector after division.
         */
        Vector4 operator/=(const Vector4& V);

        /**
         * Adds one to the vector.
         *
         * @return Reference to this vector after addition.
         */
        Vector4& operator++();

        /**
         * Subtract one to the vector.
         *
         * @return Reference to this vector after subtraction.
         */
        Vector4& operator--();

        /**
         * Results in a vector where each element is the value subtracted with the vector's component.
         * @param value to subtract from.
         * @param vector to subtract with.
         * @return returns a vector after subtraction.
         */
        friend Vector4 operator-(const number& value, const Vector4& vector);

        /**
         * Results in a vector where each element is the value added with the vector's component.
         * @param value to add to.
         * @param vector to add with.
         * @return returns a vector after addition.
         */
        friend Vector4 operator+(const number& value, const Vector4& vector);


        /**
         * Results in a vector where each element is the value multiplied with the vector's component.
         * @param value to multiply to.
         * @param vector to multiply with.
         * @return returns a vector after multiplying.
         */
        friend Vector4 operator*(const number& value, const Vector4& vector);

        /**
         * Results in a vector where each element is the value divided with the vector's component.
         * @param value to divide to.
         * @param vector to divide with.
         * @return returns a vector after division.
         */
        friend Vector4 operator/(const number& value, const Vector4& vector);

        /**
         * Sets the vectors components to the given values
         *
         * @param inX X coordinate
         * @param inY Y coordinate
         * @param inZ Z coordinate
         */
        void Set(const number& inX, const number& inY, const number& inZ);

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

        /**
         * Sets the vectors components to the given values
         *
         * @param inX X coordinate
         * @param inY Y coordinate
         * @param inZ Z coordinate
         * @param inW W coordinate
         */
        void Set(const number& inX, const number& inY, const number& inZ,
                 const number& inW);

        friend std::ostream&
        operator<<(std::ostream& os, const Vector4& vector) {
            os << "{ " << vector.X << ", " << vector.Y << ", " << vector.Z
               << ", " << vector.W
               << " }" << std::endl;
            return os;
        };

        friend std::istream& operator>>(std::istream& is, Vector4& vector) {
            is >> vector.X >> vector.Y >> vector.Z >> vector.W;
            return is;
        };

        operator std::string() const {
            return std::string(
                    "{ " + std::to_string(X) + ", " + std::to_string(Y) + ", " +
                    std::to_string(Z) + ", " + std::to_string(W) + " }");
        }

        operator Vector() const {
            return Vector(X, Y, Z);
        }

        operator Vector2() const {
            return Vector2(X, Y);
        }

        /**
         * Calculates the distance value of the Vector3 in this vector
         * @return Distance of the vector3
         */
        number Dist3() const;

        /**
         * Calculates the square of the distance value of the Vector3 in this vector
         * @return Square of the distance of the vector3
         */
        number DistSquared3() const;

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
        Vector4 ProjectOnTo(const Vector4& A) const;

        Vector4 Dehomogenize();
    };

} /* namespace Divisaction */

#endif //THREEENGINE_VECTOR4_H
