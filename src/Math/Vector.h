/*
 * File Vector.h in project ThreeEngine
 * 
 * Copyright (C) Ricardo Rodrigues 2017 - All Rights Reserved
 */
#ifndef THREEENGINE_VECTOR_H
#define THREEENGINE_VECTOR_H

#include <string>

namespace ThreeEngine {

    struct Vector {
            float X, Y, Z;


            /** A zero vector (0,0,0) */
            static const Vector ZeroVector;

            /** One vector (1,1,1) */
            static const Vector OneVector;

            /** World up vector (0,0,1) */
            static const Vector UpVector;

            /** Unreal forward vector (1,0,0) */
            static const Vector ForwardVector;

            /** Unreal right vector (0,1,0) */
            static const Vector LeftVector;

            Vector();

            explicit Vector(float in);

            Vector(float inX, float inY, float inZ);

            Vector(const Vector& other);

            Vector& operator=(const Vector& other);

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
            float operator|(const Vector& V) const;

            /**
             * Calculate the dot product of two vectors.
             *
             * @param A The first vector.
             * @param B The second vector.
             * @return The dot product.
             */
            static float DotProduct(const Vector& A, const Vector& B);

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
            Vector operator-(float value) const;

            /**
             * Gets the result of adding to each component of the vector.
             *
             * @param value How much to add to each component.
             * @return The result of addition.
             */
            Vector operator+(float value) const;

            /**
             * Gets the result of scaling the vector (multiplying each component by a value).
             *
             * @param scale What to multiply each component by.
             * @return The result of multiplication.
             */
            Vector operator*(float scale) const;

            /**
             * Gets the result of dividing each component of the vector by a value.
             *
             * @param scale What to divide each component by.
             * @return The result of division.
             */
            Vector operator/(float scale) const;

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
            Vector operator+=(float in);

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
            Vector operator-=(float in);

            /**
             * Scales the vector.
             *
             * @param in Amount to scale this vector by.
             * @return Copy of the vector after scaling.
             */
            Vector operator*=(float in);

            /**
             * Divides the vector by a number.
             *
             * @param in What to divide this vector by.
             * @return Copy of the vector after division.
             */
            Vector operator/=(float in);

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


            friend std::ostream &operator<<(std::ostream& os, const Vector& vector) {
                os << "{ " << vector.X << ", " << vector.Y << ", " <<
                    vector.Z << " }" << std::endl;
                return os;
            };
            friend std::istream &operator>>(std::istream& is, const Vector& vector) {
                // TODO Implement in stream
                return is;
            };

            operator std::string() const {
                return std::string("{ " + std::to_string(X) + ", " + std::to_string(Y) + ", " +
                                   std::to_string(Z) + " }");
            }

            float Dist() const;

            float DistSquared() const;

            Vector ProjectOnTo(const Vector& A) const ;

    };

    Vector operator-(float value, Vector vector);

    Vector operator+(float value, Vector vector);

    Vector operator*(float value, Vector vector);

    Vector operator/(float value, Vector vector);

} /* namespace Divisaction */

#endif //THREEENGINE_VECTOR_H
